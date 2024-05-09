/*
 ================================================================================================
 Name        : MC2.c
 Author      : Mohamed Tarek
 Description : MC2 Code in Exercise3
 Date        : 19/9/2014
 ================================================================================================
 */ 

#include "uart.h"
#include "lcd.h"

#define MC2_READY 0x10

int main(void)
{

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	UART_init(9600);

	/* Initialize the LCD Driver */
	LCD_init();

			/* Send MC2_READY byte to MC1 to ask it to send the string */
			UART_sendByte(MC2_READY);

			/* Receive String from MC1 through UART */
			//UART_receiveString(Str);

			/* Display the received string on the LCD display */
			LCD_displayString(" Value C = ");
		while(1){
			char recieved_data=UART_recieveByte();
			LCD_moveCursor(1,0);
			LCD_intgerToString(recieved_data);

		}
}
