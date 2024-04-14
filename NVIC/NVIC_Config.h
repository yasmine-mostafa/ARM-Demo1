/**************************************************************************************************************/
/* File Name:	NVIC_Cfg.h                                                                                    */
/* Module	: 	NVIC						                                                                  */
/* Layer	:	MCAL										                                                  */
/* AUTHOR   :   Lina Nassar                                                                                   */
/* Date     :   12/3/2024                                                                                     */
/**************************************************************************************************************/


#ifndef NVIC_CFG_H
#define NVIC_CFG_H

/*Implemented bits can vary from 3 to 8*/
#define NVIC_Implemented_Bits   4


/*Priority Group
-----------------------------------------------------------------
| Priority Group | Pre-empt Priority | Field Sub-priority Field |
|----------------|-------------------|--------------------------|
|   0 (default)  |    Bit [7:1]      |       Bit [0]            |
|   1            |    Bit [7:2]      |       Bit [1:0]          |
|   2            |    Bit [7:3]      |       Bit [2:0]          |
|   3            |    Bit [7:4]      |       Bit [3:0]          |
|   4            |    Bit [7:5]      |       Bit [4:0]          |
|   5            |    Bit [7:6]      |       Bit [5:0]          |
|   6            |    Bit [7]        |       Bit [6:0]          |
|   7            |    None           |       Bit [7:0]          |
-----------------------------------------------------------------
Choose from the following:
--------------------------
NVIC_PriorityGroup_1
NVIC_PriorityGroup_2
NVIC_PriorityGroup_3
NVIC_PriorityGroup_4
NVIC_PriorityGroup_5
NVIC_PriorityGroup_6
NVIC_PriorityGroup_7
*/
#define NVIC_PriorityGroup     NVIC_PriorityGroup_5

#endif