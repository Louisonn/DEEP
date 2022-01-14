/*
 * button.c
 *
 *  Created on: 14 janv. 2022
 *      Author: Louison
 */

#include "button.h"

#define NUMBER_BUTTONS 11

button_state_t buttonFinder(int16_t, int16_t);

typedef struct{
	button_state_t button;
	int16_t x1;		//top left
	int16_t y1; 	//top left
	int16_t x2; 	//bottom right
	int16_t y2; 	//bottom right
}button_graphic_t;

//Tableau de boutons
static button_graphic_t buttons[NUMBER_BUTTONS] ={
		{{FALSE,		FALSE,		FALSE,		0},		80,		240,	160,	320},
		{{FALSE,		FALSE,		FALSE,		1},		0,		160,	80,		240},
		{{FALSE,		FALSE,		FALSE,		2},		80,		160,	160,	240},
		{{FALSE,		FALSE,		FALSE,		3},		160,	160,	240,	240},
		{{FALSE,		FALSE,		FALSE,		4},		0,		80,		80,		160},
		{{FALSE,		FALSE,		FALSE,		5},		80,		80,		160,	160},
		{{FALSE,		FALSE,		FALSE,		6},		160,	80,		240,	160},
		{{FALSE,		FALSE,		FALSE,		7},		0,		0,		80,		80},
		{{FALSE,		FALSE,		FALSE,		8},		80,		0,		160,	80},
		{{FALSE,		FALSE,		FALSE,		9},		160,	0,		240,	80},
		{{FALSE,	FALSE,		TRUE,		0},		0,		240,	80,		320}
	};

//
static button_graphic_t noButton ={{TRUE,FALSE,FALSE,0},0,0,0,0};








button_state_t buttonFinder(int16_t x, int16_t y){
	uint8_t i;
	for(i = 0; i < NUMBER_BUTTONS; i++){
		if(x > buttons[i].x1 && x < buttons[i].x2 && y > buttons[i].y1 && y < buttons[i].y2){
			return buttons[i].button;
		}
	}
	return noButton.button;
}





