/*
 * button.h
 *
 *  Created on: 14 janv. 2022
 *      Author: Louison
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include "macro_types.h"


#define NUMBER_BUTTONS 11


typedef struct{
	bool_e NOBUTTON;
	bool_e CANCELBUTTON;
	int8_t BUTTONVALUE;
}button_state_t;

typedef struct {
	button_state_t button;
	uint16_t x1;		//top left
	uint16_t y1; 	//top left
	uint16_t x2; 	//bottom right
	uint16_t y2; 	//bottom right
} button_graphic_t;



button_state_t buttonFinder(int16_t, int16_t);



button_graphic_t getButton(uint8_t);


#endif /* BUTTON_H_ */
