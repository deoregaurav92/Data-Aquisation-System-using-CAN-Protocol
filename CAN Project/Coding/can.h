/*-------------------------------------------------------------
	CAN protocol
--------------------------------------------------------------*/

#include<htc.h>
#include "adc.h"
#include "lcd.h"

void can_init(void);
void can_TX(unsigned int *);
unsigned char can_RX(void);
void serial_init(void);
