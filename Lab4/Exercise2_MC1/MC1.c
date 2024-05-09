/*
 ================================================================================================
 Name        : MC1.c
 Author      : Mohamed Tarek
 Description : MC1 Code in Exercise2
 Date        : 4/11/2014
 ================================================================================================
 */

#include "spi.h"
#include <util/delay.h> /* To use the delay functions */
#include <avr/io.h>
#include <avr/interrupt.h>
void INT0_Init(void)
{
	DDRD  &= (~(1<<PD2));               // Configure INT0/PD2 as input pin
	MCUCR |= (1<<ISC00) | (1<<ISC01);   // Trigger INT0 with the raising edge ***** theses sequance should be as follow bec
	GICR  |= (1<<INT0);                 // Enable external interrupt pin INT0 ***** if the MCUCR came after GICR it will give
	SREG  |= (1<<7);                    // Enable interrupts by setting I-bit  ***** interrupt by defulat as it assumed that u are
}

ISR(INT0_vect)
{
	/* Send the string to MC2 */
	SPI_sendString("I am Micro1#");

}
int main(void)
{
	INT0_Init();
	/* Initialize the SPI driver as Master */
	SPI_initMaster();

	/* Delay until MC2 finish its initialization task */
	_delay_ms(100);

    while(1)
    {

    }
}


