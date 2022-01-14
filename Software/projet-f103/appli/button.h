/*
 * button.h
 *
 *  Created on: 14 janv. 2022
 *      Author: Louison
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include "macro_types.h"

typedef struct{
	bool_e NOBUTTON;
	bool_e FULLSCREEN;
	bool_e CANCELBUTTON;
	int8_t BUTTONVALUE;
}button_state_t;



void buttonInit(void);

button_state_t getButtonState(void);




#endif /* BUTTON_H_ */
