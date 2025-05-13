#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "LCD.h"
#include "UART.h"
#include "GPS.h"
#include "GPIO.h"
#include "LED.h"


#define LCD_Clear() lcd_cmd(0x01)

#define LCD_OutString(str) lcd_string(str, strlen(str))

int main(void) {
    char temp_string[20];
    int temp_len;

    int nearest_index;

    // Initialization
    PORT_INT('b');
		SET_PIN_DIR('b', 2, 1);
		SET_PIN_DIR('b', 3, 1);


    UART0_Init();
    UART2_Init();
    lcd_init();

    LCD_Clear();
    LCD_OutString("Waiting 4 GPS...");

    while (1) {
        GPS_ReadData();
        GPS_ProcessData();

        nearest_index = FindNearestLandmark(latitude, longitude);

        if (!(latitude == 0.0 && longitude == 0.0)) {
            snprintf(temp_string, sizeof(temp_string), "Latitude:%.5f\n", latitude);
            UART0_Print(temp_string);

            snprintf(temp_string, sizeof(temp_string), "Longitude:%.5f\n", longitude);
            UART0_Print(temp_string);

            snprintf(temp_string, sizeof(temp_string), "%.0fm", (float)minDist * 1000);
            UART0_Print("Distance:"); 
            UART0_Print(temp_string);
            UART0_Print("\n\r");
        } else {
            UART0_Print("No valid GPS, fix\n\r");
        }

        LCD_Clear();
        
        if (minDist * 1000 < 50) {
          SET_PIN_DATA('b', 2, 1);
          SET_PIN_DATA('b', 3, 1);
          
          LCD_OutString("Nearest:");
          LCD_OutString(temp_string);
          lcd_cmd(0xc0);
          lcd_string(name[nearest_index], strlen(name[nearest_index]));
        } else {
          SET_PIN_DATA('b', 2, 0);
          SET_PIN_DATA('b', 3, 0);
          lcd_string("Keep Going...", 13);
        }
    }
}
