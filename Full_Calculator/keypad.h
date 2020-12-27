/*
 * keypad.h
 *
 *  Created on: ??�/??�/????
 *      Author: Gouda
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"


/* Keypad static configurations */

#define KEYPAD_PORT_DIR DDRA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_OUT PORTA

#define N_COL 4
#define N_ROW 4

/* Function Prototype */

uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
