/*
 * button.c
 *
 *  Created on: 14 janv. 2022
 *      Author: Louison
 */

#include "button.h"





//Tableau de boutons
//		NOBUTTON		CANCEL		VALUE	X1		Y1		X2		Y2
static button_graphic_t buttons[NUMBER_BUTTONS] = {
		{{FALSE,		FALSE,		0},		80,		240,	160,	320},
		{{FALSE,		FALSE,		1},		0,		160,	80,		240},
		{{FALSE,		FALSE,		2},		80,		160,	160,	240},
		{{FALSE,		FALSE,		3},		160,	160,	240,	240},
		{{FALSE,		FALSE,		4},		0,		80,		80,		160},
		{{FALSE,		FALSE,		5},		80,		80,		160,	160},
		{{FALSE,		FALSE,		6},		160,	80,		240,	160},
		{{FALSE,		FALSE,		7},		0,		0,		80,		80},
		{{FALSE,		FALSE,		8},		80,		0,		160,	80},
		{{FALSE,		FALSE,		9},		160,	0,		240,	80},
		{{FALSE,		TRUE,		0},		0,		240,	80,		320}};

//
static button_graphic_t noButton = { { TRUE, FALSE, 0 }, 0, 0, 0, 0 };

/*
 * @brief	Associe un bouton aux coordonnées données
 * @param	coordonnées de l'appui
 * @return	le bouton correspondant aux coordonnées
 */
button_state_t buttonFinder(int16_t x, int16_t y) {
	uint8_t i;
	for (i = 0; i < NUMBER_BUTTONS; i++) {
		if (x > buttons[i].x1 && x < buttons[i].x2 && y > buttons[i].y1
				&& y < buttons[i].y2) {
			return buttons[i].button;
		}
	}
	return noButton.button;
}


/*
 * @brief	accesseur de bouton
 * @param	index du bouton voulu
 * @return	{@button_graphic_t} correspondant à l'index
 */
button_graphic_t getButton(uint8_t i){
	return buttons[i];
}





