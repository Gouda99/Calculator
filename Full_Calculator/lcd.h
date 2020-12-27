/*
 * lcd.h
 *
 *  Created on: ??�/??�/????
 *      Author: Gouda
 */

#ifndef LCD_H_
#define LCD_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/* LCD configurations */

#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#undef  UPPER_PORT_PINS
#endif

/* LCD HW pins */

#define RS PB1
#define RW PB2
#define E  PB3
#define LCD_CTRL_PORT_DIR  DDRB
#define LCD_CTRL_PORT      PORTB

#define LCD_DATA_PORT_DIR DDRD
#define LCD_DATA_PORT     PORTD

/* LCD commands */

#define CLEAR_COMMAND               0x01
#define FOUR_BITS_DATA_MODE         0x02
#define TWO_LINE_LCD_Four_BIT_MODE  0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 					0x0C
#define CURSOR_ON				    0x0E
#define SET_CURSOR_LOCATION 		0x80

/* Functions prototype */
void LCD_init(void);
void LCD_sendCommand(uint8 a_command);
void LCD_displayCharacter(const uint8 a_character);
void LCD_displayString(uint8 * a_str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const uint8 * a_str);
void LCD_clearScreen(void);
void LCD_intgerToString(uint16 data);
void LCD_intgerToStringRowCol(uint8 row,uint8 col,uint8 data);
#endif /* LCD_H_ */
