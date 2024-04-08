
#include"STD_TYPES.h"
#include"HKPD/KYD.h"
#include"MGPIO/GPIO.h"

#define THRESHOLD     5

extern tstr_KPDPinConfiguration KPD_Conf;
static u8 SwitchState[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS] ;

tenu_ErrorStatus KPD_INIT(void)
{

	GPIO_Pin_tstr Switch_Pin;
	Switch_Pin.Speed=GPIO_SPEED_HIGH;
	/*define variable to indicating the success or failure of the function */
	tenu_ErrorStatus Local_u8ErrorStatus = LBTY_OK;
	/*define variable to loop on all col pins and row pins */
	u8 Local_u8Index=0;
	/*define all col pin as output high */
	for(Local_u8Index=0;Local_u8Index<KPD_NUMBER_OF_COLUMNS;Local_u8Index++)
	{
		Switch_Pin.Mode=KPD_Conf.ColModePin[Local_u8Index];
		Switch_Pin.Pin=KPD_Conf.ColPinNumber[Local_u8Index];
		Switch_Pin.Port=KPD_Conf.ColPortNumber[Local_u8Index];
		MGPIO_InitPin(&Switch_Pin);
		MGPIO_SetPin(Switch_Pin.Port,Switch_Pin.Pin,GPIO_High);
	}
	/*define all row pin as input pull up */
	for(Local_u8Index=0;Local_u8Index<KPD_NUMBER_OF_ROWS;Local_u8Index++)
	{
		Switch_Pin.Mode=KPD_Conf.RowModePin[Local_u8Index];
		Switch_Pin.Pin=KPD_Conf.RowPinNumber[Local_u8Index];
		Switch_Pin.Port=KPD_Conf.RowPortNumber[Local_u8Index];
		MGPIO_InitPin(&Switch_Pin);
	}
	/*return value of Local_u8ErrorStatus variable */
	return Local_u8ErrorStatus;
}
/******************************************************************************************************************************/
void KPD_Runnable(void)
{
	u8 Local_Current;

	/*define variable to loop on all col pins */
	u8 Local_u8Index1=0;
	/*define variable to loop on all row pins */
	u8 Local_u8Index2=0;
	/*define variable to store pin value */
	u8 Local_u8PinValue=GPIO_High;

	static u8 Local_Prev[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS]={0};
	static u8 Local_Counts[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS]={0};

	/*local array to store keypad name that user entered it in configuration*/
	u8 Local_u8KpdArr[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS] = KPD_ARRAY;
	for(Local_u8Index1=0;Local_u8Index1<KPD_NUMBER_OF_COLUMNS;Local_u8Index1++)
	{
		/*define col pin as output low */
		MGPIO_SetPin(KPD_Conf.ColPortNumber[Local_u8Index1],KPD_Conf.ColPinNumber[Local_u8Index1],GPIO_Low);
		/*read the current row (pressed--->low) (not pressed--->high)*/
		for(Local_u8Index2=0;Local_u8Index2<KPD_NUMBER_OF_ROWS;Local_u8Index2++)
		{
			/*get pin value of current row */
			MGPIO_GetPinState(KPD_Conf.RowPortNumber[Local_u8Index2],KPD_Conf.RowPinNumber[Local_u8Index2],&Local_u8PinValue);
			/*check if switch is pressed */
			
			if(Local_Current==Local_Prev[Local_u8Index1][Local_u8Index2])
			{
				Local_Counts[Local_u8Index1][Local_u8Index2]++;
			}
			else
			{
				Local_Counts[Local_u8Index1][Local_u8Index2]=0;
			}
			if(Local_Counts[Local_u8Index1][Local_u8Index2]==THRESHOLD)
			{
				SwitchState[Local_u8Index1][Local_u8Index2]=Local_Current;
				Local_Counts[Local_u8Index1][Local_u8Index2]=0;
			}
			Local_Prev[Local_u8Index1][Local_u8Index2]=Local_Current;		
		}
		/*define col pin as output high */
		MGPIO_SetPin(KPD_Conf.ColPortNumber[Local_u8Index1],KPD_Conf.ColPinNumber[Local_u8Index1],GPIO_High);

	}

}
tenu_ErrorStatus KPD_GetPressedKey(u8 *Copy_pu8Key)
{
	u8 Local_Current;
	/*define variable to indicating the success or failure of the function */
	tenu_ErrorStatus Local_u8ErrorStatus = LBTY_OK;
	/*define variable to loop on all col pins */
	u8 Local_u8Index1=0;
	/*define variable to loop on all row pins */
	u8 Local_u8Index2=0;
	/*define variable to store pin value */
	u8 Local_u8PinValue=GPIO_High;

	static u8 Local_Prev[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS]={0};
	static u8 Local_Counts[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS]={0};
	/*check if a NULL pointer is provided as input*/
	if(Copy_pu8Key!=NULL){
	/*local array to store keypad name that user entered it in configuration*/
	u8 Local_u8KpdArr[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS] = KPD_ARRAY;
	for(Local_u8Index1=0;Local_u8Index1<KPD_NUMBER_OF_COLUMNS;Local_u8Index1++){
		/*define col pin as output low */
		Local_u8ErrorStatus=MGPIO_SetPin(KPD_Conf.ColPortNumber[Local_u8Index1],KPD_Conf.ColPinNumber[Local_u8Index1],GPIO_Low);
		/*read the current row (pressed--->low) (not pressed--->high)*/
		for(Local_u8Index2=0;Local_u8Index2<KPD_NUMBER_OF_ROWS;Local_u8Index2++)
		{
			/*get pin value of current row */
			Local_u8ErrorStatus=MGPIO_GetPinState(KPD_Conf.RowPortNumber[Local_u8Index2],KPD_Conf.RowPinNumber[Local_u8Index2],&Local_u8PinValue);
			/*check if switch is pressed */
			if(Local_Current==Local_Prev[Local_u8Index1][Local_u8Index2])
			{
				Local_Counts[Local_u8Index1][Local_u8Index2]++;
			}
			else
			{
				Local_Counts[Local_u8Index1][Local_u8Index2]=0;
			}
			if(Local_Counts[Local_u8Index1][Local_u8Index2]==THRESHOLD)
			{
				SwitchState[Local_u8Index1][Local_u8Index2]=Local_Current;
				Local_Counts[Local_u8Index1][Local_u8Index2]=0;
			}
			Local_Prev[Local_u8Index1][Local_u8Index2]=Local_Current;		
		}
		/*define col pin as output high */
		Local_u8ErrorStatus=MGPIO_SetPin(KPD_Conf.ColPortNumber[Local_u8Index1],KPD_Conf.ColPinNumber[Local_u8Index1],GPIO_High);

	}
	}
	else
	{
		/*if a NULL pointer is provided as input return NOK*/
		Local_u8ErrorStatus=LBTY_ErrorNullPointer;
	}
     /*return value of Local_u8ErrorStatus variable */
       return Local_u8ErrorStatus;
}
