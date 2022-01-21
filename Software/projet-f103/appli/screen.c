/*
 * screen.c
 *
 *  Created on: 12 janv. 2022
 *      Author: Louison
 */

#include "screen.h"




int8_t actualPin[4] = {0};
bool_e isTouched = FALSE;
bool_e isCancelled = FALSE;
uint8_t actualPinIndex = 0;


/*
 * @brief	initialisation de l'écran
 */
void screenInit(){
	ILI9341_Init();
	ILI9341_Rotate(ILI9341_Orientation_Portrait_2);
	ILI9341_Fill(ILI9341_COLOR_GREEN);

	XPT2046_init();
}

/*
 * @brief	passerelle entre la détection d'appui et le main
 * @param	état actuel
 * @param	true si on vient de changer d'état
 * @return	l'action réalisé par l'appui
 */
screen_event_e screenMain(screen_mode_e state, bool_e entrance){

	switch(state){
	case UNLOCKED:
		if(entrance){
			//on unlock le verrou
			displayUNLOCKED();
		}
		if(isTouched){
			return TOUCHED;
		}
		break;
	case SETPIN:
		if(entrance){
			displaySETPIN();
		}
		if(actualPinIndex == 4){
			return NEWPIN;
		}
		else if(isCancelled){
			return CANCEL;
		}
		break;
	case LOCKED:
		if(entrance){
			//on lock le verrou
			displayLOCKED();
		}
		if(isTouched){
			return TOUCHED;
		}
		break;
	case ENTERPIN:
		if(entrance){
			displayENTERPIN();
		}
		if(actualPinIndex == 4){
			return NEWPIN;
		}
		else if(isCancelled){
			return CANCEL;
		}
		break;
	default:
		break;
	}
	return NOTHING;



}

/*
 * @brief verifie si appui sur l'écran, et modifie les variables en conséquence
 * @param état actuel du système
 * @param pointeur sur le temps, permet d'eviter 2 appui trop rapidedement
 */
void screenCheck(screen_mode_e state,uint32_t * pt ){
	int16_t x, y;
	isTouched = FALSE;
	isCancelled = FALSE;
	if(XPT2046_getMedianCoordinates(&x, &y, XPT2046_COORDINATE_SCREEN_RELATIVE) && !*pt){
		switch(state){
		case UNLOCKED:
			isTouched = TRUE;
			break;
		case LOCKED:
			isTouched = TRUE;
			break;
		default: // Here is for ENTER/SET PIN (AND INIT BUT NORMALEMENT NEVER)
		{
			button_state_t newButton = buttonFinder(x, y);
			if(newButton.CANCELBUTTON){
				isCancelled = TRUE;
				actualPinIndex = 0;
			}
			else if(newButton.NOBUTTON){
				break;
			}
			else if(actualPinIndex < 4){
				actualPin[actualPinIndex] = newButton.BUTTONVALUE;
				actualPinIndex++;

			}
		}
			break;
		}
		*pt = 500;
	}
}


int8_t * screenGetPin(){
	actualPinIndex = 0;
	return actualPin;
}



//----------PARTIE AFFICHAGE -----------------------------------------

/*
 * @brief appel fonction d'affichage correspondant a l'état actuel
 * @param état du système actuel
 */
void displayScreen(screen_mode_e state){

	switch(state){
	case UNLOCKED:
		displayUNLOCKED();
		break;
	case SETPIN:
		displaySETPIN();
		break;
	case LOCKED:
		displayLOCKED();
		break;
	case ENTERPIN:
		displayENTERPIN();
		break;
	default:
		break;
	}
}





void displayUNLOCKED() {
	ILI9341_Fill(ILI9341_COLOR_GREEN);
	ILI9341_Puts(87, 151, "FREE", &Font_11x18, ILI9341_COLOR_BLUE,
			ILI9341_COLOR_GREEN);
}

void displaySETPIN() {
	ILI9341_Fill(ILI9341_COLOR_WHITE);

	uint8_t i;
	for (i = 0; i < NUMBER_BUTTONS; i++) {
		button_graphic_t button = getButton(i);
		ILI9341_DrawRectangle(button.x1, button.y1, button.x2,
				button.y2, ILI9341_COLOR_BLACK);

		uint16_t x = (uint16_t) (button.x1 + 35);
		uint16_t y = (uint16_t) (button.y1 + 31);
		if (button.button.CANCELBUTTON == TRUE)
		{
			ILI9341_Puts((uint16_t) (x - 33), y, "CANCEL", &Font_11x18,
					ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
		} else
		{
			ILI9341_Putc(x, y, (char) (button.button.BUTTONVALUE + 48),
					&Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);

		}
	}
}

void displayLOCKED() {
	ILI9341_Fill(ILI9341_COLOR_RED);

	uint8_t i;
	for (i = 0; i < 4; i++)
	{
		char c = (char) (screenGetPin()[i] + 48);
		ILI9341_Putc((uint16_t) (153 + 11 * i), 10, c, &Font_11x18,
		ILI9341_COLOR_BLUE, ILI9341_COLOR_RED);
	}

	ILI9341_Puts(10, 10, "You entered:", &Font_11x18, ILI9341_COLOR_BLUE,
			ILI9341_COLOR_RED);
	ILI9341_Puts(87, 151, "LOCKED", &Font_11x18, ILI9341_COLOR_BLUE,
			ILI9341_COLOR_RED);
}

void displayENTERPIN() {
	ILI9341_Fill(ILI9341_COLOR_WHITE);
	uint8_t i;
	for (i = 0; i < NUMBER_BUTTONS; i++) {
		button_graphic_t button = getButton(i);

		ILI9341_DrawRectangle(button.x1, button.y1, button.x2,
				button.y2, ILI9341_COLOR_BLACK);
		uint16_t x = (uint16_t) (button.x1 + 35);
		uint16_t y = (uint16_t) (button.y1 + 31);

		if (button.button.CANCELBUTTON == TRUE)
		{
			ILI9341_Puts((uint16_t) (x - 33), y, "CANCEL", &Font_11x18,
					ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
		} else
		{
			ILI9341_Putc(x, y, (char) (button.button.BUTTONVALUE + 48),
					&Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);

		}
	}
}




