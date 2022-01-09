/*
 * PIN.c
 *
 *  Created on: 8 janv. 2022
 *      Author: porta
 */

#include "PIN.h"

#define PIN_MAX_NUMBER	2
#define DEFAULT_PIN_CODE {0, 0, 0, 0}


static int* pins[PIN_MAX_NUMBER];


typedef struct
{
	int a;
}myStruct;
uint32_t


void PIN_init(){
	int default_pin_code[] = DEFAULT_PIN_CODE;
	PIN_add(default_pin_code);

}

bool_e PIN_add(int * newPin){
	uint8_t i;
	for(i = 0; i<PIN_MAX_NUMBER; i++)
		{
			if(!pins[i])	//On a trouvé une place libre ?
			{
				pins[i] = newPin;
				return TRUE;
			}
		}
		return FALSE;	//Pas de place libre !

}



