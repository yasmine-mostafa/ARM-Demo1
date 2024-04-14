/**************************************************************************************************************/
/* File Name:	NVIC.h                                                                                        */
/* Module	: 	NVIC						                                                                  */
/* Layer	:	MCAL										                                                  */
/* AUTHOR   :   Lina Nassar                                                                                   */
/* Date     :   12/3/2024                                                                                     */
/**************************************************************************************************************/

#include "Libraries/STD_Types.h"
#include "Libraries/Masks.h"
#include "STM32F401_Interrupts.h"


/*Priority Group
----------------------------------------------------------------
| Priority Group | Preempt Priority | Field Sub-priority Field |
|----------------|------------------|--------------------------|
|   0(default)   |    Bit [7:4]     |       None               |
|   4            |    Bit [7:5]     |       Bit [4]          |
|   5            |    Bit [7:6]     |       Bit [5:4]          |
|   6            |    Bit [7]       |       Bit [6:4]          |
|   7            |    None          |       Bit [7:4]          |
--------------------------------------------------------------*/
#define NVIC_PriorityGroup_0    0 
#define NVIC_PriorityGroup_4    1
#define NVIC_PriorityGroup_5    2
#define NVIC_PriorityGroup_6    3
#define NVIC_PriorityGroup_7    4


typedef enum
{
    NVIC_enuOk,
    NVIC_enuNOk,
    NVIC_enuWrongIRQ,
    NVIC_enuNullPtr,
    NVIC_enuWrongPriority,
    NVIC_enuWrongPriorityGrouping

}NVIC_errors_t;


NVIC_errors_t NVIC_EnableIRQ(NVIC_Interrupts_t IRQn); 

NVIC_errors_t NVIC_DisableIRQ(NVIC_Interrupts_t IRQn); 

NVIC_errors_t NVIC_SetPendingIRQ(NVIC_Interrupts_t IRQn); 

NVIC_errors_t NVIC_ClearPendingIRQ(NVIC_Interrupts_t IRQn); 

NVIC_errors_t NVIC_GetPendingIRQ(NVIC_Interrupts_t IRQn, uint32_t *IRQPendingStatus); 

NVIC_errors_t NVIC_GetActive(NVIC_Interrupts_t IRQn, uint32_t *IRQActiveStatus); 

NVIC_errors_t NVIC_SetPriority(NVIC_Interrupts_t IRQn, uint8_t PremptPriority, uint8_t SubPriority);

NVIC_errors_t NVIC_GetPriority(NVIC_Interrupts_t IRQn);

NVIC_errors_t NVIC_SetPriorityGrouping(uint32_t Priority_Grouping); 

//NVIC_errors_t NVIC_SystemReset(void);
