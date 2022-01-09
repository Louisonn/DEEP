/**
  ******************************************************************************
  * @file    main.c
  * @author  Nirgal
  * @date    03-July-2019
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"
#include "tft_ili9341/stm32f1_ili9341.h"
#include "PIN.h"


void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, !b);
}

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
}

static  uint32_t t = 0;
void process_ms(void)
{
	if(t)
	{
		t--;
	}

}


int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la première étape de la fonction main().
	HAL_Init();


	//Initialisation de l'UART2 à la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reliées jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirigées vers la sonde de débogage, la liaison UART étant ensuite encapsulée sur l'USB vers le PC de développement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le périphérique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);
	BSP_GPIO_PinCfg(GPIOA, GPIO_PIN_15, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	BSP_GPIO_PinCfg(GPIOB, GPIO_PIN_12, GPIO_MODE_INPUT,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms à la liste des fonctions appelées automatiquement chaque ms par la routine d'interruption du périphérique SYSTICK
	Systick_add_callback_function(&process_ms);




	ILI9341_Init();
	ILI9341_Fill(ILI9341_COLOR_WHITE);
	ILI9341_DrawCircle(20,20,5,ILI9341_COLOR_BLUE);
	ILI9341_DrawLine(20,20,100,20,ILI9341_COLOR_RED);
	ILI9341_DrawLine(20,20,20,100,ILI9341_COLOR_RED);
	ILI9341_Putc(110,11,'x',&Font_11x18,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
	ILI9341_Puts(10,110,"hugo",&Font_11x18,ILI9341_COLOR_BLUE,ILI9341_COLOR_WHITE);
	ILI9341_Puts(100,200, "hugo", &Font_11x18, ILI9341_COLOR_BROWN,
	ILI9341_COLOR_WHITE);







	while(1)	//boucle de tâche de fond
	{

		writeLED(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12));

	}
}

static void state_machine(void)
{
	typedef enum
	{
		INIT,
		UNLOCKED,
		PIN_MODIFYING,
		LOCKED,
		PIN_ENTERING
	}state_e;
	static state_e state = INIT;
	static state_e previous_state = INIT;
	bool_e entrance = (state!=previous_state)?TRUE:FALSE;	//ce booléen sera vrai seulement 1 fois après chaque changement d'état.
	previous_state = state;									//previous_state mémorise l'état actuel (qui est le futur état précédent)



	switch(state)
	{
		case INIT:
			PIN_init();
			//LOCK_init();
			//SCREEN_init();
			//TACTILE_init();
			//Systick_add_callback_function(&process_ms);
			state = UNLOCKED;
			break;
		case UNLOCKED:
			if(entrance){
				writeLED(0);	//UNLOCKING;
			}
			else if(newUser()){
				state = PIN_MODIFYING;
			}
			break;
		case PIN_MODIFYING:{
			int myNewPin[4] = {0, 1, 2, 3};
			int action = PIN_add(myNewPin);
			if(action == 0){		// 0 signifie cancel pour l'instant
				state = UNLOCKED;	// Echec de la procédure
			}
			if(action == 1){	// PIN is validated
				state = LOCKED;
			}
			break;}
		case LOCKED:
			if(entrance){
				writeLED(1);		//LOCKING
			}
			if(recovering()){	// On demande si l'utilisateur veux recuperer son bien (entrer le PIN)
				state = PIN_ENTERING;
			}
			break;
		case PIN_ENTERING:
			int action = 0;
			if(action == 0){		// 0 signifie cancel pour l'instant
				state = LOCKED;	// Echec de la procédure
			}
			if(action == 1){	// PIN is accepted
				state = UNLOCKED;
			}
			break;

		default:
			break;
	}
}
