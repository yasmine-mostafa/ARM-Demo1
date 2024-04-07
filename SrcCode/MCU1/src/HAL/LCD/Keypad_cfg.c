/*
 * Keypad_cfg.c
 *
 *  Created on: Apr 5, 2024
 *      Author: Noha
 */
#include "../../MCAL/INCLUDES/GPIO.h"
#include "../INCLUDES/Keypad.h"

KEYPAD_t KEYPAD_Configuration[8]=
{
		[KEYPAD_COL4]={.port=GPIOB, .pin=GPIO_PIN_NUM0, .connection=CONNECTION_PU},
		[KEYPAD_COL3]={.port=GPIOB, .pin=GPIO_PIN_NUM1, .connection=CONNECTION_PU},
		[KEYPAD_COL2]={.port=GPIOB, .pin=GPIO_PIN_NUM2, .connection=CONNECTION_PU},
		[KEYPAD_COL1]={.port=GPIOB, .pin=GPIO_PIN_NUM3, .connection=CONNECTION_PU},
		[KEYPAD_ROW1]={.port=GPIOB, .pin=GPIO_PIN_NUM4, .connection=OTPUT_NO_CONNSCTION},
		[KEYPAD_ROW2]={.port=GPIOB, .pin=GPIO_PIN_NUM5, .connection=OTPUT_NO_CONNSCTION},
		[KEYPAD_ROW3]={.port=GPIOB, .pin=GPIO_PIN_NUM6, .connection=OTPUT_NO_CONNSCTION},
		[KEYPAD_ROW4]={.port=GPIOB, .pin=GPIO_PIN_NUM7,.connection=OTPUT_NO_CONNSCTION}
};

u8 KEYPAD_Keys[4][4]=
{
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'}

};



