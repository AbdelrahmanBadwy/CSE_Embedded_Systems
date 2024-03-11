/*
 * Lcd_Keypad_drivers.c
 *
 * Created: 3/10/2024 5:23:53 PM
 * Author : abdal
 */ 

#include <avr/io.h>
#include "LCD/lcd.h"
unsigned char i =0;
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
int main(void)
{
	LCD_INIT();
    /* Replace with your application code */
    while (1) 
    {
		firstCase();
		LCD_clear_screen();
		secendCase();
    }
	
}

