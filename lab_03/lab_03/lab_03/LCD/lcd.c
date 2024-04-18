/*
 ============================================================================
 Name        : lcd.c
 Author      : Abdelrahman_Badawy
 Version     : 3.5
 Copyright   : Your copyright notice
 Description : LCD driver file in C, Ansi-style
 ============================================================================
 */

#include "lcd.h"

void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position<16 && position >=0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW + position);
		}
	}
	else if (line == 2){
		if (position<32 && position >=0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + position);
		}
		
	}
}
void LCD_KICK(){
	LCD_CTRL_PORT &= ~(1<<EN_SWITCH);
	_delay_ms(1);
	LCD_CTRL_PORT |= (1<<EN_SWITCH);
}
void LCD_check_lcd_isbusy(){
	DataDir_LCD_PORT &= ~(0xFF<<DATA_SHIFT);
	LCD_CTRL_PORT |= (1<<RW_SWITCH); //Read Mode
	LCD_CTRL_PORT &= ~(1<<RS_SWITCH); 
	LCD_KICK();
	DataDir_LCD_PORT |= (0xFF<<DATA_SHIFT);
	LCD_CTRL_PORT &= ~(1<<RW_SWITCH);
}
void LCD_clear_screen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}
void LCD_INIT(){
	_delay_ms(20);
	//LCD_check_lcd_isbusy();
	DataDir_LCD_CTRL |= (1<<RW_SWITCH) | (1<<RS_SWITCH) | (1<<EN_SWITCH) ;
	LCD_CTRL_PORT &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH) | (1<<EN_SWITCH));
	DataDir_LCD_PORT = 0xFF;
	_delay_ms(15);
	LCD_clear_screen();
	#ifdef EIGHT_BIT_MODE
		LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif //EIGHT_BIT_MODE
	#ifdef FOUR_BIT_MODE
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif //FOUR_BIT_MODE
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_WRITE_COMMAND(unsigned char command){
	//LCD_check_lcd_isbusy();
	_delay_ms(20);
	#ifdef EIGHT_BIT_MODE
		LCD_PORT = command;
		LCD_CTRL_PORT &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
		LCD_KICK();
	#endif //EIGHT_BIT_MODE
	#ifdef FOUR_BIT_MODE
		//LCD_check_lcd_isbusy();
		LCD_PORT &= (LCD_PORT & 0x87);
		LCD_PORT |= ((LCD_PORT & 0x87) | (command & 0xF0)>>1);
		LCD_CTRL_PORT &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
		LCD_KICK();
		LCD_PORT &= (LCD_PORT & 0x87);
		LCD_PORT |= ((LCD_PORT & 0x87) | (command << 3));
		LCD_CTRL_PORT &= ~((1<<RW_SWITCH) | (1<<RS_SWITCH));
		LCD_KICK();
	#endif //FOUR_BIT_MODE
}

void LCD_WRITE_CHAR(unsigned char character){
	_delay_ms(20);
	#ifdef EIGHT_BIT_MODE
	LCD_PORT = character;
	LCD_CTRL_PORT &= ~(1<<RW_SWITCH) ;
	LCD_CTRL_PORT |= (1<<RS_SWITCH);
	LCD_KICK();
	
	
	#endif //EIGHT_BIT_MODE
	#ifdef FOUR_BIT_MODE
	LCD_PORT &= (LCD_PORT & 0x87);
	LCD_PORT |= ((LCD_PORT & 0x87) | (character & 0xF0)>>1);
	LCD_CTRL_PORT &= ~(1<<RW_SWITCH) ;
	LCD_CTRL_PORT |= (1<<RS_SWITCH);
	LCD_KICK();
	LCD_PORT &= (LCD_PORT & 0x87);
	LCD_PORT |= ((LCD_PORT & 0x87) | (character << 3));
	LCD_CTRL_PORT &= ~(1<<RW_SWITCH) ;
	LCD_CTRL_PORT |= (1<<RS_SWITCH);
	LCD_KICK();
	#endif //FOUR_BIT_MODE
	
	
	
}
void LCD_WRITE_STRING(char* data){
	unsigned char count =0;
	while(*data >0){
		count++;
		LCD_WRITE_CHAR(*data++);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		} 
		else if(count ==32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);

		}
	}
	
}