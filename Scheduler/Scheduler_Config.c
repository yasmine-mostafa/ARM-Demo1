/***********************************************************************************************/
/* File Name:	Scheduler_Config.c                                                             */
/* Module	: 	Scheduler						                                               */
/* Layer	:	Scheduler										                               */
/* AUTHOR   :   Lina Nassar                                                                    */
/***********************************************************************************************/

#include "Scheduler_Config.h"
#include "Scheduler.h"

/*Add prototypes of the runnables here
*   Example: extern void Run_1(void); */

extern void Traffic_Lights(void);
extern void Toggle_Led(void);

/*Add each of the runnables to the array and fill its required fields*/
/*  Example: 
        [Run_1]=
        {
            .name= "Run_1"   ,
            .Priority= 1     ,
            .cb = Run1_cb    ,    
            .FirstDelayMS= 15,   
            .PeriodicityMS= 5,
        },
*/
const Runnable_t Runnable[_Runnables_Num]=
{
    [0]=
    {
        .name= "Toggle",
        .Priority= 0,
        .cb = Toggle_Led,    
        .FirstDelayMS= 0,
        .PeriodicityMS= 250,
    },
    // [Switch_Led]=
    // {
    //     .name= "Led1",
    //     .Priority= 0,
    //     .cb = Toggle_Led,    
    //     .FirstDelayMS= 10,
    //     .PeriodicityMS= 50,
    // },
    // [Switch_Runn]=
    // {
    //     .name= "Led1",
    //     .Priority= 0,
    //     .cb = Toggle_Led,    
    //     .FirstDelayMS= 0,
    //     .PeriodicityMS= 1 ,
    // },

};
