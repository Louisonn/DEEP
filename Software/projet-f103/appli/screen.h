/*
 * screen.h
 *
 *  Created on: 12 janv. 2022
 *      Author: Louison
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include "macro_types.h"
#include "tft_ili9341/stm32f1_ili9341.h"
#include "tft_ili9341/stm32f1_xpt2046.h"
#include "button.h"

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



void screenInit(void);
void screenCheck(screen_mode_e);
screen_event_e screenMain(screen_mode_e, bool_e);
int8_t * screenGetPin(void);

#endif /* SCREEN_H_ */
