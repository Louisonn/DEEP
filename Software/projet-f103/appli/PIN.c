/*
 * PIN.c
 *
 *  Created on: 8 janv. 2022
 *      Author: Louison
 */

#include "PIN.h"

#include "tft_ili9341/stm32f1_ili9341.h"


#define PIN_MAX_NUMBER	2
#define DEFAULT_PIN_CODE {0, 0, 0, 0}


static int8_t * pins[PIN_MAX_NUMBER] = {0};



/*
 * @brief	initialisation des saves des pins
 */
void pinInit() {
	static int8_t default_pin_code[] = DEFAULT_PIN_CODE;
	pinAdd(default_pin_code);

}



/*
 * @brief	ajoute le pin au tableau de saves si il y a de la place
 * @param	pointeur sur le tableau du pin a ajouté
 * @return	true si le pin est bien ajouté
 */
bool_e pinAdd(int8_t * newPin) {

	uint16_t i;
	for (i = 0; i < PIN_MAX_NUMBER; i++) {
		if (!pins[i])	//On a trouvï¿½ une place libre ?
		{
			pins[i] = newPin;
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
bool_e pinUse(int8_t *pin) {
	/*for (int8_t i = 0; i < 4; i++) {
		char c = (char) (pins[1][i] + 48);
		ILI9341_Putc((uint16_t) (10 + 15 * i), 10, c, &Font_11x18,
		ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);
	}*/

	uint8_t i;
	for (i = 0; i < PIN_MAX_NUMBER; i++) {
		uint8_t matches = 0;
		for (uint8_t y = 0; y < 4; y++) {
			if (pin[y] == pins[i][y]) {
				matches++;
			}
		}
		if (matches == 4) {
			if(i == 1){
				pins[i] = 0; // place utilisateur dans  saves de Pin : libre
			}
			return TRUE;
		}
	}
	return FALSE;	//Pas de place libre !
}

