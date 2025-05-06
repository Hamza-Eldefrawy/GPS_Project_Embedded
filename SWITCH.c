#include "tm4c123gh6pm.h"
#include "Macros.h"
#include "GPIO.h"
void SWITCH_INT(unsigned char portname,unsigned char pinnumber){
SET_PIN_DIR(portname,pinnumber,0);
ENABLE_PULLUP(portname,pinnumber);
	
}
unsigned char SWITCH_READ(unsigned char portname,unsigned char pinnumber){
return READ_PIN(portname,pinnumber);
}
