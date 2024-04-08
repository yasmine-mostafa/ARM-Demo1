/*
 * Display.c
 *
 *  Created on: Apr 8, 2024
 *      Author: Noha
 */

#include "LCD.h"
#include "STD_TYPES.h"
#define PERIODICITY 500
u32 G_u32Years=202;
u8 G_u8Month=10;
u8 G_u8Days=24;
u8 G_u8hours=14;
u8 G_u8Mins=12;
u16 G_u8Secs=20;
u16 G_u8MSecs;


void DisplayTimeMode_Runnable(void)
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
	if(G_u8hours<10)
	{
		LCD_WriteNumberAsynch(0);
		LCD_WriteNumberAsynch(G_u8hours);

	}
	else
	{
		LCD_WriteNumberAsynch(G_u8hours);
	}
	LCD_WriteStringAsynch(".");
	if(G_u8Mins<10)
	{
		LCD_WriteNumberAsynch(0);
		LCD_WriteNumberAsynch(G_u8Mins);

	}
	else
	{
		LCD_WriteNumberAsynch(G_u8Mins);
	}
	LCD_WriteStringAsynch(".");
	if(G_u8Secs<10)
	{
		LCD_WriteNumberAsynch(0);
		LCD_WriteNumberAsynch(G_u8Secs);

	}
	else
	{
		LCD_WriteNumberAsynch(G_u8Secs);
	}
	if (G_u8MSecs<=1000)
	{
		G_u8Secs++;
		G_u8MSecs=0;
	}
	if(G_u8Secs>60)
	{
		G_u8Secs=0;
		G_u8Mins++;
	}
	else
	{

	}
	if (G_u8Mins==60)
	{
		G_u8Mins = 0;
		G_u8hours++;
	}
	if (G_u8hours==24)
	{
		G_u8hours = 0;
		G_u8Days++;
	}
	if (G_u8Days==29)
	{
		if(G_u8Month==2 && (G_u32Years%4 !=0))
		{
			G_u8Days = 1;
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
				G_u8Month++;
		}
	}
	if(G_u8Days==32)
	{
		G_u8Days = 1;
		G_u8Month++;
	}
	if (G_u8Month==13)
		{
		G_u8Month = 1;
		G_u32Years++;
	}

}
