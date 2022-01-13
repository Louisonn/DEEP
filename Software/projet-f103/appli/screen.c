/*
 * screen.c
 *
 *  Created on: 12 janv. 2022
 *      Author: Louison
 */

#include "screen.h"

screen_event_e screenMain(screen_mode_e mode){
	if(mode)
	{
		return TOUCHED;
	}
	return TOUCHED;
}


int * screenGetPin(){
	return 0;
}
