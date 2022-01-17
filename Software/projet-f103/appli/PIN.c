/*
 * PIN.c
 *
 *  Created on: 8 janv. 2022
 *      Author: Louison
 */

#include "PIN.h"

#include "tft_ili9341/stm32f1_ili9341.h"


#define DEFAULT_PIN_CODE {0, 0, 0, 0}


/*
 * @brief	initialisation des saves des pins
 */
void pinInit(int8_t * pins[]) {
	int8_t default_pin_code[4] = DEFAULT_PIN_CODE;
	pinAdd(default_pin_code, pins);

}

/*
 * @brief	ajoute le pin au tableau de saves si il y a de la place
 * @param	pointeur sur le tableau du pin a ajouté
 * @return	true si le pin est bien ajouté
 */
bool_e pinAdd(int8_t * newPin, int8_t *pins[]) {


	uint16_t i;
	int8_t addedPin[4] = {0};
	for (i = 0; i < 4; i++) {
		addedPin[i] = newPin[i];
	}

	for (i = 0; i < PIN_MAX_NUMBER; i++) {
		if (!pins[i])	//On a trouvï¿½ une place libre ?
		{
			pins[i] = addedPin;


			return TRUE;
		}
	}
	return FALSE;	//Pas de place libre !


}

/*
 * @brief	utilise un pin et le compare aux pins enregistré
 * @param	pointeur sur tableau du pin a utiliser
 * @return	TRUE si le pin est validé
 */
bool_e pinUse(int8_t *pin, int8_t * pins[]) {
	for (int8_t i = 0; i < 4; i++) {
		char c = (char) (pins[0][i] + 48);
		ILI9341_Putc((uint16_t) (10 + 7 * i), 10, c, &Font_11x18,
		ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
	}

	uint8_t i;
	for (i = 0; i < PIN_MAX_NUMBER; i++) {
		uint8_t matches = 0;
		for (uint8_t y = 0; y < 4; y++) {
			if (pin[y] == pins[i][y]) {
				matches++;
				char c = (char) (pins[y][i] + 48);
				ILI9341_Putc((uint16_t) (10 + 7 * y), 10, c, &Font_11x18,
				ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
			}
		}
		if (matches == 4) {
			return TRUE;
		}
	}
	return FALSE;	//Pas de place libre !
}

