/*-------------------------------------------------------------
	16x2 LCD
--------------------------------------------------------------*/

#include<htc.h>

#define lcd_data PORTB
#define busy TRISB7
#define check RB7
#define EN RD7
#define RW RD6
#define RS RD5

void lcd_init();
void lcd_write(unsigned char ,unsigned char );
void lcd_puts(const unsigned char *);
void delay(unsigned int );
