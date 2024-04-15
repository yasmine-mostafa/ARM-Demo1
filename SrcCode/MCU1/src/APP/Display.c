/*
 * Display.c
 *
 *  Created on: Apr 8, 2024
 *      Author: Noha
 */

#include "../../include/HAL/LCD/LCD.h"
#include "STD_TYPES.h"
#include "Keypad.h"
#define PERIODICITY 500

#define FIRST_ROW  0
#define SECOND_ROW 1

#define TENS_DIGIT_DAY       5
#define UNITS_DIGIT_DAY      6
#define TENS_DIGIT_MONTH     8
#define UNITS_DIGIT_MONTH    9
#define THOUSANDS_DIGIT_YEAR 11
#define HUNDEREDS_DIGIT_YEAR 12
#define TENS_DIGIT_YEAR      13
#define UNITS_DIGIT_YEAR     14


#define TENS_DIGIT_HOURS       5
#define UNITS_DIGIT_HOURS      6
#define TENS_DIGIT_MINS        8
#define UNITS_DIGIT_MINS       9
#define TENS_DIGIT_SECS        11
#define UNITS_DIGIT_SECS       12

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
	EditOFF,
	EditON
}EditState_t;

SelectMode_t G_enuMode;
u32 G_u32Years=2023;
u8 G_u8Month=12;
u8 G_u8Days=31;
u8 G_u8hours=23;
u8 G_u8Mins=58;
u8 G_u8Secs=30;

u16 G_u8MSecs;




EditState_t G_enuEditMode;

u8 G_u8CurrRow=0;
u8 G_u8CurrCol=4;
EditPressedButton_t G_enuEditControl;

u8 G_u8HoursFlag=0;
u8 G_u8MinsFlag=0;
u8 G_u8SecsFlag=0;
u8 G_u8HDaysFlag=0;
u8 G_u8MonthsFlag=0;
u8 G_uYearsFlag=0;
u8 G_u8EditOn_flag=0;


void DisplayTimeMode_Runnable(void)
{

	u8 Loc_u8SecondsBackup;
	u8 Loc_u8MinsBackup;
	u8 Loc_u8HoursBackup;
	u8 Loc_u8DaysBackup;
	u8 Loc_u8MonthsBackup;
	u32 Loc_u32YearsBackup;
	
	G_u8MSecs+=PERIODICITY;
	if (G_u8MSecs==1000)
	{
		i
		 if(G_enuEditMode==EditON&&(G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&G_u8CurrRow==SECOND_ROW)
		{
			Loc_u8SecondsBackup++;
			G_u8MSecs=0;
		}
		else
		{
			G_u8Secs++;
			G_u8MSecs=0;

		}


	}
		
	if(G_u8Secs==60)
	{
		G_u8Secs=0;
		if(G_enuEditMode==EditON&&(G_u8CurrCol==UNITS_DIGIT_MINS||G_u8CurrCol==TENS_DIGIT_MINS)&&G_u8CurrRow==SECOND_ROW)
		{
			Loc_u8MinsBackup++;

		}
		else
		{
			if (!(Loc_u8SecondsBackup==60&&(G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&G_u8CurrRow==SECOND_ROW))
			{
				G_u8Mins++;
			}

		}
	}

	else if (G_u8Mins==60)
	{
		G_u8Mins = 0;
		if(G_enuEditMode==EditON&&(G_u8CurrCol==UNITS_DIGIT_HOURS||G_u8CurrCol==TENS_DIGIT_HOURS)&&G_u8CurrRow==SECOND_ROW)
		{
			Loc_u8HoursBackup++;
		}
		else
		{
			G_u8hours++;

		}
	}
	
		
	if (G_u8hours==24)
	{
		G_u8hours = 0;
		if(G_enuEditMode==EditON&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==FIRST_ROW)
		{
			Loc_u8DaysBackup++;

		}
		else
		{
			if(!(Loc_u8HoursBackup==24&&(G_u8CurrCol==UNITS_DIGIT_HOURS||G_u8CurrCol==TENS_DIGIT_HOURS)&&G_u8CurrRow==FIRST_ROW))
			{
				G_u8Days++;
			}

		}
	}


	if (G_u8Days==29)
	{
		if(G_u8Month==2 && (G_u32Years%4 !=0))
		{
			G_u8Days = 1;
			if(G_enuEditMode==EditON&&(G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==FIRST_ROW)
			{
				Loc_u8MonthsBackup++;

		}
			else
			{
				G_u8Month++;
			}
		}
	}

	if (G_u8Days==30)
	{
		if(G_u8Month==2 && (G_u32Years%4 ==0))
		{
			G_u8Days = 1;
			if(G_enuEditMode==EditON&&(G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==FIRST_ROW)
			{
				Loc_u8MonthsBackup++;

			}
			else
			{
				G_u8Month++;
			}
		}
	}
		

	if (G_u8Days==31)
	{
		if(		G_u8Month==4
				||G_u8Month==6
				||G_u8Month==9
				||G_u8Month==11)
		{
				G_u8Days = 1;
				if(G_enuEditMode==EditON&&(G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==FIRST_ROW)
				{
					Loc_u8MonthsBackup++;

				}
				else if(!(Loc_u8DaysBackup==31&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==FIRST_ROW))
				{
					G_u8Month++;
				}
		}
	}

	if(G_u8Days>31)
	{
		G_u8Days = 1;
		if((G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==FIRST_ROW)
		{
			Loc_u8MonthsBackup++;

		}
		else if(!(Loc_u8DaysBackup>31&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==FIRST_ROW))
		{
			G_u8Month++;
		}

	}
	if (G_u8Month>12)
	{
		G_u8Month = 1;
		if(G_enuEditMode==EditON&&(G_u8CurrCol==UNITS_DIGIT_YEAR
			||G_u8CurrCol==TENS_DIGIT_YEAR
			||G_u8CurrCol==HUNDEREDS_DIGIT_YEAR
			||G_u8CurrCol==THOUSANDS_DIGIT_YEAR)&&G_u8CurrRow==FIRST_ROW)
		{
			Loc_u32YearsBackup++;

		}
		else
		{

			G_u32Years++;
		}

	}
	if(G_enuMode==DISPLAY_MODE)
	{

		LCD_ClearScreenAsynch();
		LCD_WriteStringAsynch("DATE:");
		
		if(G_u8Days>=10)
		{
			LCD_WriteNumberAsynch(G_u8Days);

		}
		else
		{
			LCD_WriteNumberAsynch(0);
			LCD_WriteNumberAsynch(G_u8Days);
		}

		LCD_WriteStringAsynch(".");
		if(G_u8Month>=10)
		{

			LCD_WriteNumberAsynch(G_u8Month);

		}
		else
		{
			LCD_WriteNumberAsynch(0);
			LCD_WriteNumberAsynch(G_u8Month);
		}
		LCD_WriteStringAsynch(".");
		LCD_WriteNumberAsynch(G_u32Years);
		LCD_SetCursorPositionAsynch(1,0);
		LCD_WriteStringAsynch("TIME:");

		if(G_u8hours<10)
		{
			LCD_WriteNumberAsynch(0);
			LCD_WriteNumberAsynch(G_u8hours);

		}
		else
		{
			LCD_WriteNumberAsynch(G_u8hours);
		}
		LCD_WriteStringAsynch(":");
		if(G_u8Mins<10)
		{
			LCD_WriteNumberAsynch(0);
			LCD_WriteNumberAsynch(G_u8Mins);

		}
		else
		{
			LCD_WriteNumberAsynch(G_u8Mins);
		}
		LCD_WriteStringAsynch(":");
		if(G_u8Secs<10)
		{
			LCD_WriteNumberAsynch(0);
			LCD_WriteNumberAsynch(G_u8Secs);

		}
		else
		{
			LCD_WriteNumberAsynch(G_u8Secs);
		}
		



	}

	if(G_enuEditMode==EditON)
	{
				if((G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&G_u8CurrRow==1&&G_u8SecsFlag==0)
		{
			Loc_u8SecondsBackup=G_u8Secs;
			G_u8SecsFlag=1;
			G_u8HoursFlag=0;
			G_u8MinsFlag=0;
			G_u8HDaysFlag=0;
			G_u8MonthsFlag=0;
			G_uYearsFlag=0;

		}


		else if((G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==0&&G_u8MonthsFlag==0)
		{
			Loc_u8MonthsBackup=G_u8Month;
			G_u8SecsFlag=0;
			G_u8HoursFlag=0;
			G_u8MinsFlag=0;
			G_u8HDaysFlag=0;
			G_u8MonthsFlag=1;
			G_uYearsFlag=0;

		}

		else if((G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==0&&G_u8HDaysFlag==0)
		{
			Loc_u8DaysBackup=G_u8Days;
			G_u8SecsFlag=0;
			G_u8HoursFlag=0;
			G_u8MinsFlag=0;
			G_u8HDaysFlag=1;
			G_u8MonthsFlag=0;
			G_uYearsFlag=0;
		}

		else if((G_u8CurrCol==UNITS_DIGIT_YEAR||G_u8CurrCol==TENS_DIGIT_YEAR||G_u8CurrCol==HUNDEREDS_DIGIT_YEAR
				||G_u8CurrCol==THOUSANDS_DIGIT_YEAR)&&G_u8CurrRow==1&&G_u8HoursFlag==0)
		{
			Loc_u32YearsBackup=G_u32Years;
			G_u8SecsFlag=0;
			G_u8HoursFlag=1;
			G_u8MinsFlag=0;
			G_u8HDaysFlag=0;
			G_u8MonthsFlag=0;
			G_uYearsFlag=0;

		}


		else if((G_u8CurrCol==UNITS_DIGIT_MINS||G_u8CurrCol==TENS_DIGIT_MINS)&&G_u8CurrRow==1&&G_u8MinsFlag==0)
		{
			Loc_u8MinsBackup=G_u8Mins;
			G_u8SecsFlag=0;
			G_u8HoursFlag=0;
			G_u8MinsFlag=1;
			G_u8HDaysFlag=0;
			G_u8MonthsFlag=0;
			G_uYearsFlag=0;
		}

		else if((G_u8CurrCol==UNITS_DIGIT_HOURS||G_u8CurrCol==TENS_DIGIT_HOURS)&&G_u8CurrRow==1&&G_u8HoursFlag==0)
		{
			Loc_u8HoursBackup=G_u8hours;
			G_u8SecsFlag=0;
			G_u8HoursFlag=1;
			G_u8MinsFlag=0;
			G_u8HDaysFlag=0;
			G_u8MonthsFlag=0;
			G_uYearsFlag=0;
		}

		if(Loc_u8SecondsBackup==60&&(G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&G_u8CurrRow==SECOND_ROW)
		{
			Loc_u8SecondsBackup=0;
			G_u8Mins++;

		}
		if(Loc_u8MinsBackup==60&&(G_u8CurrCol==UNITS_DIGIT_MINS||G_u8CurrCol==TENS_DIGIT_MINS)&&G_u8CurrRow==SECOND_ROW)
		{
			Loc_u8MinsBackup=0;

			G_u8hours++;

		}
		if (Loc_u8HoursBackup==24&&((G_u8CurrCol==UNITS_DIGIT_HOURS||G_u8CurrCol==TENS_DIGIT_HOURS)&&G_u8CurrRow==FIRST_ROW))
		{

				Loc_u8HoursBackup=0;
				G_u8Days++;
		}

		if (Loc_u8DaysBackup==29&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==FIRST_ROW)
		{

			if(G_u8Month==2 && (G_u32Years%4 !=0))
			{
				Loc_u8DaysBackup = 1;
				G_u8Month++;
			}
		}



		if (Loc_u8DaysBackup==30&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==FIRST_ROW)
		{
			if(G_u8Month==2 && (G_u32Years%4 ==0))
			{
				Loc_u8DaysBackup = 1;

				G_u8Month++;
			}

		}



		if (Loc_u8DaysBackup==31&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==FIRST_ROW)
		{
			if(		G_u8Month==4
					||G_u8Month==6
					||G_u8Month==9
					||G_u8Month==11)
			{
					Loc_u8DaysBackup = 1;

					G_u8Month++;
			}
		}


		if(Loc_u8DaysBackup>31&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==FIRST_ROW)
		{
			Loc_u8DaysBackup = 1;
			G_u8Month++;

		}


		if (Loc_u8MonthsBackup>12&&(G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==FIRST_ROW)
		{
			Loc_u8MonthsBackup = 1;
			G_u32Years++;
		}

		Edit_Action();

	}

}


void Edit_Action(void)
{
	u8 Loc_u8PreviousValue;
	u8 Loc_u8EditHours;
	u8 Loc_u8EditSecs;
	u8 Loc_u8EditMins;
	u8 Loc_u8EditMonth;
	u8 Loc_u8EditDays;
	u32 Loc_u32EditYears;
	Loc_u32EditYears=G_u32Years;
	Loc_u8EditMonth=G_u8Month;
	Loc_u8EditDays=G_u8Days;
	Loc_u8EditHours=G_u8hours;
	Loc_u8EditSecs=G_u8Secs;
	Loc_u8EditMins=G_u8Mins;

	LCD_SetCursorPositionAsynch(G_u8CurrRow,G_u8CurrCol);
	//KEYPAD_voidGetPressedKey(&G_enuEditControl);
	switch(G_enuEditControl)
	{
		case DOWN_ARROW:
			if(G_u8CurrRow==0)
			{
				G_u8CurrRow++;

			}
			else
			{
				//do nothing
			}

			break;
		case UP_ARROW:
			if(G_u8CurrRow==1)
			{
				G_u8CurrRow--;
			}
			else
			{

			}

			break;
		case RIGHT_ARROW:
			if(G_u8CurrCol<15)
			{
				G_u8CurrCol++;

			}
			else
			{

			}
			break;
		case LEFT_ARROW:
			if(G_u8CurrCol>0)
			{
				G_u8CurrCol--;
			}
			else
			{

			}
			break;
		case OK:
			G_enuEditMode=EditOFF;
			G_u8SecsFlag=0;
			G_u8HoursFlag=0;
			G_u8MinsFlag=0;
			G_u8HDaysFlag=0;
			G_u8MonthsFlag=0;
			G_uYearsFlag=0;
			break;
		case DECREASE_BUTTON:
			switch(G_u8CurrRow)
			{
			case FIRST_ROW:
				if((G_u8CurrCol==TENS_DIGIT_DAY||G_u8CurrCol==UNITS_DIGIT_DAY)&&Loc_u8EditDays<=32)
				{
					Loc_u8EditDays--;
					G_u8Days=Loc_u8EditDays;

				}
				else if((G_u8CurrCol==TENS_DIGIT_MONTH||G_u8CurrCol==UNITS_DIGIT_MONTH)&&Loc_u8EditMonth<=12)
				{
					Loc_u8EditMonth--;
					G_u8Month=Loc_u8EditMonth;

				}
				else if(G_u8CurrCol<UNITS_DIGIT_YEAR+1&&G_u8CurrCol>THOUSANDS_DIGIT_YEAR-1)
				{
					Loc_u32EditYears--;
					G_u32Years=Loc_u32EditYears;

				}
				else
				{

				}
				break;
			case SECOND_ROW:
				if((G_u8CurrCol==TENS_DIGIT_HOURS||G_u8CurrCol==UNITS_DIGIT_HOURS)&&Loc_u8EditHours<=24)
				{
					Loc_u8EditHours--;
					G_u8hours=Loc_u8EditHours;

				}
				else if((G_u8CurrCol==TENS_DIGIT_MINS||G_u8CurrCol==UNITS_DIGIT_MINS)&&Loc_u8EditMins<=60)
				{
					Loc_u8EditMins--;
					G_u8Mins=Loc_u8EditMins;

				}
				else if((G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&Loc_u8EditSecs<=60)
				{
					Loc_u8EditSecs--;
					G_u8Secs=Loc_u8EditSecs;
				}
				else
				{

				}

				break;

				}
			break;
			case INCREASE_BUTTON:
			switch(G_u8CurrRow)
			{

			case FIRST_ROW:
				if((G_u8CurrCol==TENS_DIGIT_DAY||G_u8CurrCol==UNITS_DIGIT_DAY)&&Loc_u8EditDays<=32)
				{
					Loc_u8EditDays++;
					G_u8Days=Loc_u8EditDays;

				}
				else if((G_u8CurrCol==TENS_DIGIT_MONTH||G_u8CurrCol==UNITS_DIGIT_MONTH)&&Loc_u8EditMonth<=12)
				{
					Loc_u8EditMonth++;
					G_u8Month=Loc_u8EditMonth;

				}
				else if(G_u8CurrCol<UNITS_DIGIT_YEAR+1&&G_u8CurrCol>THOUSANDS_DIGIT_YEAR-1)
				{
					Loc_u32EditYears++;
					G_u32Years=Loc_u32EditYears;

				}
				else
				{

				}
				break;
			case SECOND_ROW:
				if((G_u8CurrCol==TENS_DIGIT_HOURS||G_u8CurrCol==UNITS_DIGIT_HOURS)&&Loc_u8EditHours<=24)
				{
					Loc_u8EditHours++;
					G_u8hours=Loc_u8EditHours;

				}
				else if((G_u8CurrCol==TENS_DIGIT_MINS||G_u8CurrCol==UNITS_DIGIT_MINS)&&Loc_u8EditMins<=60)
				{
					Loc_u8EditMins++;
					G_u8Mins=Loc_u8EditMins;

				}
				else if((G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&Loc_u8EditSecs<=60)
				{
					Loc_u8EditSecs++;
					G_u8Secs=Loc_u8EditSecs;
				}
				else
				{

				}

				break;

				}
			break;

		default:
			break;

		

	}
	G_enuEditControl=No_EditAction;

}

