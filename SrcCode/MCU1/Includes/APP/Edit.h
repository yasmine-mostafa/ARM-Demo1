/*
 * Edit.h
 *
 *  Created on: Apr 8, 2024
 *      Author: top one
 */

#ifndef APP_INCLUDES_EDIT_H_
#define APP_INCLUDES_EDIT_H_

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
	EditON,
	EditOFF
}EditState_t;


#endif /* APP_INCLUDES_EDIT_H_ */
