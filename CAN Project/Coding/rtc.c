/*-------------------------------------------------------------
	Real Time Clock
--------------------------------------------------------------*/

#include "rtc.h"

/*-------------------------------------------------------------
	TIMER1 Initialization
--------------------------------------------------------------*/
void timer_init(void)
{
  TMR1H=0xfd;	//Load values in Timer1 register
  TMR1L=0x00;
  T1CON=0x05;	//Configure Timer1
  TMR1IE=1; 	//Enable Timer1 overflow interrupt
  PEIE=1;		//Enable Peripheral Interrupt
  GIE=1; 		//Enable Global Interrupt
}

/*-------------------------------------------------------------
	Initialize Clock Date and Time
--------------------------------------------------------------*/
void clock_init(void)
{
	HOUR=0;		
	MINUTES=0;
	SECONDS=0;
	DAY=1;
	MONTH=1;
	YEAR=2014;
}

/*-------------------------------------------------------------
	Update Time
--------------------------------------------------------------*/
void time_update(void)
{
	SECONDS++;
	if(SECONDS==60)
    {  
		SECONDS=0;
		MINUTES++;
		if(MINUTES==60)
		{
			MINUTES=0;HOUR++;
			if(HOUR==24)
			{
				HOUR=0;
				date_update();
			}
		}
	}
}

/*-------------------------------------------------------------
	Update Date
--------------------------------------------------------------*/
void date_update(void)
{
	DAY++;
    if(YEAR%4!=0 && MONTH==2 && DAY>=29)
    {
	    DAY=1;MONTH++;
	}
	else if(DAY==31 && (MONTH==4 || MONTH==6 || MONTH==9 || MONTH==11))
	{
	    DAY=1;MONTH++;
	}
	else if(DAY==0)	
	{
		DAY=1;MONTH++;
		if(MONTH>12)
		{
			MONTH=1;YEAR++;
		}
	}
}