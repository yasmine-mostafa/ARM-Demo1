/**************************************************************************************************************/
/* File Name:	NVIC.h                                                                                        */
/* Module	: 	NVIC						                                                                  */
/* Layer	:	MCAL										                                                  */
/* AUTHOR   :   Lina Nassar                                                                                   */
/* Date     :   12/3/2024                                                                                     */
/**************************************************************************************************************/

#include "NVIC.h"

#define NVIC_Add    0xE000E100
#define SCB_AIRCR   (*((volatile uint32_t * const)(0xE000ED0C)))

#define NVIC_ImplementedBits               Reg_Offset_4bit
#define NVIC_SCBAIRCIR_PriorGroupingMask   0x07FF0000  //Masks Priority Grouping bits & VECTKEY bits
#define NVIC_SCBAIRCIR_VECTKEY             0x05FA0000
#define NVIC_SCBAIRCR_PRIGROUP_OFFSET      Reg_Offset_8bit



typedef struct{
    uint32_t ISER[8];
    uint32_t reserved0[24];
    uint32_t ICER[8];
    uint32_t reserved1[24];
    uint32_t ISPR[8];
    uint32_t reserved2[24];
    uint32_t ICPR[8];
    uint32_t reserved3[24];
    uint32_t IABR[8];
    uint32_t reserved4[56];
    uint8_t  IPR[240];
    uint32_t reserved5[644];
    uint32_t STIR;
}NVIC_Reg_t;

/*Global Variables*/
static volatile NVIC_Reg_t * const NVIC = (volatile NVIC_Reg_t * const)(NVIC_Add);
static uint8_t NVIC_PriorityGroup = NVIC_PriorityGroup_0;


/*Static Functions*/
/**
 *@brief  : This function generates the priority the should be assigned to the NVIC->IPR based on the Priority 
 *          group global variable and Preempt and sub-priority parameters passed over from SetPriority function.
 *@param  : pEncodedPriority: pointer to the variable in which the encoded priority is returned.
 *        : PreemptPriority value to be assigned to its bits in NVIC->IPR Register
 *        : Sub-priority value to be assigned to its bits in NVIC->IPR Register
 *@return : NVIC Error Status               
 */
static NVIC_errors_t NVIC_EncodePriority (uint32_t *pEncodedPriority, uint8_t PreemptPriority, uint8_t Subpriority)
{
    NVIC_errors_t Ret_EncPrior = NVIC_enuNOk;

    /*Paramater Check*/
    if(pEncodedPriority== NULL)
    {
        Ret_EncPrior=NVIC_enuNullPtr;         
    }
    else if( (PreemptPriority>(1<<(NVIC_ImplementedBits - NVIC_PriorityGroup))) || (Subpriority>(1<<(NVIC_PriorityGroup))) )
    {
        Ret_EncPrior=NVIC_enuNullPtr;
    }
    else
    {
        *pEncodedPriority = ((PreemptPriority<<NVIC_PriorityGroup)<<NVIC_ImplementedBits) ;
    }
    return Ret_EncPrior;

}
// static void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t *PreemptPriority, uint32_t *pSubpriority)
// {

// }


/*Functions Implementations*/

NVIC_errors_t NVIC_SetPriority(NVIC_Interrupts_t IRQn, uint8_t PremptPriority, uint8_t SubPriority)
{
    NVIC_errors_t Ret_SetPrior = NVIC_enuNOk;
    uint32_t Loc_EncodedPriority;
    

    if( (IRQn < 0) || (IRQn > _NVIC_IRQCount))
    {
        Ret_SetPrior = NVIC_enuWrongIRQ;
    }
    else
    {
        Ret_SetPrior = NVIC_EncodePriority(&Loc_EncodedPriority, PremptPriority, SubPriority);
    }
    if (Ret_SetPrior == NVIC_enuOk)
    {
        NVIC->IPR[IRQn] = (Loc_EncodedPriority << NVIC_ImplementedBits); 
    }
    return Ret_SetPrior;  
}




NVIC_errors_t NVIC_EnableIRQ(NVIC_Interrupts_t IRQn)
{
    NVIC_errors_t Ret_EnIRQ = NVIC_enuNOk;
    uint8_t Loc_RegIdx, Loc_BitIdx;
    
    if(!((IRQn <_NVIC_IRQCount) && (IRQn>= 0)))
    {
        Ret_EnIRQ = NVIC_enuWrongIRQ;
    } 
    else if (Ret_EnIRQ == NVIC_enuOk)
    {
        Loc_RegIdx = IRQn/32;
        Loc_BitIdx = IRQn%32;

        NVIC->ISER[Loc_RegIdx] |= (1 << Loc_BitIdx);
    }
    return Ret_EnIRQ;  
}


NVIC_errors_t NVIC_DisableIRQ(NVIC_Interrupts_t IRQn)
{
    NVIC_errors_t Ret_DisIRQ = NVIC_enuNOk;
    uint8_t Loc_RegIdx, Loc_BitIdx;
    
    if(!((IRQn <_NVIC_IRQCount) && (IRQn>= 0)))
    {
        Ret_DisIRQ = NVIC_enuWrongIRQ;
    } 
    else if (Ret_DisIRQ == NVIC_enuOk)
    {
        Loc_RegIdx = IRQn/32;
        Loc_BitIdx = IRQn%32;

        NVIC->ICER[Loc_RegIdx] |= (1 << Loc_BitIdx);
    }
    return Ret_DisIRQ;  
}


NVIC_errors_t NVIC_SetPendingIRQ(NVIC_Interrupts_t IRQn)
{
    NVIC_errors_t Ret_SetPendRQ = NVIC_enuNOk;
    uint8_t Loc_RegIdx, Loc_BitIdx;
    
    if(!((IRQn <_NVIC_IRQCount) && (IRQn>= 0)))
    {
        Ret_SetPendRQ = NVIC_enuWrongIRQ;
    } 
    else if (Ret_SetPendRQ == NVIC_enuOk)
    {
        Loc_RegIdx = IRQn/32;
        Loc_BitIdx = IRQn%32;

        NVIC->ISPR[Loc_RegIdx] |= (1 << Loc_BitIdx);
    }
    return Ret_SetPendRQ;  
}


NVIC_errors_t NVIC_ClearPendingIRQ(NVIC_Interrupts_t IRQn)
{
    NVIC_errors_t Ret_CLrPendIRQ = NVIC_enuNOk;
    uint8_t Loc_RegIdx, Loc_BitIdx;
    
    if(!((IRQn <_NVIC_IRQCount) && (IRQn>= 0)))
    {
        Ret_CLrPendIRQ = NVIC_enuWrongIRQ;
    } 
    else if (Ret_CLrPendIRQ == NVIC_enuOk)
    {
        Loc_RegIdx = IRQn/32;
        Loc_BitIdx = IRQn%32;

        NVIC->ICPR[Loc_RegIdx] |= (1 << Loc_BitIdx);
    }
    return Ret_CLrPendIRQ;  
}

NVIC_errors_t NVIC_GetPendingIRQ(NVIC_Interrupts_t IRQn, uint32_t *IRQPendingStatus)
{
    NVIC_errors_t Ret_GetPendRQ = NVIC_enuNOk;
    uint8_t Loc_RegIdx, Loc_BitIdx;
    

    if(!((IRQn <_NVIC_IRQCount) && (IRQn>= 0)))
    {
        Ret_GetPendRQ = NVIC_enuWrongIRQ;
    }
    else if(IRQPendingStatus == NULL)
    {
        Ret_GetPendRQ = NVIC_enuNullPtr;
    } 
    else if (Ret_GetPendRQ == NVIC_enuOk)
    {
        Loc_RegIdx = IRQn/32;
        Loc_BitIdx = IRQn%32;

        *IRQPendingStatus= ((NVIC->ISPR[Loc_RegIdx] >>Loc_BitIdx) & 0x01);
    }
    return Ret_GetPendRQ;  
}


NVIC_errors_t NVIC_GetActive(NVIC_Interrupts_t IRQn, uint32_t *IRQActiveStatus)
{
    NVIC_errors_t Ret_DisIRQ = NVIC_enuNOk;
    uint8_t Loc_RegIdx, Loc_BitIdx;
    

    if(!((IRQn <_NVIC_IRQCount) && (IRQn>= 0)))
    {
        Ret_DisIRQ = NVIC_enuWrongIRQ;
    }
    else if(IRQActiveStatus == NULL)
    {
        Ret_DisIRQ = NVIC_enuNullPtr;
    } 
    else if (Ret_DisIRQ == NVIC_enuOk)
    {
        Loc_RegIdx = IRQn/32;
        Loc_BitIdx = IRQn%32;

        *IRQActiveStatus= ((NVIC->IABR[Loc_RegIdx] >>Loc_BitIdx) & 0x01);
    }
    return Ret_DisIRQ;  
}



// NVIC_errors_t NVIC_GetPriority(NVIC_Interrupts_t IRQn)
// {

// }


NVIC_errors_t NVIC_SetPriorityGrouping(uint32_t NIVC_PriorityGrouping)
{
    NVIC_errors_t Ret_SetPriorGroup = NVIC_enuNOk;
    uint32_t Loc_RegisterTempVal;
    

    if((NIVC_PriorityGrouping < NVIC_PriorityGroup_0) || (NIVC_PriorityGrouping > NVIC_PriorityGroup_7) )
    {
        Ret_SetPriorGroup = NVIC_enuWrongPriorityGrouping;
    }
    else if (Ret_SetPriorGroup == NVIC_enuOk)
    {
        NVIC_PriorityGroup  = NIVC_PriorityGrouping;
        Loc_RegisterTempVal = SCB_AIRCR;
        Loc_RegisterTempVal &= (~NVIC_SCBAIRCIR_PriorGroupingMask);
        Loc_RegisterTempVal |= (NVIC_SCBAIRCIR_VECTKEY | (NIVC_PriorityGrouping << NVIC_SCBAIRCR_PRIGROUP_OFFSET));
        SCB_AIRCR = Loc_RegisterTempVal;
    }
    return Ret_SetPriorGroup;  
}