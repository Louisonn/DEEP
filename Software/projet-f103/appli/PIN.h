/*
 * PIN.h
 *
 *  Created on: 8 janv. 2022
 *      Author: porta
 */

#ifndef PIN_H_
#define PIN_H_
#include "macro_types.h"

void pinInit(void);
bool_e pinAdd(int * newPin);
bool_e pinUse(int * newPin);

#endif /* PIN_H_ */
