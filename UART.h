#ifndef UART_H
#define UART_H

#include <stdint.h> // Required for uint32_t if not included by tm4c123gh6pm.h indirectly

// Initialize UART2 for GPS (PD6 RX, PD7 TX) at 9600 baud
void UART2_Init(void);
// Read a character from UART2 (blocking)
// Note: The main loop now uses a non-blocking check before reading DR
// char UART2_ReadChar(void); // This specific function might not be needed if main reads DR directly after checking FR

// Initialize UART0 for Debug (PA0 RX, PA1 TX) at 9600 baud
void UART0_Init(void);
// Write a character to UART0 (blocking)
void UART0_WriteChar(char data);
// Write a null-terminated string to UART0
void UART0_OutString(char* str);
void UART0_Print(char *buf);
char UART2_ReadChar(void);


#endif
// Added newline after this #endif