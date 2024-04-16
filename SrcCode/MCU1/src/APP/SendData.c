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
#include "HUSART.h"

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

   if(Loc_Key != NULL)
   {
	   HUSART_SendByte(USART1,Loc_Key);
   }

}
