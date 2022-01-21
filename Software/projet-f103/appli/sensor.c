/*
 * sensor.c
 *
 *  Created on: 20 janv. 2022
 *      Author: Louison
 */

#include "sensor.h"

#define BoireOuConduireIlFautChoisir 1


#if BoireOuConduireIlFautChoisir
	#define AlcoholLimit 0.25
#endif


void sensorInit(){
	ADC_init();
}



int16_t test(){
	return ADC_getValue(ADC_0);

}

