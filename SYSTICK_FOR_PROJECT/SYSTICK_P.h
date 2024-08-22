/*
 * SYSTICK_.h
 *
 *  Created on: Jul 28, 2024
 *      Author: Zyad Ayman
 */

#ifndef SYSTICK_P_H_
#define SYSTICK_P_H_


/**************************************************************************************************************************/
/*                                              # INCLUDES                                                                */
/**************************************************************************************************************************/




#include "tm4c123gh6pm_registers.h"
#include "std_types.h"
#include "Utils.h"





/**************************************************************************************************************************/
/*                                              FUNCTIONS PROTOTYPES                                                      */
/**************************************************************************************************************************/

/*Description: Initialize the SysTick timer with the specified time in milliseconds using interrupts. This function is used to setup the timer to generate periodic interrupts every specified time in milliseconds. */
void SysTick_Init(uint16 a_TimeInMilliSeconds) ;
/*Description: Initialize the SysTick timer with the specified time in milliseconds using polling or busy-wait technique. The function should exit when the time is elapsed and stops the timer at the end. */
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds) ;
/*Description: Handler for SysTick interrupt use to call the call-back function. */
void SysTick_Handler(void) ;
/*Description: Function to setup the SysTick Timer call back to be executed in SysTick Handler. */
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)) ;
/*Description: Stop the SysTick timer. */
void SysTick_Stop(void) ;
/*Description: Start/Resume the SysTick timer. */
void SysTick_Start(void) ;
/*Description: Function to De-initialize the SysTick Timer.*/
void SysTick_DeInit(void) ;

/**************************************************************************************************************************/
/*                                              # DEFINES    & CONFIGURATIONS                                                                        */
/**************************************************************************************************************************/

/*OPTIONS FOR CHOOSING CLOCK SOURCE */
#define SYSTICK_CLK_SRC SYSTEM_CLOCK
#define SYSTEM_CLOCK 1
#define INTERNAL_OSC_DIVIDED_BY_4 0

/*THIS MACRO USED FOR CONFIGURING WHETHER YOU WILL ENABLE OR DISABLE INTERRUPT*/
/*JUST ASSIGN TO INTERRUPT_MODE .....> DISABLE_INTERRUPT OR ENABLE_INTERRUPT*/
#define INTERRUPT_MODE DISABLE_INTERRUPT
/*TWO MODES YOU CHOOSE FROM THE AND ASSIGN IN THE ABOVE INTERRUPT_MODE */
#define ENABLE_INTERRUPT 1
#define DISABLE_INTERRUPT 0

/*MACRO FOR THE MAX NUMBER CAN BE RELOADED IN THE SYSTICK TIMER RELOAD REGISTER*/
#define SYSTICK_MAX_RELOAD_N0_ 15999999



/*************************************************************************************************************************/
                                        /*FUNCTIONS LIKE MACROS*/
/*************************************************************************************************************************/


/* MACRO FOR POLLING ON IT UNTIL FINISH DELAY */
#define SYSTICK_vPolling_On_Count_Flag() while(!READ_PIN(SYSTICK_CTRL_REG,BIT_NO_16))



/*Global Pointer to function used in systick callback and set callback*/
extern volatile void (*Ptr_func) (void) ;



#endif /* SYSTICK_P_H_ */
