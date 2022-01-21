/*
 * sensor.h
 *
 *  Created on: 20 janv. 2022
 *      Author: Louison
 */

#ifndef SENSOR_H_
#define SENSOR_H_
#include "macro_types.h"
#include "stm32f1_adc.h"

int16_t test(void);
bool_e getAlcoholLevel(void);
void sensorInit(void);


#endif /* SENSOR_H_ */
