/*
 * PIN.h
 *
 *  Created on: 8 janv. 2022
 *      Author: Louison
 */

#ifndef PIN_H_
#define PIN_H_
#include "macro_types.h"

#define PIN_MAX_NUMBER	2


void pinInit(int8_t **);
bool_e pinAdd(int8_t * , int8_t * pins[]);
bool_e pinUse(int8_t * , int8_t * pins[]);

#endif /* PIN_H_ */
