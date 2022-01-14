/*
 * PIN.c
 *
 *  Created on: 8 janv. 2022
 *      Author: Louison
 */

#include "PIN.h"

#define PIN_MAX_NUMBER	2
#define DEFAULT_PIN_CODE {0, 0, 0, 0}


static int8_t* pins[PIN_MAX_NUMBER];
int8_t tableau[2] = {0};




void pinInit(void){
	int8_t default_pin_code[] = DEFAULT_PIN_CODE;
	pinAdd(default_pin_code);

}

bool_e pinAdd(int8_t * newPin){
	uint8_t i;
	for(i = 0; i<PIN_MAX_NUMBER; i++)
		{
			if(!pins[i])	//On a trouv� une place libre ?
			{
				pins[i] = newPin;
				return TRUE;
			}
		}
		return FALSE;	//Pas de place libre !

}

bool_e pinUse(int8_t * pin){
	uint8_t i;
	for(i = 0; i<PIN_MAX_NUMBER; i++)
		{
		uint8_t matches = 0;
			for (uint8_t y = 0; y<4; y++){
				if(pin[y] == pins[i][y]){
					matches++;
				}
			}
		if(matches == 4){
			return TRUE;
		}
		}
		return FALSE;	//Pas de place libre !
}



