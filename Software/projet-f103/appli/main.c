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
#include "tft_ili9341/stm32f1_xpt2046.h"
#include "PIN.h"
#include "screen.h"

static void state_machine(void);

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
	//Cette ligne doit rester la premi�re �tape de la fonction main().
	HAL_Init();


	//Initialisation de l'UART2 � la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reli�es jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirig�es vers la sonde de d�bogage, la liaison UART �tant ensuite encapsul�e sur l'USB vers le PC de d�veloppement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le p�riph�rique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);
	BSP_GPIO_PinCfg(GPIOA, GPIO_PIN_15, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	BSP_GPIO_PinCfg(GPIOB, GPIO_PIN_12, GPIO_MODE_INPUT,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms � la liste des fonctions appel�es automatiquement chaque ms par la routine d'interruption du p�riph�rique SYSTICK
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







	while(1)	//boucle de t�che de fond
	{

		writeLED(!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12));
		state_machine();

	}
}

static void state_machine(void)
{

	static screen_mode_e state = INIT;
	static screen_mode_e previous_state = INIT;
	bool_e entrance = (state!=previous_state)?TRUE:FALSE;	//ce bool�en sera vrai seulement 1 fois apr�s chaque changement d'�tat.
	previous_state = state;									//previous_state m�morise l'�tat actuel (qui est le futur �tat pr�c�dent)



	int8_t currentPin[4] = {-1,-1,-1,-1};


	UNUSED(currentPin);
	(void)entrance;



	switch(state){
		case INIT:
			pinInit();
			//LOCK_init();
			//SCREEN_init();
			//TACTILE_init();
			//Systick_add_callback_function(&process_ms);
			state = UNLOCKED;
			break;
		case UNLOCKED:
				if(screenMain(state) == TOUCHED){
					state = SETPIN;
				}
			break;
		case SETPIN:
			switch(screenMain(state))
			{
			case CANCEL:
				state = UNLOCKED;
				break;
			case NEWPIN:
				pinAdd(screenGetPin());
				break;
			default:
				break;
			}
			break;
		case LOCKED:
			if(screenMain(state) == TOUCHED)
			{
				state = SETPIN;
			}
			break;
		case ENTERPIN:
			switch(screenMain(state)){
			case CANCEL:
				state = LOCKED;
				break;
			case NEWPIN:
				pinUse(screenGetPin());
				break;
			default:
				break;
			}
			break;
		default:
			break;
	}

}
