/*-------------------------------------------------------------
	16x2 LCD functions
--------------------------------------------------------------*/

#include<htc.h>
#include "lcd.h"
#include "adc.h"
#include "can.h"

/*-------------------------------------------------------------
	LCD initialization
--------------------------------------------------------------*/
void lcd_init()
{
	lcd_write(0,0x02);	
	lcd_write(0,0x28);	//4 bit mode
	lcd_write(0,0x01);	//Clear LCD
	lcd_write(0,0x0e);	//Cursor ON, blink
	lcd_write(0,0x80);	//first line, first character
}

/*-------------------------------------------------------------
	Writing to LCD
--------------------------------------------------------------*/
void lcd_write(unsigned char c,unsigned char d)
{
	busy = 1;		
	RS = 0;
 	RW = 1;
 	while(check==1)		//check for busy
 	{
		EN = 0;
		delay(2);
		EN =1;
 	}
	busy = 0;
	lcd_data=((d&0xF0));//Send higher nibble
 	RS=c;
 	RW=0;
 	EN=1;
 	delay(5);
 	EN=0;
	lcd_data=((d&0x0F)<<4);//Send lower nibble
 	RS=c;
 	RW=0;
 	EN=1;
 	delay(5);
 	EN=0;
}

/*-------------------------------------------------------------
	Display a String on LCD
--------------------------------------------------------------*/
void lcd_puts(const unsigned char *s)
{
	while(*s)
	{
		lcd_write(1,*s++);
	}
}

/*-------------------------------------------------------------
	Software Delay Routine
--------------------------------------------------------------*/
void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<65;j++);
}