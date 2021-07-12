/*-------------------------------------------------------------
	
	NODE2
	Humidity measurement using sensor SYHS220
	Transmitting humidity value over CAN bus
	Displaying humidity value in percentage on 16x2 LCD display
	
--------------------------------------------------------------*/

#include<htc.h>
#include "adc.h"
#include "lcd.h"
#include "can.h"

#define _XTAL_FREQ 4000000

/*-------------------------------------------------------------
	CONFIG WORD
--------------------------------------------------------------*/
#pragma config BOR =OFF		//Brown out reset OFF
#pragma config WDT =OFF		//Watch Dog Timer OFF
#pragma config LVP =OFF		//Low Voltage Programming OFF
#pragma config OSC =HS		//High Speed Oscilator
#pragma config PWRT =ON		//Power On Reset=ON
#pragma config DEBUG =OFF	//Debugger OFF

/*-------------------------------------------------------------
	INTERRUPT ROUTINE
--------------------------------------------------------------*/
void interrupt can_isr(void)
{
	if(TXB0IF)
	{
		TXB0IF=0;		//Clear CAN_TX flag
	}
	if(RXB0IF)
	{
		RXB0IF=0;		//Clear CAN_RX flag
	}
}

/*-------------------------------------------------------------
	Main
--------------------------------------------------------------*/

#define SAMPLES_PER_SECOND 1

void main(void)
{
	unsigned int *p,c[10],val,sample;
	unsigned char i;
	adc_init();						//ADC initialization
	//serial_init();					//Serial initialization
	lcd_init();						//16x2 LCD initialization
	can_init();						//CAN engine initialization
	lcd_puts("CAN TRANSMIT");		//Display initial string
	delay(1000);		
	lcd_write(0,0x01);		
	lcd_puts("HUMIDITY: ");			
	p=c;
	sample=SAMPLES_PER_SECOND*1000;
	while(1)
	{
		for(i=0;i<10;i++,delay(1))
		{
			c[i]=read_analog();		//take 10 sample values of temp in array
		}
		val=avg(p);					//get average value of 10 samples
		convert(val);				//convert into deg.C and print value
		delay(sample);		
		p=c;
	}
}