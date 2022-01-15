/*
 * screen.c
 *
 *  Created on: 12 janv. 2022
 *      Author: Louison
 */

#include "screen.h"



int16_t x, y;
int8_t actualPin[4] = {0};
bool_e isTouched = FALSE;
bool_e isCancelled = FALSE;
uint8_t actualPinIndex = 0;



void screenInit(){
	ILI9341_Init();
	ILI9341_Rotate(ILI9341_Orientation_Portrait_2);
	ILI9341_Fill(ILI9341_COLOR_GREEN);
}


screen_event_e screenMain(screen_mode_e state, bool_e entrance){

	switch(state){
	case UNLOCKED:
		if(entrance){
			//on unlock le verrou
			//et on affiche le menu locked
		}
		if(isTouched){
			return TOUCHED;
		}
		break;
	case SETPIN:
		if(entrance){
			//affichage setpin menu
		}
		if(actualPinIndex == 4){
			return NEWPIN;
		}
		break;
	default:
		return NOTHING;
		break;
	}
	return NOTHING;



}


void screenCheck(screen_mode_e state){
	isTouched = FALSE;
	isCancelled = FALSE;
	if(XPT2046_getMedianCoordinates(&x, &y, XPT2046_COORDINATE_SCREEN_RELATIVE)){
		switch(state){
		case UNLOCKED:
			isTouched = TRUE;
			break;
		case SETPIN:
		{
			button_state_t newButton = buttonFinder(x, y);
			if(newButton.CANCELBUTTON){
				isCancelled = TRUE;
			}
			else if(newButton.NOBUTTON){
				break;
			}
			else if(actualPinIndex < 4){
				actualPin[actualPinIndex] = newButton.BUTTONVALUE;
				actualPinIndex++;
			}
		}
			break;
		default:
			break;
		}
	}
}


int8_t * screenGetPin(){
	return actualPin;
}



//PARTIE AFFICHAGE


void displayScreen(screen_mode_e state){

	switch(state){
	case UNLOCKED:
		displayUNLOCKED();
		break;
	case SETPIN:
		displaySETPIN();
		break;
	case LOCKED:
		displayLOCKED();
		break;
	case ENTERPIN:
		displayENTERPIN();
		break;
	default:
		break;
	}
}





