/*
 * ReceiveData.c
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
#include "Mode.h"
#include "Edit.h"
#include "StopWatch.h"

/****************************************************************************************
 *                        	              Defines                                       *
 ****************************************************************************************/

#define START 0
#define PAUSE 1
#define CONTINUE 2

/****************************************************************************************
 *                        	            Variables                                     *
 ****************************************************************************************/

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


/****************************************************************************************
 *                        	              Runnable Implementation                   *
 ****************************************************************************************/

/**
 *@brief  : Receive the pressed key over UART and update states.
 *@periodicity:
 */
void ReceiveData_Runnable(void)
{
	static u8 Loc_StopWatchCount=START;

	USART_ReceiveBufferAsynchronous(&USART_RX);
	u8* Loc_ReceivedKey=&(USART_RX.Data);

	switch(*Loc_ReceivedKey)
	{
	/*Change mode*/
	case 'M':
		G_enuMode ^=1;
		break;

		/*Start/Pause/Continue stopwatch*/
	case 'S':
		if(G_enuMode == STOP_WATCH_MODE)
		{
			switch(Loc_StopWatchCount)
			{
			/*Start stopwatch*/
			case START:
				G_enuStopWatchControl = STOP_WATCH_START;
				Loc_StopWatchCount = PAUSE;
				break;

				/*Pause stopwatch*/
			case PAUSE:
				G_enuStopWatchControl = STOP_WATCH_PAUSE;
				Loc_StopWatchCount = CONTINUE;
				break;

				/*continue stopwatch*/
			case CONTINUE:
				G_enuStopWatchControl = STOP_WATCH_CONTINUE;
				Loc_StopWatchCount = PAUSE;
				break;

			default:
				break;
			}

		}
		break;

		/*Reset stopwatch*/
	case 'C':
		if(G_enuMode == STOP_WATCH_MODE)
		{
			G_enuStopWatchControl = STOP_WATCH_RESET;
			Loc_StopWatchCount = START;

		}
		break;

		/*Edit date or time*/
	case 'E':
		if(G_enuMode == DISPLAY_MODE)
		{
			G_enuEdit_flag=EditON;
		}
		break;

		/*Confirm edit*/
	case 'k':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=OK;
		}
		break;

		/*Go to the first row*/
	case 'U':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=UP_ARROW;
		}
		break;

		/*Go to the second row*/
	case 'D':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=DOWN_ARROW;
		}
		break;

		/*Go left*/
	case 'L':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=LEFT_ARROW;
		}
		break;

		/*Go right*/
	case 'R':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=RIGHT_ARROW;
		}
		break;

		/*Increase the selected number*/
	case '+':
		if(G_enuMode == DISPLAY_MODE && G_enuEdit_flag==EditON)
		{
			G_enuEditControl=INCREASE_BUTTON;
		}
		break;

		/*Decrease the selected number*/
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


