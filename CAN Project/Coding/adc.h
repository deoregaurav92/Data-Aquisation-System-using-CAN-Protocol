/*-------------------------------------------------------------
	Analog to Digital Conversion
--------------------------------------------------------------*/

#include<htc.h>

void adc_init();
unsigned int read_analog();
void convert(unsigned int );
unsigned int avg(unsigned int *);
