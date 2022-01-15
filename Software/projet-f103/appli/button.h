/*
 * button.h
 *
 *  Created on: 14 janv. 2022
 *      Author: Louison
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include "macro_types.h"
#include "tft_ili9341/stm32f1_ili9341.h"

typedef struct{
	bool_e NOBUTTON;
	bool_e CANCELBUTTON;
	int8_t BUTTONVALUE;
}button_state_t;



void buttonInit(void);

button_state_t buttonFinder(int16_t, int16_t);

void displayUNLOCKED(void);
void displaySETPIN(void);
void displayLOCKED(void);
void displayENTERPIN(void);


#endif /* BUTTON_H_ */
