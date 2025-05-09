
//RS =PD0
//RW =PD1
//EN =PD2

//D0 =PA7
//D1= PA6
//D2= PA5
//D3= PB4
//D4= PE5
//D5= PE4
//D6= PB1
//D7= PB0
void delay(long d);
void printdata(unsigned char data);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_string( char *str,int len);
void lcd_init(void);
void SystemInit(void);
// LCD.h




