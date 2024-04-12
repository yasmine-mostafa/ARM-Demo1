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



#define UP_ARROW    6
#define DOWN_ARROW  1
#define RIGHT_ARROW 2
#define LEFT_ARROW  3
#define INCREASE_BUTTON 4
#define DECREASE_BUTTON 5
#define	OK				7



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
	DISPLAY_MODE,
	STOP_WATCH_MODE
}SelectMode_t;

SelectMode_t G_enuMode;


u32 G_u32Years=2023;
u8 G_u8Month=12;
u8 G_u8Days=31;
u8 G_u8hours=23;
u8 G_u8Mins=59;
u8 G_u8Secs=30;

u16 G_u8MSecs;


u8 G_u8SecondsBackup;
u8 G_u8MinsBackup;
u8 G_u8HoursBackup;
u8 G_u8DaysBackup;
u8 G_u8MonthsBackup;
u32 G_u32YearsBackup;

u8 G_u8EditHours;
u8 G_u8EditSecs;
u8 G_u8EditMins;
u8 G_u8EditMonth;
u8 G_u8EditDays;
u32 G_u32EditYears;
u8 G_u8EditMode;

u8 G_u8CurrRow=0;
u8 G_u8CurrCol=4;
u8 G_PressedButton;



u8 G_CurrentCursor;

u8 G_u8HoursFlag=0;
u8 G_u8MinsFlag=0;
u8 G_u8SecsFlag=0;
u8 G_u8HDaysFlag=0;
u8 G_u8MonthsFlag=0;
u8 G_uYearsFlag=0;



void DisplayTimeMode_Runnable(void)
{
	if(G_enuMode==DISPLAY_MODE)
	{
		G_u8MSecs+=PERIODICITY;

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


		if((G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&G_u8CurrRow==1&&G_u8SecsFlag==0)
		{
			G_u8SecondsBackup=G_u8Secs;
			G_u8SecsFlag=1;
			G_u8HoursFlag=0;
			G_u8MinsFlag=0;
			G_u8HDaysFlag=0;
			G_u8MonthsFlag=0;
			G_uYearsFlag=0;

		}


		else if((G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==0&&G_u8MonthsFlag==0)
		{
			G_u8MonthsBackup=G_u8Month;
			G_u8SecsFlag=0;
			G_u8HoursFlag=0;
			G_u8MinsFlag=0;
			G_u8HDaysFlag=0;
			G_u8MonthsFlag=1;
			G_uYearsFlag=0;

		}

		else if((G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==0&&G_u8HDaysFlag==0)
		{
			G_u8DaysBackup=G_u8Days;
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
			G_u32YearsBackup=G_u32Years;
			G_u8MinsBackup=G_u8Mins;
			G_u8DaysBackup=G_u8Days;
			G_u8SecsFlag=0;
			G_u8HoursFlag=1;
			G_u8MinsFlag=0;
			G_u8HDaysFlag=0;
			G_u8MonthsFlag=0;
			G_uYearsFlag=0;

		}


		else if((G_u8CurrCol==UNITS_DIGIT_MINS||G_u8CurrCol==TENS_DIGIT_MINS)&&G_u8CurrRow==1&&G_u8MinsFlag==0)
		{
			G_u8MinsBackup=G_u8Mins;
			G_u8DaysBackup=G_u8Days;
			G_u8SecsFlag=0;
			G_u8HoursFlag=0;
			G_u8MinsFlag=1;
			G_u8HDaysFlag=0;
			G_u8MonthsFlag=0;
			G_uYearsFlag=0;
		}

		else if((G_u8CurrCol==UNITS_DIGIT_HOURS||G_u8CurrCol==TENS_DIGIT_HOURS)&&G_u8CurrRow==1&&G_u8HoursFlag==0)
		{
			G_u8HoursBackup=G_u8hours;
			G_u8DaysBackup=G_u8Days;
			G_u8SecsFlag=0;
			G_u8HoursFlag=1;
			G_u8MinsFlag=0;
			G_u8HDaysFlag=0;
			G_u8MonthsFlag=0;
			G_uYearsFlag=0;
		}

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
		if (G_u8MSecs==1000)
		{
			 if((G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&G_u8CurrRow==1)
			{
				G_u8SecondsBackup++;
				G_u8MSecs=0;
			}
			else
			{
				G_u8Secs++;
				G_u8MSecs=0;

			}
			/*if(G_PressedButton==OK)
			{
				G_u8Secs=G_u8EditSecs;
			}*/

		}

		if(G_u8SecondsBackup==60&&(G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&G_u8CurrRow==1)
		{
			G_u8SecondsBackup=0;
			G_u8Mins++;

		}
		if(G_u8Secs==60)
		{
			G_u8Secs=0;
			if((G_u8CurrCol==UNITS_DIGIT_MINS||G_u8CurrCol==TENS_DIGIT_MINS)&&G_u8CurrRow==1)
			{
				G_u8MinsBackup++;

			}
			else
			{
				if (!(G_u8SecondsBackup==60&&(G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&G_u8CurrRow==1))
				{
					G_u8Mins++;
				}

			}
		}
		if(G_u8MinsBackup==60&&(G_u8CurrCol==UNITS_DIGIT_MINS||G_u8CurrCol==TENS_DIGIT_MINS)&&G_u8CurrRow==1)
		{
			G_u8MinsBackup=0;

			G_u8hours++;

		}
		else if (G_u8Mins==60)
		{
			G_u8Mins = 0;
			if((G_u8CurrCol==UNITS_DIGIT_HOURS||G_u8CurrCol==TENS_DIGIT_HOURS)&&G_u8CurrRow==1)
			{
				G_u8HoursBackup++;

			}
			else
			{
				G_u8hours++;

			}
		}
		if (G_u8HoursBackup==24&&((G_u8CurrCol==UNITS_DIGIT_HOURS||G_u8CurrCol==TENS_DIGIT_HOURS)&&G_u8CurrRow==0))
		{

			    G_u8HoursBackup=0;
				G_u8Days++;
		}

		if (G_u8hours==24)
		{
			G_u8hours = 0;
			if((G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==0)
			{
				G_u8DaysBackup++;

			}
			else
			{
				if(!(G_u8HoursBackup==24&&(G_u8CurrCol==UNITS_DIGIT_HOURS||G_u8CurrCol==TENS_DIGIT_HOURS)&&G_u8CurrRow==0))
				{
					G_u8Days++;
				}

			}
		}

		if (G_u8DaysBackup==29&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==0)
		{

			if(G_u8Month==2 && (G_u32Years%4 !=0))
			{
				G_u8DaysBackup = 1;
				G_u8Month++;
			}
		}

		if (G_u8Days==29)
		{
			if(G_u8Month==2 && (G_u32Years%4 !=0))
			{
				G_u8Days = 1;
				if((G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==0)
				{
					G_u8MonthsBackup++;

				}
				else
				{
					G_u8Month++;
				}
			}
		}



		if (G_u8DaysBackup==30&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==0)
		{
			if(G_u8Month==2 && (G_u32Years%4 ==0))
			{
				G_u8DaysBackup = 1;

				G_u8Month++;
			}

		}
		if (G_u8Days==30)
		{
			if(G_u8Month==2 && (G_u32Years%4 ==0))
			{
				G_u8Days = 1;
				if((G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==0)
				{
					G_u8MonthsBackup++;

				}
				else
				{
					G_u8Month++;
				}
			}
		}

		if (G_u8DaysBackup==31&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==0)
		{
			if(		G_u8Month==4
					||G_u8Month==6
					||G_u8Month==9
					||G_u8Month==11)
			{
					G_u8DaysBackup = 1;

					G_u8Month++;
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
					if((G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==0)
					{
						G_u8MonthsBackup++;

					}
					else if(!(G_u8DaysBackup==31&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==0))
					{
						G_u8Month++;
					}
			}
		}

		if(G_u8DaysBackup>31&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==0)
		{
			G_u8DaysBackup = 1;
			G_u8Month++;

		}


		if(G_u8Days>31)
		{
			G_u8Days = 1;
			if((G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==0)
			{
				G_u8MonthsBackup++;

			}
			else if(!(G_u8DaysBackup>31&&(G_u8CurrCol==UNITS_DIGIT_DAY||G_u8CurrCol==TENS_DIGIT_DAY)&&G_u8CurrRow==0))
			{
				G_u8Month++;
			}

		}
		if (G_u8MonthsBackup>12&&(G_u8CurrCol==UNITS_DIGIT_MONTH||G_u8CurrCol==TENS_DIGIT_MONTH)&&G_u8CurrRow==0)
		{
			G_u8MonthsBackup = 1;
			G_u32Years++;
		}


		if (G_u8Month>12)
		{
			G_u8Month = 1;
			if((G_u8CurrCol==UNITS_DIGIT_YEAR
					||G_u8CurrCol==TENS_DIGIT_YEAR
					||G_u8CurrCol==HUNDEREDS_DIGIT_YEAR
					||G_u8CurrCol==THOUSANDS_DIGIT_YEAR)&&G_u8CurrRow==0)
			{
				G_u32YearsBackup++;

			}
			else
			{

				G_u32Years++;
			}

		}






	}
	G_u8EditMode=1;
	if(G_u8EditMode)
	{
		Edit_Runnable();

	}

}


void Edit_Runnable(void)
{
	//noha
	u8 Loc_u8PreviousValue;

	G_u32EditYears=G_u32Years;
	G_u8EditMonth=G_u8Month;
	G_u8EditDays=G_u8Days;
	G_u8EditHours=G_u8hours;
	G_u8EditSecs=G_u8Secs;
	G_u8EditMins=G_u8Mins;

	LCD_SetCursorPositionAsynch(G_u8CurrRow,G_u8CurrCol);
	KEYPAD_voidGetPressedKey(&G_PressedButton);
	switch(G_PressedButton)
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
		case INCREASE_BUTTON:
			switch(G_u8CurrRow)
			{
			case FIRST_ROW:
				if((G_u8CurrCol==TENS_DIGIT_DAY||G_u8CurrCol==UNITS_DIGIT_DAY)&&G_u8EditDays<31)
				{
					G_u8EditDays++;
					G_u8Days=G_u8EditDays;

				}
				else if((G_u8CurrCol==TENS_DIGIT_MONTH||G_u8CurrCol==UNITS_DIGIT_MONTH)&&G_u8EditMonth<12)
				{
					G_u8EditMonth++;
					G_u8Month=G_u8EditMonth;

				}
				else if(G_u8CurrCol<UNITS_DIGIT_YEAR+1&&G_u8CurrCol>THOUSANDS_DIGIT_YEAR-1&&G_u32EditYears<2024)
				{
					G_u32EditYears++;
					G_u32Years=G_u32EditYears;

				}
				else
				{

				}
				break;
			case SECOND_ROW:
				if((G_u8CurrCol==TENS_DIGIT_HOURS||G_u8CurrCol==UNITS_DIGIT_HOURS)&&G_u8EditHours<24)
				{
					G_u8EditHours++;
					G_u8hours=G_u8EditHours;

				}
				else if((G_u8CurrCol==TENS_DIGIT_MINS||G_u8CurrCol==UNITS_DIGIT_MINS)&&G_u8EditMins<60)
				{
					G_u8EditMins++;
					G_u8Mins=G_u8EditMins;

				}
				else if((G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&G_u8EditSecs<60)
				{
					G_u8EditSecs++;
					G_u8Secs=G_u8EditSecs;
				}
				else
				{

				}

				break;

				}
			break;
			case DECREASE_BUTTON:
			switch(G_u8CurrRow)
			{
				case FIRST_ROW:
					if((G_u8CurrCol==TENS_DIGIT_DAY||G_u8CurrCol==UNITS_DIGIT_DAY)&&G_u8EditDays<31)
					{
						G_u8EditDays--;
						G_u8Days=G_u8EditDays;

					}
					else if((G_u8CurrCol==TENS_DIGIT_MONTH||G_u8CurrCol==UNITS_DIGIT_MONTH)&&G_u8EditMonth<12)
					{
						G_u8EditMonth--;
						G_u8Month=G_u8EditMonth;

					}
					else if(G_u8CurrCol<UNITS_DIGIT_YEAR+1&&G_u8CurrCol>THOUSANDS_DIGIT_YEAR-1&&G_u32EditYears<2024)
					{
						G_u32EditYears--;
						G_u32Years=G_u32EditYears;

					}
					else
					{

					}
					break;
				case SECOND_ROW:
					if((G_u8CurrCol==TENS_DIGIT_HOURS||G_u8CurrCol==UNITS_DIGIT_HOURS)&&G_u8EditHours<24)
					{
						G_u8EditHours--;
						G_u8hours=G_u8EditHours;

					}
					else if((G_u8CurrCol==TENS_DIGIT_MINS||G_u8CurrCol==UNITS_DIGIT_MINS)&&G_u8EditMins<60)
					{
						G_u8EditMins--;
						G_u8Mins=G_u8EditMins;

					}
					else if((G_u8CurrCol==UNITS_DIGIT_SECS||G_u8CurrCol==TENS_DIGIT_SECS)&&G_u8EditSecs<60)
					{
						G_u8EditSecs--;
						G_u8Secs=G_u8EditSecs;
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

}


