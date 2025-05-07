#include "TM4C123GH6PM.h"
#include "GPS.h"
#include "GPIO.h"

#define MAX_GPS_LINE 100

void UART0_Init(void) {
    SYSCTL->RCGCUART |= (1 << 0);
    SYSCTL->RCGCGPIO |= (1 << 0);   // Enable GPIOA
    while ((SYSCTL->PRGPIO & 0x01) == 0);

    UART0->CTL &= ~0x01;            // Disable UART0
    UART0->IBRD = 104;              // 9600 baud
    UART0->FBRD = 11;
    UART0->LCRH = 0x70;
    UART0->CC = 0x0;                // System clock
    UART0->CTL |= 0x301;            // Enable UART0, TXE and RXE

    GPIOA->AFSEL |= (1 << 0) | (1 << 1);
    GPIOA->PCTL = (GPIOA->PCTL & ~0xFF) | 0x11;
    GPIOA->DEN |= (1 << 0) | (1 << 1);
    GPIOA->DIR |= (1 << 1);
    GPIOA->DIR &= ~(1 << 0);
}

void UART0_Print(const char *s) {
    while (*s) {
      while (UART0->FR & (1 << 5)); // Wait until TXFF is 0
      UART0->DR = *s++;
    }
}

void UART2_Init(void) {
    SYSCTL->RCGCUART |= (1 << 2);    // Enable UART2 clock
    PORT_INT('D');                   // Initialize Port D

    // Unlock PD7 if needed
    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R |= (1 << 7);

    // UART2 configuration
    UART2->CTL &= ~0x01;             // Disable UART2
    UART2->IBRD = 104;               // Integer baud rate divisor
    UART2->FBRD = 11;                // Fractional baud rate divisor
    UART2->LCRH = 0x70;              // 8-bit, no parity, 1 stop, FIFO enabled
    UART2->CC = 0x0;                 // Use system clock
    UART2->CTL |= 0x301;             // Enable UART2, TXE and RXE

    // Configure PD6 (RX) and PD7 (TX) for UART2
    SET_PIN_DIR('D', 6, 0);          // PD6 input
    SET_PIN_DIR('D', 7, 1);          // PD7 output

    GPIO_PORTD_AFSEL_R |= (1 << 6) | (1 << 7);            // Enable alternate function
    GPIO_PORTD_PCTL_R &= ~0xFF000000;                     // Clear PCTL for PD6 and PD7
    GPIO_PORTD_PCTL_R |= (1 << 24) | (1 << 28);           // Set PCTL for UART2
}

void GPS_Read(char *buf, uint32_t max_len) {
    uint32_t i = 0;

    for (uint32_t j = 0; j < max_len; j++) {
        buf[j] = 0;
    }

    while (i < max_len - 1) {
        if ((UART2->FR & (1 << 4)) == 0) {  // While RXFE is 0 (data is available)
            char c = UART2->DR & 0xFF;
            if (c == '\n') break;
            buf[i++] = c;
        }
    }
    buf[i] = '\0';
}

void GPS_ReadLine(char *buf, uint32_t max_len) {
    uint32_t i = 0;
    char c;

    // Wait until we see a start character '$'
    do {
        while (UART2->FR & (1 << 4)); // Wait for char
        c = UART2->DR & 0xFF;
    } while (c != '$');

    buf[i++] = '$';

    // Read until newline or buffer full
    while (i < max_len - 1) {
        while (UART2->FR & (1 << 4)); // Wait for char
        c = UART2->DR & 0xFF;
        if (c == '\n') break;
        buf[i++] = c;
    }
    buf[i] = '\0';
}

uint8_t GPS_ReadLocation(char *latitude, char *longitude) { //Function return to flag success or not
    char line[MAX_GPS_LINE];

    while (1) {
        GPS_ReadLine(line, MAX_GPS_LINE);

        // Check if line is a GPRMC sentence
        if (strstr(line, "$GPRMC")) {
            // Tokenize the sentence
            char *token = strtok(line, ",");
            int field = 0;
            while (token != NULL) {
                field++;

                if (field == 4) { // Latitude
                    strcpy(latitude, token);
                }
                if (field == 6) { // Longitude
                    strcpy(longitude, token);
                    return 1; // Done
                }

                token = strtok(NULL, ",");
            }
        }
    }

    return 0; // Should not reach here
}
