#include "tm4c123gh6pm.h"
#include "Macros.h"
#include "GPIO.h"
void LED_INT(unsigned char portname,unsigned char pinnumber){
SET_PIN_DIR( portname, pinnumber,1);

}
void LED_ON(unsigned char portname,unsigned char pinnumber){
SET_PIN_DATA(portname,pinnumber,1);
}
void LED_OFF(unsigned char portname,unsigned char pinnumber){
SET_PIN_DATA(portname,pinnumber,0);
}
void LED_TOGLE(unsigned char portname,unsigned char pinnumber){
TOGLE_PIN(portname,pinnumber);

}
