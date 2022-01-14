/*
 * screen.h
 *
 *  Created on: 12 janv. 2022
 *      Author: Louison
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include "macro_types.h"

#include "PIN.h"

typedef enum
{
	NOTHING = 0,
	TOUCHED,
	CANCEL,
	NEWPIN
}screen_event_e;

typedef enum
{
	INIT = 0,
	UNLOCKED,
	SETPIN,
	LOCKED,
	ENTERPIN
}screen_mode_e;




screen_event_e screenMain(screen_mode_e, bool_e);

void screenCheck(void);

bool_e screenGetPin(int8_t *);

#endif /* SCREEN_H_ */
