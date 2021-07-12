/*-------------------------------------------------------------
	Analog to Digital Conversion functions
--------------------------------------------------------------*/

#include "adc.h"
#include "lcd.h"
#include "can.h"

/*------------------------------------------------------------
Look-up table for humidity sensor with threshhold values
for humidity in %----->30% 40% 50% 60% 70% 80% 90%		-----*/
unsigned int table[7]={198,260,330,396,462,528,594};

/*-------------------------------------------------------------
	ADC Initialization
--------------------------------------------------------------*/
void adc_init()
{
	TRISA=0xFF;		//Configure PORT A as input
	TRISD=0x00;		//Configure PORT D as output
	TRISB=0x08;		//Configure Pin CAN_RX as input, rest as output
	ADCON1=0xF4;	//Select channel 1 for humidity sensing
	ADCON0=0x8D;	//Configure ADC clock source and output format
}

/*-------------------------------------------------------------
	Reading Analog Value
--------------------------------------------------------------*/
unsigned int read_analog()
{
	unsigned int c;
	ADCON0=0x8D;		//Start Analog to Digital Conversion
	while(ADCON0&0x04);	//Wait till conversion is complete
	c=ADRESH;			//Read MSB from 10 bit value
	c=(c<<8)+ADRESL;	//Read and Add LSB value
	return c;			//Return read value
}

/*-------------------------------------------------------------
	Averaging the Value
--------------------------------------------------------------*/
unsigned int avg(unsigned int * p)
{
	unsigned char i;
	unsigned int v=0;
	for(i=0;i<10;i++,p++)	//for array of 10 values
	{
			v+=(*p);		//Summing all values
	}
	v=(v/10);				//Average=Arithematic Mean
	return v;				//Return average value
}

/*-------------------------------------------------------------
	Convert Value to appropriate format for transmission
--------------------------------------------------------------*/
void convert(unsigned int c)
{
	unsigned char i=0;//,vol[5],u='\r';
	unsigned int hum,volt;
	volt=c*5;			//multiplying by step volatage
	hum=c;
	lcd_write(0,0xC0);	//Line 1 character 0
	for(i=0;hum>table[i];i++);
	switch(i)
	{
		case 0 : lcd_puts("0-30%");break;
		case 1 : lcd_puts("30-40%");break;
		case 2 : lcd_puts("40-50%");break;
		case 3 : lcd_puts("50-60%");break;
		case 4 : lcd_puts("60-70%");break;
		case 5 : lcd_puts("70-80%");break;
		case 6 : lcd_puts("80-90%");break;
		default:lcd_puts("More than 90%");
	}
	can_TX(&hum);		//Transmit ADC value over CAN bus
	//i=0;
	/*while(volt)
	{
		vol[i]=(volt%10)+48;
		volt=volt/10;
		i++;
	}
	while(i>1)
	{
		lcd_write(1,vol[i-1]);
		//can_TX(&vol[i-1]);
		i--;
	}*/
	/*lcd_write(1,vol[i-1]);
	lcd_write(1,'m');
	lcd_write(1,'V');*/
}