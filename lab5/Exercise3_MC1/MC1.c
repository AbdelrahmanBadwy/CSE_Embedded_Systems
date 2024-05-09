/*
 ================================================================================================
 Name        : MC1.c
 Author      : Mohamed Tarek
 Description : MC1 Code in Exercise3
 Date        : 19/9/2014
 ================================================================================================
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include <util/delay.h>

#define MC2_READY 0x10



char c=64;


/* External INT0 enable and configuration function */
void INT0_Init(void)
{
	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
	MCUCR |=  (1<<ISC01);   // Trigger INT0 with the FALLING edge ***** theses sequance should be as follow bec
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0 ***** if the MCUCR came after GICR it will give
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit  ***** interrupt by defulat as it assumed that u are
}int main(void)
{
	UART_init(9600);
	DDRC|=1<<0|1<<1;
	PORTC|=1<<0;
	while(UART_recieveByte() != MC2_READY){}


	INT0_Init();
		sei();
		/*
	DDRD &= ~(1<<2);  // Configure pin 2 in PORTD as input pin

		DDRC |= (1<<1);   // Configure pin 1 in PORTC as output pin
		PORTC &= ~(1<<1); // Set pin 1 in PORTC with value 0 at the beginning(LED OFF)
		//PORTD|=1<<2;
		while(1)
		{

			if(!(PIND & (1<<2)))       // check if the push button at PD2 is pressed or not
			{_delay_ms(80);
			if(!(PIND & (1<<2))) {
				PORTC |= (1<<1);       // Set pin 1 in PORTC with value 1 (LED ON)
			}}
			else
			{
				PORTC &= ~(1<<1);      // Set pin 1 in PORTC with value 0 (LED OFF)
			}
		}
*/
	while(1);
}
ISR(INT0_vect)
{

	PORTC^=1<<1;
	c++;
	UART_sendByte(c);
	if(c==122){
		c=64;
	}
	while(!(PIND&(1<<2)));
}
