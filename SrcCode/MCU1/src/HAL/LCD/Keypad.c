/*
 * Keybad.c
 *
 *  Created on: Apr 5, 2024
 *      Author: Noha
 */
#include "../../MCAL/INCLUDES/GPIO.h"
#include "../INCLUDES/SWITCH.h"
#include "../INCLUDES/Keypad.h"

extern const KEYPAD_t KEYPAD_Configuration[8];
extern const u8 KEYPAD_Keys[4][4];
u8 G_col=0;
u8 G_row=0;
u8 G_swState[4][4]={0};
//KeypadPost_t KEYPAD_postion;

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
	for (int itr=0; itr<ROWS_NUM; itr++)
	{
		GPIO_setPinValue(KEYPAD_Configuration[itr+COLS_NUM].port,KEYPAD_Configuration[itr].pin,VALUE_SET_HIGH);
	}

}


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

//each 5ms
void KEYPADGetKey_Runnable(void)

{
	u8 Loc_swcurrent=0;
	static u32 Loc_swPrev[ROWS_NUM][COLS_NUM]={0};
	static u32  Loc_swCounts[ROWS_NUM][COLS_NUM]={0};
	u8 flag=0;
	//Rows->output
	/*for (u8 row=0;row<16;row++)
	{
		KEYPAD_postion.row=row/4;
		GPIO_setPinValue(KEYPAD_Configuration[KEYPAD_postion.row+4].port,KEYPAD_Configuration[KEYPAD_postion.row+4].pin,VALUE_SET_LOW);
		if(KEYPAD_postion.col<4)
		{
			GPIO_getPinValue(KEYPAD_Configuration[KEYPAD_postion.col].port,KEYPAD_Configuration[KEYPAD_postion.col].pin,&Loc_swcurrent);

			if(Loc_swcurrent==Loc_swPrev[KEYPAD_postion.row][KEYPAD_postion.col])
			{
				Loc_swCounts[KEYPAD_postion.row][KEYPAD_postion.col]++;
			}
			else
			{
				Loc_swCounts[KEYPAD_postion.row][KEYPAD_postion.col]=0;
			}
			if(Loc_swCounts[KEYPAD_postion.row][KEYPAD_postion.col]==5)
			{
				G_row=KEYPAD_postion.row;
				G_col=KEYPAD_postion.col;
				Loc_swcurrent^=KEYPAD_Configuration[KEYPAD_postion.col].connection;
				if(Loc_swcurrent==SWITCH_PRESSED)
				{
					Loc_swcurrent=KEYPAD_Keys[G_row][G_col];
					G_swState[KEYPAD_postion.row][KEYPAD_postion.col]=Loc_swcurrent;
					Loc_swCounts[KEYPAD_postion.row][KEYPAD_postion.col]=0;
					break;
				}
				else
				{
					G_swState[KEYPAD_postion.row][KEYPAD_postion.col]=Loc_swcurrent;
					Loc_swCounts[KEYPAD_postion.row][KEYPAD_postion.col]=0;
				}

			}
			else
			{

			}

			Loc_swPrev[KEYPAD_postion.row][KEYPAD_postion.col]=Loc_swcurrent;
			KEYPAD_postion.col++;
		}
		else
		{
			GPIO_setPinValue(KEYPAD_Configuration[KEYPAD_postion.row+4].port,KEYPAD_Configuration[KEYPAD_postion.row+4].pin,VALUE_SET_HIGH);
			KEYPAD_postion.col=0;
		}
	}
	*/
	for (u8 itr1=0; itr1<ROWS_NUM; itr1++)
	{
		GPIO_setPinValue(KEYPAD_Configuration[itr1+COLS_NUM].port,KEYPAD_Configuration[itr1+COLS_NUM].pin,VALUE_SET_LOW);
		//col->i/p
		for (u8 itr2=0; itr2<COLS_NUM; itr2++)
		{
			GPIO_getPinValue(KEYPAD_Configuration[itr2].port,KEYPAD_Configuration[itr2].pin,&Loc_swcurrent);

			if(Loc_swcurrent==Loc_swPrev[itr1][itr2])
			{
				Loc_swCounts[itr1][itr2]++;
			}
			else
			{
				Loc_swCounts[itr1][itr2]=0;
			}
			if(Loc_swCounts[itr1][itr2]==5)
			{
				G_row=itr1;
				G_col=itr2;
				Loc_swcurrent^=KEYPAD_Configuration[itr2].connection;
				if(Loc_swcurrent==SWITCH_PRESSED)
				{
					Loc_swcurrent=KEYPAD_Keys[G_row][G_col];
					G_swState[itr1][itr2]=Loc_swcurrent;
					Loc_swCounts[itr1][itr2]=0;
					flag=1;
					break;
				}
				else
				{
					G_swState[itr1][itr2]=Loc_swcurrent;
					Loc_swCounts[itr1][itr2]=0;

				}


			}
			else
			{

			}

			Loc_swPrev[itr1][itr2]=Loc_swcurrent;

		}
		GPIO_setPinValue(KEYPAD_Configuration[itr1+COLS_NUM].port,KEYPAD_Configuration[itr1+COLS_NUM].pin,VALUE_SET_HIGH);
		if (flag==1)
		{
			flag=0;
			break;
		}
		else
		{

		}
	}
}




