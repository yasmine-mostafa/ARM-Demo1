/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "STD_TYPES.h"
#include "SERVICE/SCHED/SCHED.h"


/********************************************************************************************************/
/************************************************externs*************************************************/
/********************************************************************************************************/

extern void CLCD_TASK(void);
extern void KPD_Runnable(void);
extern void DisplayDateTime(void);
extern void Sender_RunnableFunc(void);
extern void Receive_RunnableFunc(void);


/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
Runnable_tstr Runnables[_RUNNABLE_NUM]={
    [LCD_Runnable]={.PeriodicityMs=2,.FirstDelayMs=0,.CallBack=CLCD_TASK,.Priority=LCD_Runnable},
    [KPD_Runnables]={.PeriodicityMs=20,.FirstDelayMs=1,.CallBack=KPD_Runnable,.Priority=KPD_Runnables},
    [Display_Runnable]={.PeriodicityMs=500,.FirstDelayMs=5,.CallBack=DisplayDateTime,.Priority=Display_Runnable},
    [Sender_Runnable]={.PeriodicityMs=100,.FirstDelayMs=6,.CallBack=Sender_RunnableFunc,.Priority=Sender_Runnable},
    [Receiver_Runnable]={.PeriodicityMs=50,.FirstDelayMs=2,.CallBack=Receive_RunnableFunc,.Priority=Receiver_Runnable},


};
 

