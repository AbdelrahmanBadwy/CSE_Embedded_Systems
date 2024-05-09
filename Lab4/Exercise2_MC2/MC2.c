/*
 ================================================================================================
 Name        : MC2.c
 Author      : Mohamed Tarek
 Description : MC2 Code in Exercise2
 Date        : 4/11/2014
 ================================================================================================
 */

#include "spi.h"
#include "lcd.h"

#define MC2_READY 0x10

int main(void)
{
	uint8 str[20];

	/* Initialize the LCD Driver */
	LCD_init();

	/* Initialize the SPI driver as Slave */
	SPI_initSlave();

	/* Receive String from MC1 */
	SPI_receiveString(str);

	/* Display the received string on the LCD display */
	LCD_displayString(str);

    while(1)
    {

    }
}

