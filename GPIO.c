#include "tm4c123gh6pm.h"
#include "Macros.h"
void PORT_INT(unsigned char portname){
	
	
switch(portname){
	case'A':
	case'a':
	{
	SET_BIT(SYSCTL_RCGCGPIO_R ,0);
	while (READ_BIT(SYSCTL_PRGPIO_R, 0) == 0)
	 GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
	 GPIO_PORTA_CR_R =0xff;
	 GPIO_PORTA_DEN_R=0xff;
	 GPIO_PORTA_AMSEL_R =0x0;
	 GPIO_PORTA_PCTL_R=0x0; 
	 GPIO_PORTA_AFSEL_R=0x0; 
	break;
	
	}
	case'B':
	case'b':
	{
	SET_BIT(SYSCTL_RCGCGPIO_R ,1);
	while (READ_BIT(SYSCTL_PRGPIO_R, 1) == 0)
	 GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
	 GPIO_PORTB_CR_R =0xff;
	 GPIO_PORTB_DEN_R=0xff;
	 GPIO_PORTB_AMSEL_R =0x0;
	 GPIO_PORTB_PCTL_R=0x0; 
	 GPIO_PORTB_AFSEL_R=0x0; 
	break;
	
	

	}
	case'D':
	case'd':
	{
	
	SET_BIT(SYSCTL_RCGCGPIO_R ,3);
	while (READ_BIT(SYSCTL_PRGPIO_R, 3) == 0)
	 GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
	 GPIO_PORTD_CR_R =0xff;
	 GPIO_PORTD_DEN_R=0xff;
	 GPIO_PORTD_AMSEL_R =0x0;
	 GPIO_PORTD_PCTL_R=0x0; 
	 GPIO_PORTD_AFSEL_R=0x0; 
	break;
	
	
	
	}
	case'E':
	case'e':
	{
	SET_BIT(SYSCTL_RCGCGPIO_R ,4);
	while (READ_BIT(SYSCTL_PRGPIO_R, 4) == 0)
	 GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
	 GPIO_PORTE_CR_R =0xff;
	 GPIO_PORTE_DEN_R=0xff;
	 GPIO_PORTE_AMSEL_R =0x0;
	 GPIO_PORTE_PCTL_R=0x0; 
	 GPIO_PORTE_AFSEL_R=0x0; 
	break;
	
	
	}
	case'F':
	case'f':
	{
		SET_BIT(SYSCTL_RCGCGPIO_R ,5);
	while (READ_BIT(SYSCTL_PRGPIO_R, 5) == 0)
	 GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
	 GPIO_PORTF_CR_R =0x1f;
	 GPIO_PORTF_DEN_R=0x1f;
	 GPIO_PORTF_AMSEL_R =0x0;
	 GPIO_PORTF_PCTL_R=0x0; 
	 GPIO_PORTF_AFSEL_R=0x0; 
	break;

	}


}

}
void SET_PIN_DIR(unsigned char portname,unsigned char pinnumber,unsigned char direction){
	
	
	
	
	switch(portname){
	case'A':
	case'a':
	{
		if(direction==1)
			SET_BIT(GPIO_PORTA_DIR_R,pinnumber ); 
		if(direction==0)
			CLR_BIT(GPIO_PORTA_DIR_R,pinnumber ); 
		
		
	break;
	}
	case'B':
	case'b':
	{
		if(direction==1)
			SET_BIT(GPIO_PORTB_DIR_R,pinnumber ); 
		if(direction==0)
			CLR_BIT(GPIO_PORTB_DIR_R,pinnumber ); 
		
	
	break;
	
	

	}
	case'D':
	case'd':
	{
		if(direction==1)
			SET_BIT(GPIO_PORTD_DIR_R,pinnumber ); 
		if(direction==0)
			CLR_BIT(GPIO_PORTD_DIR_R,pinnumber ); 
		
	

	break;
	
	
	
	}
	case'E':
	case'e':
	{
			if(direction==1)
			SET_BIT(GPIO_PORTE_DIR_R,pinnumber ); 
		if(direction==0)
			CLR_BIT(GPIO_PORTE_DIR_R,pinnumber ); 
		
	
	
	break;
	
	
	}
	case'F':
	case'f':
	{
		if(direction==1)
			SET_BIT(GPIO_PORTF_DIR_R,pinnumber ); 
		if(direction==0)
			CLR_BIT(GPIO_PORTF_DIR_R,pinnumber ); 
		
	
	break;

	}






}
}



void SET_PIN_DATA(unsigned char portname,unsigned char pinnumber,unsigned char data){
	
	
	
	
	switch(portname){
	case'A':
	case'a':
	{
		if(data==1)
			SET_BIT(GPIO_PORTA_DATA_R,pinnumber ); 
		if(data==0)
			CLR_BIT(GPIO_PORTA_DATA_R,pinnumber ); 
		
		
	break;
	}
	case'B':
	case'b':
	{
		if(data==1)
			SET_BIT(GPIO_PORTB_DATA_R,pinnumber ); 
		if(data==0)
			CLR_BIT(GPIO_PORTB_DATA_R,pinnumber ); 
		
	
	break;
	
	

	}
	case'D':
	case'd':
	{
		if(data==1)
			SET_BIT(GPIO_PORTD_DATA_R,pinnumber ); 
		if(data==0)
			CLR_BIT(GPIO_PORTD_DATA_R,pinnumber ); 
		
	

	break;
	
	
	
	}
	case'E':
	case'e':
	{
			if(data==1)
			SET_BIT(GPIO_PORTE_DATA_R,pinnumber ); 
		if(data==0)
			CLR_BIT(GPIO_PORTE_DATA_R,pinnumber ); 
		
	
	
	break;
	
	
	}
	case'F':
	case'f':
	{
		if(data==1)
			SET_BIT(GPIO_PORTF_DATA_R,pinnumber ); 
		if(data==0)
			CLR_BIT(GPIO_PORTF_DATA_R,pinnumber ); 
		
	
	break;

	}



}
}



void TOGLE_PIN(unsigned char portname,unsigned char pinnumber){
	
	
	
	
	switch(portname){
	case'A':
	case'a':
	{
		
			TOGLE_BIT(GPIO_PORTA_DATA_R,pinnumber ); 
	
	break;
	}
	case'B':
	case'b':
	{
		
			TOGLE_BIT(GPIO_PORTB_DATA_R,pinnumber ); 

	break;
	
	

	}
	case'D':
	case'd':
	{
	
			TOGLE_BIT(GPIO_PORTD_DATA_R,pinnumber ); 
		

	break;
	
	
	
	}
	case'E':
	case'e':
	{
		
			TOGLE_BIT(GPIO_PORTE_DATA_R,pinnumber ); 
		
	break;
	
	
	}
	case'F':
	case'f':
	{
		
			TOGLE_BIT(GPIO_PORTF_DATA_R,pinnumber ); 
		
	
	break;

	}



}
}
void SET_PORT_DIR(unsigned char portname,unsigned char direction){
	switch(portname){
	case'A':
	case'a':
	{
		
			GPIO_PORTA_DIR_R= direction;
		
	break;
	}
	case'B':
	case'b':
	{
		
			GPIO_PORTB_DIR_R= direction;
		
	break;
	
	

	}
	case'D':
	case'd':
	{
		
			GPIO_PORTD_DIR_R= direction;
		
	

	break;
	
	
	
	}
	case'E':
	case'e':
	{
		
				GPIO_PORTE_DIR_R= direction;
		
	break;
	
	
	}
	case'F':
	case'f':
	{
		
		
				GPIO_PORTF_DIR_R= direction;
		
	break;

	}


}
	
}

void SET_PORT_DATA(unsigned char portname,unsigned char data){
switch(portname){
	case'A':
	case'a':
	{
		
			GPIO_PORTA_DATA_R= data;
		
	break;
	}
	case'B':
	case'b':
	{
		
			GPIO_PORTB_DATA_R= data;
		
	break;
	
	

	}
	case'D':
	case'd':
	{
		
			GPIO_PORTD_DATA_R= data;
		
	

	break;
	
	
	
	}
	case'E':
	case'e':
	{
		
				GPIO_PORTE_DATA_R= data;
		
	break;
	
	
	}
	case'F':
	case'f':
	{
		
		GPIO_PORTF_DATA_R= data;
		
	break;

	}


}


}

unsigned char READ_PIN (unsigned char portname,unsigned char pinnumber){

switch(portname){
	case'A':
	case'a':
	{
		
		return	READ_BIT(GPIO_PORTA_DATA_R,pinnumber ); 
	
	break;
	}
	case'B':
	case'b':
	{
		
		return	READ_BIT(GPIO_PORTB_DATA_R,pinnumber ); 

	break;
	
	

	}
	case'D':
	case'd':
	{
	
			return	READ_BIT(GPIO_PORTD_DATA_R,pinnumber );  
		

	break;
	
	
	
	}
	case'E':
	case'e':
	{
		
		return	READ_BIT(GPIO_PORTE_DATA_R,pinnumber ); 
	break;
	
	
	}
	case'F':
	case'f':
	{
		
			return	READ_BIT(GPIO_PORTF_DATA_R,pinnumber ); 
		
	
	break;

	}




}

}

unsigned char READ_PORT (unsigned char portname){

switch(portname){
	case'A':
	case'a':
	{
		
		return	GPIO_PORTA_DATA_R ;
	
	break;
	}
	case'B':
	case'b':
	{
		
			return	GPIO_PORTB_DATA_R ;
	break;
	
	

	}
	case'D':
	case'd':
	{
	
			return	GPIO_PORTD_DATA_R ;
		

	break;
	
	
	
	}
	case'E':
	case'e':
	{
		
			return	GPIO_PORTE_DATA_R ;
	break;
	
	
	}
	case'F':
	case'f':
	{
		
			return	GPIO_PORTF_DATA_R ;
		
	
	break;

	}




}

}

void ENABLE_PULLUP(unsigned char portname,unsigned char pinnumber){

	switch(portname){
	case'A':
	case'a':
	{
		
		SET_BIT(GPIO_PORTA_PUR_R,pinnumber ); 
	
	break;
	}
	case'B':
	case'b':
	{
		
		SET_BIT(GPIO_PORTB_PUR_R,pinnumber );  

	break;
	
	

	}
	case'D':
	case'd':
	{
	
			SET_BIT(GPIO_PORTD_PUR_R,pinnumber );   
		

	break;
	
	
	
	}
	case'E':
	case'e':
	{
		
	SET_BIT(GPIO_PORTE_PUR_R,pinnumber ); 
	break;
	
	
	}
	case'F':
	case'f':
	{
		
		SET_BIT(GPIO_PORTF_PUR_R,pinnumber ); 
		
	
	break;

	}




}
	
	


}

void SET_HIGHNIBBLE(unsigned char portname,unsigned char data){
	data<<=4;
	
	
switch(portname){
	case'A':
	case'a':
	{
		
		GPIO_PORTA_DATA_R &=0x0f ;
		GPIO_PORTA_DATA_R |=data ;
	
	break;
	}
	case'B':
	case'b':
	{
			GPIO_PORTB_DATA_R &=0x0f ;
		GPIO_PORTB_DATA_R |=data ;
	
	break;
	
	

	}
	case'D':
	case'd':
	{
		GPIO_PORTD_DATA_R &=0x0f ;
		GPIO_PORTD_DATA_R |=data ;
	

	break;
	
	
	
	}
	case'E':
	case'e':
	{
		
				GPIO_PORTE_DATA_R &=0x0f ;
		GPIO_PORTE_DATA_R |=data ;
	
	break;
	
	
	}
	case'F':
	case'f':
	{
			GPIO_PORTF_DATA_R &=0x0f ;
		GPIO_PORTF_DATA_R |=data ;
	
	
	break;

	}

}

}
void SET_LOWNIBBLE(unsigned char portname,unsigned char data){
	
	
	
switch(portname){
	case'A':
	case'a':
	{
		
		GPIO_PORTA_DATA_R &=0xf0;
		GPIO_PORTA_DATA_R |=data ;
	
	break;
	}
	case'B':
	case'b':
	{
			GPIO_PORTB_DATA_R &=0xf0 ;
		GPIO_PORTB_DATA_R |=data ;
	
	break;
	
	

	}
	case'D':
	case'd':
	{
		GPIO_PORTD_DATA_R &=0xf0 ;
		GPIO_PORTD_DATA_R |=data ;
	

	break;
	
	
	
	}
	case'E':
	case'e':
	{
		
				GPIO_PORTE_DATA_R &=0xf0 ;
		GPIO_PORTE_DATA_R |=data ;
	
	break;
	
	
	}
	case'F':
	case'f':
	{
			GPIO_PORTF_DATA_R &=0xf0 ;
		GPIO_PORTF_DATA_R |=data ;
	
	
	break;

	}




}




}






