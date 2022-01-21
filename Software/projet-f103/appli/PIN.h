/*
 * PIN.h
 *
 *  Created on: 8 janv. 2022
 *      Author: Louison
 */

#ifndef PIN_H_
#define PIN_H_
#include "macro_types.h"



void pinInit(void);
bool_e pinAdd(int8_t *);
bool_e pinUse(int8_t *);

#endif /* PIN_H_ */
