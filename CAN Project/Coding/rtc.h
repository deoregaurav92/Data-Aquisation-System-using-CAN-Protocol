/*-------------------------------------------------------------
	Real Time Clock
--------------------------------------------------------------*/

#include<htc.h>

void clock_init(void);
void timer_init(void);
void time_update(void);
void date_update(void);

#define DAY dp->dd
#define MONTH dp->mm
#define YEAR dp->yy
#define HOUR tp->hr
#define MINUTES tp->min
#define SECONDS tp->sec

typedef struct dt{
				unsigned char dd:5,mm:4;
				unsigned short int yy;
				}date;

typedef struct tm{
				unsigned char hr:5,min:6,sec:6;
				}time;
				
date d;
date *dp=&d;
time t;
time *tp=&t;