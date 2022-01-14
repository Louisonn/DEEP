/*
 * screen.c
 *
 *  Created on: 12 janv. 2022
 *      Author: Louison
 */

#include "screen.h"




int8_t actualPin[4] = {-1,-1,-1,-1};
bool_e isTouched = FALSE;
bool_e newPinAvailable = FALSE;
bool_e isCancelled = FALSE;


screen_event_e screenMain(screen_mode_e state, bool_e entrance){

	(void)entrance;

	switch(state){
	case UNLOCKED:
		if(entrance){
			//on unlock le verrou
		}
		if(isTouched){
			return TOUCHED;
		}
		break;
	case SETPIN:
		if(entrance){
			//affichage setpin menu
		}
		if(newPinAvailable){
			return NEWPIN;
		}
		break;
	default:
		return NOTHING;
		break;
	}
	return NOTHING;



}

void screenCheck(){

	if(1){

	}
}


bool_e screenGetPin(int8_t * newPin){
	for (uint8_t i = 0; i < 4; i++){
		if(actualPin[i] == -1){
			return FALSE;
		}
		else{
			newPin[i] = actualPin[i];
		}
	}
	return TRUE;
}
