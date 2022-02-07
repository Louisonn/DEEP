/**
 ******************************************************************************
 * @file    main.c
 * @author  Nirgal
 * @date    03-July-2019
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1xx_hal.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"
#include "PIN.h"
#include "screen.h"



static void state_machine(void);



static uint32_t t = 0;
void process_ms(void) {
	if (t) {
		t--;
	}

}

int main(void) {
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la premiére étape de la fonction main().
	HAL_Init();

	//Initialisation de l'UART2 é la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
	//Attention, les pins PA2 et PA3 ne sont pas reliées jusqu'au connecteur de la Nucleo.
	//Ces broches sont redirigées vers la sonde de débogage, la liaison UART étant ensuite encapsulée sur l'USB vers le PC de développement.
	UART_init(UART2_ID, 115200);

	//"Indique que les printf sortent vers le périphérique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//On ajoute la fonction process_ms é la liste des fonctions appelées automatiquement chaque ms par la routine d'interruption du périphérique SYSTICK
	Systick_add_callback_function(&process_ms);


	//Initialisation de la pin pour controler le solénoïde en sortie
	BSP_GPIO_PinCfg(GPIOB, GPIO_PIN_14, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);


	while (1)	//boucle de tache de fond
	{
		state_machine();

	}
}

static void state_machine(void) {
	static screen_mode_e state = INIT;
	static screen_mode_e previous_state = INIT;
	bool_e entrance = (state != previous_state) ? TRUE : FALSE;	//ce booléen sera vrai seulement 1 fois aprés chaque changement d'état.
	previous_state = state;	//previous_state mémorise l'état actuel (qui est le futur état précédent)

	switch (state) {
	case INIT:
		screenInit();
		pinInit();
		state = UNLOCKED;
		break;
	case UNLOCKED:
		if (screenMain(state, entrance) == TOUCHED) {
			state = SETPIN;
		}
		break;
	case SETPIN:
		switch (screenMain(state, entrance)) {
		case CANCEL:
			state = UNLOCKED;
			break;
		case NEWPIN: {
			static int8_t newPin[4];
			uint8_t i;
			for(i = 0; i<4; i++){
				newPin[i] = screenGetPin()[i];
			}
			pinAdd(newPin);
			state = LOCKED;
		}
			break;
		default:
			break;
		}
		break;
	case LOCKED:
		if (screenMain(state, entrance) == TOUCHED) {
			state = ENTERPIN;
		}
		break;
	case ENTERPIN:
		switch (screenMain(state, entrance)) {
		case CANCEL:
			state = LOCKED;
			break;
		case NEWPIN: {
			if(pinUse(screenGetPin())){
				state = UNLOCKED;
			}
			else{
				state = LOCKED;
			}
		}
			break;
		default:
			break;
		}

	default:
		break;
	}

	screenCheck(state, &t);

}
