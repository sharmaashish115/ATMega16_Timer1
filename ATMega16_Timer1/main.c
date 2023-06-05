/*
 * ATMega16_Timer1.c
 *
 * Created: 2023-06-05 6:41:57 PM
 * Author : a_shi
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
    DDRD |= (1<<6);		//PD6 OUTPUT (LED), PD6 Pin can act as an Input Capture Pin for Timer/Counter 1.
	
	TCCR1B|= (1<<CS12);	
	TCCR1B &= (~(1<<CS11)) & (~(1<<CS10));		//Set the Clock Source, 256 prescaler. 
	TCNT1 = 34285;		//Load the timer for every half second delay. 
	
	/* Timer Calculation
	
	Clock Source -> 8MHz external crystal.
	Use Prescaler 256.
	
	Clock freq -> 8000000/256 = 31250Hz
	
	To blink an LED at 2Hz i.e. 0.5sec = 500msec (1000msec in 1sec)
	
	Time period = 1/31250 = 0.000032sec = 32microsec
	
	To elapse 32 microseconds, it takes 1 count
	So, to elapse 1 microseconds, it takes 1/32count
	So, to elapse 500 microseconds, it takes {(1/32)*500} = 15625 count
	
	Timer 1 is a 16 bit counter. So, 0, 1, -> 65535 and then overflows.
	
	65535 - 15625 = 49910.
	
	If we load the Timer Counter with 49910 
	then from 49910 -> 65535, it will take 500msec delay.
	
	https://www.easycalculation.com/engineering/electrical/avr-timer-calculator.php Use this for AVR Timer Counter calculation
	
	For 1 sec delay 65535 - 31250 = 34285 count.
	
	*/
	
	TIMSK |= (1<<TOIE1);		//Timer/Counter1, Overflow Interrupt Enable.
	
	sei();						//Enable Global Interrupt. 
	
    while (1) 
    {
		
    }	
}

ISR (TIMER1_OVF_vect)
{
	PORTD ^= (1<<6);
	TCNT1 = 34285;
}
