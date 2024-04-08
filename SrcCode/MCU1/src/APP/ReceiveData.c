/*
 * ReceiveData.c
 *
 *  Created on: Apr 7, 2024
 *      Author: Yasmine Mostafa
 */

#include "Error.h"
#include "STD_TYPES.h"
#include "USART.h"


#define START 0
#define PAUSE 1
#define CONTINUE 2


typedef enum
{
	No_EditAction,
	UP_ARROW ,
	DOWN_ARROW,
	RIGHT_ARROW,
	LEFT_ARROW,
	INCREASE_BUTTON,
	DECREASE_BUTTON,
	OK
}EditPressedButton_t;

typedef enum
{
	DISPLAY_MODE,
	STOP_WATCH_MODE
}SelectMode_t;

typedef enum
{
	No_Action,
	STOP_WATCH_START,
	STOP_WATCH_PAUSE,
	STOP_WATCH_CONTINUE,
	STOP_WATCH_RESET
}StopWatchControl_t;

typedef enum
{
	EditON,
	EditOFF
}EditState_t;

USART_RXBuffer USART_RX=
{
		.Channel=USART1,
		.Data=NULL,
		.Size=1,
		.Index=0,
};


EditState_t G_enuEdit_flag=EditOFF;
SelectMode_t G_enuMode= DISPLAY_MODE;
EditPressedButton_t G_enuEditControl=No_Action;
StopWatchControl_t G_enuStopWatchControl=No_Action;


void ReceiveData_Runnable(void)
{
	static u8 Loc_StopWatchCount=START;
	USART_ReceiveBufferAsynchronous(&USART_RX);
	u8* Loc_ReceivedKey=&(USART_RX.Data);
	switch(*Loc_ReceivedKey)
	{
	case 'M':
		G_enuMode ^=1;
		break;

	case 'S':
		if(G_enuMode == STOP_WATCH_MODE)
		{
			switch(Loc_StopWatchCount)
			{
			case START:
				G_enuStopWatchControl = STOP_WATCH_START;
				Loc_StopWatchCount = PAUSE;
				break;

			case PAUSE:
				G_enuStopWatchControl = STOP_WATCH_PAUSE;
				Loc_StopWatchCount = CONTINUE;
				break;

			case CONTINUE:
				G_enuStopWatchControl = STOP_WATCH_CONTINUE;
				Loc_StopWatchCount = PAUSE;
				break;

			default:
				break;
			}

		}
		break;

	case 'C':
		if(G_enuMode == STOP_WATCH_MODE)
		{
			G_enuStopWatchControl = STOP_WATCH_RESET;
			Loc_StopWatchCount = START;

		}
		break;

	case 'E':
		if(G_enuMode == DISPLAY_MODE)
		{
			G_enuEdit_flag=EditON;
		}
		break;

	case 'k':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=OK;
		}
		break;

	case 'U':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=UP_ARROW;
		}
		break;

	case 'D':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=DOWN_ARROW;
		}
		break;

	case 'L':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=LEFT_ARROW;
		}
		break;

	case 'R':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=RIGHT_ARROW;
		}
		break;

	case '+':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=INCREASE_BUTTON;
		}
		break;

	case '-':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=DECREASE_BUTTON;
		}
	    break;

	default:
		break;

	}
   USART_RX.Data=NULL;
}


