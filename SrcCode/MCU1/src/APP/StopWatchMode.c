/*
 * StopWatchMode.c
 *
 *  Created on: Apr 7, 2024
 *      Author: Yasmine Mostafa
 */

#include "Error.h"
#include "STD_TYPES.h"
#include "GPIO.h"
#include "LCD_CFG.h"
#include "LCD.h"
#include "Mode.h"
#include "StopWatch.h"

#define PERIODICITY 50
#define FIRST_ROW 0
#define SECOND_ROW 1
#define STRING_COLUMN 1
#define NUMBERS_COLUMN 5
#define MODE_OFF 0
#define MODE_ON 1
#define MODE_RESET 2
#define MAX_MSEC 100
#define MAX_SEC 60


extern SelectMode_t G_enuMode;
extern StopWatchControl_t G_enuStopWatchControl;

void StopWatchMode_Runnable(void) ////50 msec
{
	static u8 Loc_mSec=0;
	static u8 Loc_Sec=0;
	static u8 Loc_Min=0;
	static u8 Loc_Mode=MODE_OFF;

	if(G_enuMode == STOP_WATCH_MODE)
	{
		LCD_ClearScreenAsynch();
		LCD_SetCursorPositionAsynch(FIRST_ROW,STRING_COLUMN);
		LCD_WriteStringAsynch("StopWatch Mode");

		if(Loc_Min < 10)
		{
			LCD_SetCursorPositionAsynch(SECOND_ROW,NUMBERS_COLUMN);
			LCD_WriteNumberAsynch(0);
			LCD_WriteNumberAsynch(Loc_Min);
		}
		else if(Loc_Min > 99)
		{
			LCD_SetCursorPositionAsynch(SECOND_ROW,NUMBERS_COLUMN-1);
			LCD_WriteNumberAsynch(Loc_Min);
		}
		else
		{
			LCD_SetCursorPositionAsynch(SECOND_ROW,NUMBERS_COLUMN);
			LCD_WriteNumberAsynch(Loc_Min);
		}

		LCD_WriteStringAsynch(".");

		if(Loc_Sec < 10)
		{
			LCD_WriteNumberAsynch(0);
			LCD_WriteNumberAsynch(Loc_Sec);
		}
		else
		{
			LCD_WriteNumberAsynch(Loc_Sec);
		}

		LCD_WriteStringAsynch(".");
		if(Loc_mSec < 10)
		{
			LCD_WriteNumberAsynch(0);
			LCD_WriteNumberAsynch(Loc_mSec);
		}
		else
		{
			LCD_WriteNumberAsynch(Loc_mSec);
		}

		switch(G_enuStopWatchControl)
		{
		case STOP_WATCH_START:
			Loc_Mode = MODE_ON;
			break;

		case STOP_WATCH_PAUSE:
			Loc_Mode = MODE_OFF;
			break;

		case STOP_WATCH_CONTINUE:
			Loc_Mode = MODE_ON;
			break;

		case STOP_WATCH_RESET:
			Loc_Mode = MODE_RESET;
			break;

		case No_Action:
			break;

		default:
			break;
		}


	}

	if(Loc_Mode == MODE_ON)
	{
		Loc_mSec+=PERIODICITY;
		if(Loc_mSec == MAX_MSEC)
		{
			Loc_mSec=0;
			Loc_Sec++;
		}
		if(Loc_Sec == MAX_SEC)
		{
			Loc_Sec=0;
			Loc_Min++;
		}
	}
	else if(Loc_Mode == MODE_RESET)
	{
		Loc_mSec=0;
		Loc_Sec=0;
		Loc_Min=0;
		LCD_SetCursorPositionAsynch(SECOND_ROW,NUMBERS_COLUMN);
		LCD_WriteNumberAsynch(0);
		LCD_WriteNumberAsynch(0);
		LCD_WriteStringAsynch(".");
		LCD_WriteNumberAsynch(0);
		LCD_WriteNumberAsynch(0);
		LCD_WriteStringAsynch(".");
		LCD_WriteNumberAsynch(0);
		LCD_WriteNumberAsynch(0);
		Loc_Mode = MODE_OFF;
	}
	else
	{

	}

}
