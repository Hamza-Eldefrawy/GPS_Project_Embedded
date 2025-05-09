#include <stdint.h>
#include "tm4c123gh6pm.h"

void UART2_Init(void) {
    // Enable UART2 and GPIOD
    SYSCTL_RCGCUART_R |= 0x04;    // UART2
    SYSCTL_RCGCGPIO_R |= 0x08;    // GPIOD

    while ((SYSCTL_PRGPIO_R & 0x08) == 0); // Wait for GPIOD to be ready

    // Unlock PD7
    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R |= 0x80;

    // Disable UART2
    UART2_CTL_R &= ~0x01;

    // Set baud rate for 9600 (assuming 16 MHz clock)
    UART2_IBRD_R = 0x68;
    UART2_FBRD_R = 0x0B;

    // Line control: 8-bit, FIFO enabled
    UART2_LCRH_R = 0x70;

    // Clock source = system
    UART2_CC_R = 0x00;

    // Enable UART2, TX, RX
    UART2_CTL_R |= 0x301;

    // PD6, PD7 ? alternate function
    GPIO_PORTD_AFSEL_R |= 0xC0;
    GPIO_PORTD_PCTL_R &= ~0xFF000000;
    GPIO_PORTD_PCTL_R |=  0x11000000;

    // Digital enable and analog disable
    GPIO_PORTD_DEN_R |= 0xC0;
    GPIO_PORTD_AMSEL_R &= ~0xC0;
}

char UART2_ReadChar(void) {
    while ((UART2_FR_R & 0x10) != 0);  // Wait until RXFE (bit 4) is 0 ? FIFO not empty
    return (char)(UART2_DR_R & 0xFF);  // Read the received byte (mask lower 8 bits)
}

void UART0_Init(void) {
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0) == 0);

    GPIO_PORTA_AFSEL_R |= (1 << 1) | (1 << 0);
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011;
    GPIO_PORTA_DEN_R |= (1 << 1) | (1 << 0);

    UART0_CTL_R &= ~(uint32_t)UART_CTL_UARTEN;
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
    UART0_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);
    UART0_CTL_R |= (UART_CTL_UARTEN | UART_CTL_RXE | UART_CTL_TXE);
}

void UART0_Print(char *buf) {
    while (*buf) {
        while (UART0_FR_R & UART_FR_TXFF);
        UART0_DR_R = *buf++;
    }
}


