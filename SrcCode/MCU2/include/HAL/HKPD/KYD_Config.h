/*
 * KYD_Config.h
 *
 *  Created on: Jan 6, 2024
 *      Author: DELL
 */

#ifndef HAL_KYD_KYD_CONFIG_H_
#define HAL_KYD_KYD_CONFIG_H_

/***************************************configuration parameters to keypad***********************************************/
/*number of rows*/
#define KPD_NUMBER_OF_ROWS              4
/*number of columns*/
#define KPD_NUMBER_OF_COLUMNS           4
/*The names of the switches in keypad*/
#define KPD_ARRAY                       {{'1','2','3','4'},{'5','6','7','8'},{'A','B','C','D'},{'E','F','G','H'}}
/*The sign that indicates there are no buttons pressed*/
#define KPD_NO_PRESSED_SWITCH           0xff


typedef struct
{
	u8  RowPinNumber[KPD_NUMBER_OF_ROWS];
	u8  RowPortNumber[KPD_NUMBER_OF_ROWS];
	u8  RowModePin[KPD_NUMBER_OF_ROWS];

	u8  ColPinNumber[KPD_NUMBER_OF_COLUMNS];
	u8  ColPortNumber[KPD_NUMBER_OF_COLUMNS];
	u8  ColModePin[KPD_NUMBER_OF_COLUMNS];

}tstr_KPDPinConfiguration;



#endif /* HAL_KYD_KYD_CONFIG_H_ */
