/*
 * program.c
 *
 *  Created on: ??�/??�/????
 *      Author: Gouda
 */

#include "lcd.h"
#include "keypad.h"

uint16 firstNum = 0,secondNum = 0;
uint8 op;
uint8 key;
uint16 result = 0;

int main(void)
{
	LCD_init();

	while(1)
	{
		key = KEYPAD_getPressedKey();
		while((key >= 0) && (key <= 9))
		{
			LCD_intgerToString(key);
			firstNum = key + firstNum * 10;
			_delay_ms(300);
			key = KEYPAD_getPressedKey();
		}
		LCD_displayCharacter(key);
		op = key;
		_delay_ms(300);
		key = KEYPAD_getPressedKey();
		while((key >= 0) && (key <= 9))
		{
			LCD_intgerToString(key);
			secondNum = key + secondNum * 10;
			_delay_ms(300);
			key = KEYPAD_getPressedKey();
		}
		LCD_displayCharacter(key);
		_delay_ms(300);
		switch(op)
		{
		case '+' : result = firstNum + secondNum;
		break;
		case '-' : result = firstNum - secondNum;
		break;
		case '/' : result = firstNum / secondNum;
		break;
		case '*' : result = firstNum * secondNum;
		break;
		}
		LCD_intgerToString(result);
		firstNum = 0;
		secondNum = 0;
		key = 0;
		result = 0;
		if((KEYPAD_getPressedKey()) == 13)
		{
			LCD_clearScreen();
		}
		_delay_ms(300);
	}
}
