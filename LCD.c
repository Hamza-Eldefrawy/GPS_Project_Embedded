#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "Macros.h"
#include "LCD.h"


void lcd_data(unsigned char data)
{
	//steps:
	
	//pass the data to be datalines of lcd
	printdata(data);
	//Turn off the R/W for write operation in lcd
	GPIO_PORTD_DATA_R &= ~(0x02);
	//Turn on the RS for writing to the data register of lcd
	GPIO_PORTD_DATA_R |= (0x01);
	//Turn on the Enable of LCD FOR Enabling the clock of LCD
	GPIO_PORTD_DATA_R |= (0x04);
	//wait for sometime(less than 1ms)
	delay(10000);
	//turn off the EN of LCD 
	GPIO_PORTD_DATA_R &= ~(0x04);
	
}

void lcd_cmd(unsigned char cmd)
{
	//steps:
	
	//pass the data to be datalines of lcd
	printdata(cmd);
	//Turn off the R/W for write operation in lcd
	GPIO_PORTD_DATA_R &= ~(0x02);
	//Turn off the RS for writing to the data register of lcd
	GPIO_PORTD_DATA_R &= ~(0x01);
	//Turn on the Enable of LCD FOR Enabling the clock of LCD
	GPIO_PORTD_DATA_R |= (0x04);
	//wait for sometime(less than 1ms)
	delay(10000);
	//turn off the EN of LCD 
	GPIO_PORTD_DATA_R &= ~(0x04);
	
}

void lcd_string( char *str,int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		lcd_data(str[i]);
		
	}
	
}

void lcd_init(void)
{
	//steps:
	//8bit mode utilising 16 Colums and 2 Rows
	lcd_cmd(0x38);
	//autoIncrementing the cursor when print data in current 
	lcd_cmd(0x06);
	//cursor off amd display on
	lcd_cmd(0x0C);
	//clear Screen
	lcd_cmd(0x01);
	
}

void delay(long d)
{
	while(d--);
	
}

void printdata(unsigned char data){
	// zeroth bit = D0 = PA7
    if ((data & 0x01) == 0x01)
        GPIO_PORTA_DATA_R = GPIO_PORTA_DATA_R | (1 << 7);
    else
        GPIO_PORTA_DATA_R = GPIO_PORTA_DATA_R & ~(1 << 7);
    
    // first bit = D1 = PA6
    if ((data & 0x02) == 0x02)
        GPIO_PORTA_DATA_R = GPIO_PORTA_DATA_R | (1 << 6);
    else
        GPIO_PORTA_DATA_R = GPIO_PORTA_DATA_R & ~(1 << 6);
    
    // second bit = D2 = PA5
    if ((data & 0x04) == 0x04)
        GPIO_PORTA_DATA_R = GPIO_PORTA_DATA_R | (1 << 5);
    else
        GPIO_PORTA_DATA_R = GPIO_PORTA_DATA_R & ~(1 << 5);
    
    // third bit = D3 = PB4
    if ((data & 0x08) == 0x08)
        GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | (1 << 4);
    else
        GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R & ~(1 << 4);
    
    // fourth bit = D4 = PE5
    if ((data & 0x10) == 0x10)
        GPIO_PORTE_DATA_R = GPIO_PORTE_DATA_R | (1 << 5);
    else
        GPIO_PORTE_DATA_R = GPIO_PORTE_DATA_R & ~(1 << 5);
    
    // fifth bit = D5 = PE4
    if ((data & 0x20) == 0x20)
        GPIO_PORTE_DATA_R = GPIO_PORTE_DATA_R | (1 << 4);
    else
        GPIO_PORTE_DATA_R = GPIO_PORTE_DATA_R & ~(1 << 4);
    
    // sixth bit = D6 = PB1
    if ((data & 0x40) == 0x40)
        GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | (1 << 1);
    else
        GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R & ~(1 << 1);
    
    // seventh bit = D7 = PB0
    if ((data & 0x80) == 0x80)
        GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R | (1 << 0);
    else
        GPIO_PORTB_DATA_R = GPIO_PORTB_DATA_R & ~(1 << 0);
	
}

void SystemInit(void)
{
	//clock of portA,portB,portD and portE
	
	SYSCTL_RCGCGPIO_R |= 0x1B;
	while ((SYSCTL_PRGPIO_R & 0x1B) == 0);
	
	// Digitalisa the data pins and config pins
	GPIO_PORTA_DEN_R |= 0xE0;
	GPIO_PORTB_DEN_R |= 0x13;
	GPIO_PORTD_DEN_R |= 0x07;
	GPIO_PORTE_DEN_R |= 0x30;
	
	//Direction of data pins and config pins ->output pins
	GPIO_PORTA_DIR_R |= 0xE0;
	GPIO_PORTB_DIR_R |= 0x13;
	GPIO_PORTD_DIR_R |= 0x07;
	GPIO_PORTE_DIR_R |= 0x30;
	
	
	
}
