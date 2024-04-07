/*
 * Keybad.c
 *
 *  Created on: Apr 5, 2024
 *      Author: Noha
 */
#include "../../MCAL/INCLUDES/GPIO.h"
#include "../INCLUDES/SWITCH.h"
#include "../INCLUDES/Keypad.h"

#define PERIODICITY 50

extern const KEYPAD_t KEYPAD_Configuration[8];
extern u8 KEYPAD_Keys[4][4];
u8 G_col=0;
u8 G_row=0;
u8 G_swState[4][4]={0};

void KEYPAD_Init(void)
{
	GPIO_pin_t sw;
	sw.pinSpeed=PIN_SPEED_HIGH_SPEED;

	for(u32 itr=0; itr<8; itr++)
	{
		switch(KEYPAD_Configuration[itr].connection)
		{
			case CONNECTION_PU:
				sw.pinMode=PIN_STATUS_INPUT_PU;
				break;
			case CONNECTION_PD:
				sw.pinMode=PIN_STATUS_INPUT_PD;
				break;
			case OTPUT_NO_CONNSCTION:
				sw.pinMode=PIN_STATUS_GP_OUTPUT_PP_PU;
				break;

			default:
				break;
		}

		sw.GPIONum=KEYPAD_Configuration[itr].port;
		sw.pinNum=KEYPAD_Configuration[itr].pin;
		GPIO_initPin(sw);
		}

	/*setting default value of rows to be 1 (high) as they are outputs the other pullup resistors are already set to 1*/
	for (int itr=4; itr<8; itr++)
	{
		GPIO_setPinValue(KEYPAD_Configuration[itr].port,KEYPAD_Configuration[itr].pin,VALUE_SET_HIGH);
	}

}

//each 50ms
KEYPAD_enuErrorStatus_t KEYPAD_voidGetPressedKey(u8 * Copy_pu8KeyValue)
{
	KEYPAD_enuErrorStatus_t KEYPAD_enuErrorStatus=KEYPAD_StatusOk;
	if(Copy_pu8KeyValue==NULL)
	{
		KEYPAD_enuErrorStatus=KEYPAD_StatusNOk;
	}
	else
	{
		* Copy_pu8KeyValue=G_swState[G_row][G_col];
	}
	return KEYPAD_enuErrorStatus;
}
void KEYPADGetKey_Runnable(void)

{
	u8 Loc_swcurrent=0;
	static u32 Loc_swPrev[4][4]={0};
	static u32  Loc_swCounts[4][4]={0};
	u8 flag=0;
	//Rows->output
	for (int itr1=4; itr1<8; itr1++)
	{
		GPIO_setPinValue(KEYPAD_Configuration[itr1].port,KEYPAD_Configuration[itr1].pin,VALUE_SET_LOW);
		//col->i/p
		for (int itr2=0; itr2<4; itr2++)
		{
			GPIO_getPinValue(KEYPAD_Configuration[itr2].port,KEYPAD_Configuration[itr2].pin,&Loc_swcurrent);
			if(Loc_swcurrent==Loc_swPrev[itr1-4][itr2])
			{
				Loc_swCounts[itr1-4][itr2]++;
			}
			else
			{
				Loc_swCounts[itr1-4][itr2]=0;
			}
			if(Loc_swCounts[itr1-4][itr2]==5)
			{
				G_row=itr1-4;
				G_col=itr2;
				Loc_swcurrent^=KEYPAD_Configuration[itr2].connection;
				if(Loc_swcurrent==SWITCH_PRESSED)
				{
					Loc_swcurrent=KEYPAD_Keys[itr1-4][itr2];
					G_swState[itr1-4][itr2]=Loc_swcurrent;
					Loc_swCounts[itr1-4][itr2]=0;
					flag=1;
				break;
				}
				else
				{
					G_swState[itr1-4][itr2]=Loc_swcurrent;
				}


			}

			Loc_swPrev[itr1-4][itr2]=Loc_swcurrent;

		}
		GPIO_setPinValue(KEYPAD_Configuration[itr1].port,KEYPAD_Configuration[itr1].pin,VALUE_SET_HIGH);
		if (flag==1)
		{
			flag=0;
			break;
		}
	}
}


