/*
 ============================================================================
 Name        : lab_03.c
 Author      : Abdelrahman_Badawy
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : main file in C, Ansi-style
 ============================================================================
 */
#include <avr/io.h>
#include "LCD/lcd.h"
#include  <util/delay.h>
#include <avr/interrupt.h>
int i;
void firstCase(){
	for (i =0 ; i<6 ; i++)
	{
		LCD_clear_screen();
		LCD_GOTO_XY(1,i);
		LCD_WRITE_STRING("HELLO");
		_delay_ms(1000);
	}
}
void  secendCase(){
	for (i =4 ; i>0 ; i--)
	{
		LCD_clear_screen();
		LCD_GOTO_XY(1,i);
		LCD_WRITE_STRING("HELLO");
		_delay_ms(1000);
	}
}

void adc_init()
{
	ADMUX |= (1<<REFS1) | (1<<REFS0); //internal ref ,enable adc 0
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) |(1<<ADIE); // en adc, prescalar = 128
}

void INT_EN()
{
	MCUCR |= (1<<ISC01); //falling edge
	GICR  |= (1<<INT0); //En int0
	
}

int main(void)
{
	DDRD &= ~(1<<2); //pD2 input
	adc_init();
	INT_EN();
	LCD_INIT();
	LCD_clear_screen();
	_delay_ms(50);
	sei();
    while (1) 
    {
          firstCase();
          LCD_clear_screen();
          secendCase();
		
    }
}

ISR(INT0_vect)
{
	char num[5];
	int adc_value;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA&(1<<ADSC)); //still converting 
	adc_value = ADCW;
	itoa(adc_value, num, 10);
	LCD_clear_screen();
	_delay_ms(250);
	//LCD_vidSendNumber(adc_value);
	LCD_WRITE_STRING("ADC = ");
	LCD_WRITE_STRING(num);
	_delay_ms(2000);
}

