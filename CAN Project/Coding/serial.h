/*-------------------------------------------------------------
	Serial Port
--------------------------------------------------------------*/

#include<htc.h>

void serial_init(void);
void serial_write(unsigned char *);

unsigned char time_hum[9]="00:00:00";
unsigned char time_temp[9]="00:00:00";