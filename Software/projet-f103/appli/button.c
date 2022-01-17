/*
 * button.c
 *
 *  Created on: 14 janv. 2022
 *      Author: Louison
 */

#include "button.h"

#define NUMBER_BUTTONS 11

typedef struct {
	button_state_t button;
	uint16_t x1;		//top left
	uint16_t y1; 	//top left
	uint16_t x2; 	//bottom right
	uint16_t y2; 	//bottom right
} button_graphic_t;

//Tableau de boutons
//		NOBUTTON		CANCEL		VALUE	X1		Y1		X2		Y2
static button_graphic_t buttons[NUMBER_BUTTONS] = { { { FALSE, FALSE, 0 }, 80,
		240, 160, 320 }, { { FALSE, FALSE, 1 }, 0, 160, 80, 240 }, { { FALSE,
		FALSE, 2 }, 80, 160, 160, 240 }, { { FALSE, FALSE, 3 }, 160, 160, 240,
		240 }, { { FALSE, FALSE, 4 }, 0, 80, 80, 160 }, { { FALSE, FALSE, 5 },
		80, 80, 160, 160 }, { { FALSE, FALSE, 6 }, 160, 80, 240, 160 }, { {
		FALSE, FALSE, 7 }, 0, 0, 80, 80 },
		{ { FALSE, FALSE, 8 }, 80, 0, 160, 80 }, { { FALSE, FALSE, 9 }, 160, 0,
				240, 80 }, { { FALSE, TRUE, 0 }, 0, 240, 80, 320 } };

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

void displayUNLOCKED() {
	ILI9341_Fill(ILI9341_COLOR_GREEN);
}

void displaySETPIN() {
	ILI9341_Fill(ILI9341_COLOR_WHITE);
	uint8_t i;
	for (i = 0; i < NUMBER_BUTTONS; i++) {
		ILI9341_DrawRectangle(buttons[i].x1, buttons[i].y1, buttons[i].x2,
				buttons[i].y2, ILI9341_COLOR_BLACK);
		uint16_t x = (uint16_t) (buttons[i].x1 + 40);
		uint16_t y = (uint16_t) (buttons[i].y1 + 40);
		ILI9341_Putc(x, y, (char) (buttons[i].button.BUTTONVALUE + 48),
				&Font_7x10, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
	}
}

void displayLOCKED() {
	ILI9341_Fill(ILI9341_COLOR_RED);
	uint8_t i;
	for (i = 0; i < 4; i++) {
		char c = (char) (screenGetPin()[i] + 48);
		ILI9341_Putc((uint16_t) (10 + 7 * i), 10, c, &Font_11x18,
		ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
	}


/*
	for (int8_t i = 0; i < 4; i++) {
		char c = (char) (newPin[i] + 48);
		ILI9341_Putc((uint16_t) (10 + 7 * i), 10, c, &Font_11x18,
		ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
	}*/



}

void displayENTERPIN() {
	ILI9341_Fill(ILI9341_COLOR_WHITE);
	uint8_t i;
	for (i = 0; i < NUMBER_BUTTONS; i++) {
		ILI9341_DrawRectangle(buttons[i].x1, buttons[i].y1, buttons[i].x2,
				buttons[i].y2, ILI9341_COLOR_BLACK);
		uint16_t x = (uint16_t) (buttons[i].x1 + 40);
		uint16_t y = (uint16_t) (buttons[i].y1 + 40);
		if (buttons[i].button.CANCELBUTTON == TRUE) {
			ILI9341_Puts((uint16_t)(x - 10), y, "CANCEL", &Font_7x10, ILI9341_COLOR_BLUE,
					ILI9341_COLOR_WHITE);
		} else {
			ILI9341_Putc(x, y, (char) (buttons[i].button.BUTTONVALUE + 48),
					&Font_7x10, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);

		}
	}
}

