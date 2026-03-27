/*
 * lm35_integration.c
 * Created: 26-03-2026 20:59:11
 * Author :Sunil Thomas
 
 
 
 
* statement;
 
 Design and implement a system using a LM35 temperature sensor and a microcontroller to achieve the following: 
 Temperature Measurement: Read the analog output from the LM35 and convert it to a Celsius value. 
 Dual Output: Display the real-time temperature on a 16x2 LCD and simultaneously transmit the data to a PC Serial Monitor using UART.
 Status Indicator:
 Blink an LED at 0.5-second intervals to indicate the machine is operational.
 Software Constraint: You must implement a custom delay function (e.g., my_delay_ms) to manage the timing, 
 rather than using the standard built-in delay library.
 

*solution;
            //hardware connections
            * PB0= arduino pin 8 for led status blinking
            * vss = gnd, vcc= 5v, rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  This is our lcd connection to arduino.
            * vcc = vss + rw, gnd = vcc, out = cc       potentiometer to lcd connections.
            * vcc= 5v, gnd=gnd, analog out = A0,    lm35 to arduino connection.

 */ 



#include <avr/io.h>
#define F_CPU 16000000UL
#include "Timer.h"
#include "lcd.h"
#include "uart.h"

#include <util/delay.h> //this delay is used for lcd and uart initialisation 

void adc_init(void)
{
        ADMUX|=(1<<REFS0);
        ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//ENABLING ADC AND SETTING PRESCALAR TO 128
}

uint16_t adc_read(uint8_t channel)
{
        channel&=0x07;//limiting the channel to max 7
        ADMUX  =( ADMUX&0XF8)|channel;//selecting the correct channel
        ADCSRA |=(1<<ADSC); //START CONVERSION
        while(ADCSRA &(1<<ADSC)); //WAIT UNTIL THE CONVERSION FINISHES
        uint16_t value =ADC;
        return ADC;
}


int main(void)
{ 
	//delay working by the timer0 ctc mode
	
        TIMER_CONFIG();
        DELAY_VALUE(); 
        delay_500ms();
// lcd printing 		
        lcd_init();
        adc_init();
        lcd_clear();
        lcd_set_cursor(0,0);
        lcd_print("Temperature:");
//serial monitor 		
		uart_init();

        
         while(1)
        {
	           // code for led blinking for machine status    		
                PORTB|=(1<<PB0); //PB0 IS ON 
                delay_500ms();
                PORTB&=~(1<<PB0);//PB0 IS OFF 
                delay_500ms();
                  
                //code for printing temp in lcd display
               uint16_t  value = adc_read(0);
                float temperature = (value*0.488);
                lcd_set_cursor(1,0);
                lcd_print_float(temperature);
                _delay_ms(1000);
				
				//code for data printing in serial monitor
				char buffer[10];                     // create buffer
				dtostrf(temperature, 5, 2, buffer); // convert float to string
				uart_string("Temp: ");               // optional text
				uart_string(buffer);                 // send temperature
				uart_transmit('\r');                 // carriage return
				uart_transmit('\n');                 // new line
                _delay_ms(1000);
                
        }
}                                                        

