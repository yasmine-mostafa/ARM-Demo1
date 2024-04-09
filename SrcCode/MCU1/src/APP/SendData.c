/*
 * SendData.c
 *
 *  Created on: Apr 7, 2024
 *      Author: Yasmine Mostafa
 */

/****************************************************************************************
 *                        	              Includes                                      *
 ****************************************************************************************/

#include "Error.h"
#include "STD_TYPES.h"
#include "USART.h"
#include "Keypad.h"

/****************************************************************************************
 *                        	            Variables                                     *
 ****************************************************************************************/

USART_TXBuffer USART_TX=
{
		.Data=NULL,
		.Size=1,
		.Channel=USART1,
};

/****************************************************************************************
 *                        	              Runnable Implementation                      *
 ****************************************************************************************/

/**
 *@brief  : Send the pressed key over UART.
 *@periodicity:
 */
void SendData_Runnable(void)
{
	u8 Loc_Key=0;
   KEYPAD_voidGetPressedKey(&Loc_Key);
   USART_TX.Data=&Loc_Key;
   USART_SendBufferZeroCopy(&USART_TX);

}
