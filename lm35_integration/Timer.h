  /*
 * Timer.h
 *
 * Created: 25-03-2026 00:25:28
 *  Author: Sunil Thomas
 */ 





#ifndef TIMER_H_
#define TIMER_H_

#include <util/delay.h>
#include <stdint.h>
#define F_CPU 16000000UL
#include <avr/io.h>

void TIMER_CONFIG(void);
void DELAY_VALUE(void);
void delay_500ms(void);



#endif /* TIMER_H_ */           