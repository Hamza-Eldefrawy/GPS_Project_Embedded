#ifndef GPS_H
#define GPS_H

#include <stdint.h>

void UART0_Init(void);
void UART0_Print(const char *s);
void UART2_Init(void);
void GPS_Read(char *buf, uint32_t max_len);
void GPS_ReadLine(char *buf, uint32_t max_len);
uint8_t GPS_ReadLocation(char *latitude, char *longitude);

#endif
