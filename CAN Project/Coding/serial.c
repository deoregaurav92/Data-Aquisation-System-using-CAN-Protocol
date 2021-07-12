/*-------------------------------------------------------------
	Serial Port
--------------------------------------------------------------*/
#include "serial.h"

/*-------------------------------------------------------------
	Serial Port Initialization
--------------------------------------------------------------*/
void serial_init(void)
{
	TRISC=0xBF;		//Configure TX as output, rest as input
	TXSTA=0x26;		//TX enable, 8bit data 
	RCSTA=0x90;		//RX enable
	SPBRG=25;		//Baud rate=9600
}

/*-------------------------------------------------------------
	Display string on Hyperterminal
--------------------------------------------------------------*/
void serial_write(unsigned char *p)
{
	while(*p)
	{
		TXREG=*p;
		while(!TXIF);
		TXIF=0;
		TRMT=0;
		p++;
	}
}