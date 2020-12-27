/*
 * LCD.c
 *
 *  Created on: ??�/??�/????
 *      Author: Gouda
 */

#include "lcd.h"

void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW);
	#if (DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT_DIR |= 0xF0;
		#else
			LCD_DATA_PORT_DIR |= 0x0F;
		#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE);
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
	#elif(DATA_BITS_MODE == 8)
	LCD_DATA_PORT_DIR  = 0xFF;
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);
	#endif

	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_sendCommand(uint8 a_command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_us(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_us(1);
	#if(DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (a_command & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_command & 0xF0) >>4);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);
		_delay_ms(1);
		SET_BIT(LCD_CTRL_PORT,E);
		_delay_us(1);
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((a_command & 0x0F) << 4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (a_command & 0x0F);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);
		_delay_ms(1);
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = a_command;
		_delay_us(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);
		_delay_ms(1);
	#endif
}

void LCD_displayCharacter(const uint8 a_character)
{
	SET_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_us(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_us(1);
	#if(DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (a_character & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_character & 0xF0) >>4);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);
		_delay_ms(1);
		SET_BIT(LCD_CTRL_PORT,E);
		_delay_us(1);
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((a_character & 0x0F) << 4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (a_character & 0x0F);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);
		_delay_ms(1);
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT = a_character;
		_delay_us(1);
		CLEAR_BIT(LCD_CTRL_PORT,E);
		_delay_ms(1);
	#endif
}

void LCD_displayString(uint8 * a_str)
{
	while((*a_str) != '\0')
	{
		LCD_displayCharacter(*a_str);
		a_str++;
	}
}

void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;

	switch(row)
	{
	case 0:
		Address = col;
		break;
	case 1:
		Address = col+0x40;
		break;
	case 2:
		Address = col+0x10;
		break;
	case 3:
		Address = col+0x50;
		break;
	}
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const uint8 * a_str)
{
	LCD_goToRowColumn(row,col);
	LCD_displayString(a_str);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_intgerToString(uint16 data)
{
	char str[16];
	itoa(data,str,10);
	LCD_displayString(str);
}


void LCD_intgerToStringRowCol(uint8 row,uint8 col,uint8 data)
{
	uint8 buff[16];
	itoa(data,buff,10);
	LCD_displayStringRowColumn(row,col,buff);
}
