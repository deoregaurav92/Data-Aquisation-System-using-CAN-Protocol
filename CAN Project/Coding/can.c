/*-------------------------------------------------------------
	CAN protocol functions
--------------------------------------------------------------*/

#include<htc.h>
#include "adc.h"
#include "lcd.h"
#include "can.h"

unsigned char result;

/*-------------------------------------------------------------
	CAN engine initialization
--------------------------------------------------------------*/
void can_init(void)
{
	TRISB=0x08;		//Configure Pin CAN_RX as input, rest as output
	CANCON=0x10;	//Abort all Transmission
	CANCON=0x80;	//Request Configuration mode
	while(!(CANCON&0x80));//Wait until into Config. mode
	BRGCON1=0x04;	//Set Baud Rate 
	BRGCON2=0xC9;	//Phase seg=2xTQ, Propogation Time=2xTQ
	BRGCON3=0x01;	//Phase seg2=2xTQ
	TXB0SIDH=0xFF;	//Set Standard Identifier for Transmission
	TXB0SIDL=0xA0;
	TXB0EIDH=0x00;	//Set Extended Identifier for Transmission
	TXB0EIDL=0x00;
	RXM0EIDH=0x00;  //Set Extended Identifier Mask for Reception  
	RXM0EIDL=0x00;
	RXM0SIDH=0xFF;	//Set Standard Identifier Mask for Reception
	RXM0SIDL=0xE0;
	RXM1EIDH=0x00;  
	RXM1EIDL=0x00;
	RXM1SIDH=0xFF;
	RXM1SIDL=0xE0;
	RXF0EIDH=0x00;	//Set Extended Identifier Filter for Reception
	RXF0EIDL=0x00;
	RXF0SIDH=0xFF;	//Set Standard Identifier Filter for Reception  
	RXF0SIDL=0xA0;
	RXF1EIDH=0x00;
	RXF1EIDL=0x00;
	RXF1SIDH=0xFF;  
	RXF1SIDL=0xA0;
	RXB0CON=0x64;	//Recieve all Messages
	CIOCON=0x20;	//Enable Drive High Bit
	PIE3=0xff;		//Enable Interrupt
	GIEH = 1;		//Enable Global Interrupt
	PEIE = 1;		//Enable Peripheral Interrupt
	TXB0IF = 0;		//Clear TX Interrupt Request Flag
	TXB0IE = 1;		//Enable TX Interrupt
	RXB0IF=0;		//Clear RX Interrupt Request Flag
	RXB0IE=1;		//Enable RX Interrupt
	CANCON=0x00;	//Request Normal Mode
}

/*-------------------------------------------------------------
	CAN Transmission
--------------------------------------------------------------*/
void can_TX(unsigned int *p)
{
	unsigned char i=0,vol[5],d1,d2,n='\n',r='\r';
	result=*p;
	d1=((*p>>8)&0xFF);
	d2=(*p&0xFF);
	TXB0DLC=0x02;	//Configure Data Field Length
	TXB0D0 = d1;	//Set Data Field
	TXB0D1 = d2;
	TXB0D2 = 0x00;
	TXB0D3 = 0x00;
	TXB0D4 = 0x00;
	TXB0D5 = 0x00;
	TXB0D6 = 0x00;
	TXB0D7 = 0x00;
	TXB0SIDH=0xFF;	//Set Identifier
	TXB0SIDL=0xA0;
	TXB0CON=0x08;	//Transmit Request
	//while(TXB0CON==0x08);
	//while(TXB0REQ);
	TXB0IF=0;		//Clear Interrupt Flag
}