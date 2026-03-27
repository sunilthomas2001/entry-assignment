   /*
 * Timer.c
 *
 * Created: 25-03-2026 00:26:18
 *  Author: Sunil Thomas
 */ 



#include "Timer.h"
#define F_CPU 16000000UL

void TIMER_CONFIG(void)
{
	//CONFIGURING TIMER 0 CTC MODE
	TCCR0A &=~(1<<WGM00);
	TCCR0A |=(1<<WGM01);
	
	//CONFIGURING TIMER0 FOR 1024 PRESCALAR
	TCCR0B|=(1<<CS00)|(1<<CS02);
	TCCR0B&=~(1<<CS01);
	
	DDRB|=(1<<PB0); //CONFIGURING PB5 AS PIN FOR LED
}


void DELAY_VALUE(void)
{
	OCR0A=200;
	
	TCNT0= 0; // initial value of TCNT0 =0
	
}

void delay_500ms(void)
{
	for(int i=0;i<39;i++) //repeating the process 39 times to get delay 0.5second
	{
		while (!(TIFR0&(1<<OCF0A))); //wait until ocf0a =1
		TIFR0|=(1<<OCF0A); //writing 1 to OCF0A bit to make it 0
	}
}