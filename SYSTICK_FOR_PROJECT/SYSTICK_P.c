



#include "SYSTICK_P.h"





/*Global Pointer to function used in systick callback and set callback*/
volatile void (*Ptr_func) (void) ;





/*TESTED*/
/*********************************************************************
 * Service Name: SysTick_Init
 * Sync/Async:
 * Reentrancy:
 * Parameters (in): uint16 a_TimeInMilliSeconds
 * Parameters (inout):
 * Parameters (out):
 * Return value: void
 * Description: Initialize the SysTick timer with the specified time in milliseconds using interrupts.
 * This function is used to setup the timer to generate periodic interrupts every specified time in milliseconds.
**********************************************************************/

void SysTick_Init(uint16 a_TimeInMilliSeconds)
{


       /*CLEARING THE ENABLE BIT TO TURN OFF SYSTICK WHILE INITIALIZING*/
       CLR_PIN(SYSTICK_CTRL_REG,PIN_NO_0);

       /*CLEAR THE COUNTER REGISTER*/
       SYSTICK_CURRENT_REG = 0 ;

       /*CHOOSING THE CLOCK SOURCE BY MACROS  ... SYSTEM CLOCK  / INTERNAL(16MHZ ) DIVIDED BY 4 */
       #if SYSTICK_CLK_SRC == SYSTEM_CLOCK

           SET_PIN(SYSTICK_CTRL_REG,PIN_NO_2);
       #elif SYSTICK_CLK_SRC == INTERNAL_OSC_DIVIDED_BY_4

           CLR_PIN(SYSTICK_CTRL_REG,PIN_NO_2);
       #endif

       /*ENABLE THE INTERRUPT MODE*/
       SET_PIN(SYSTICK_CTRL_REG,PIN_NO_1);

       /*Configuring The Priority Of The Systick Timer Interrupt is from nvic function set exception priority*/


       /*ENABLING THE SYSTICK TIMER*/
       SET_PIN(SYSTICK_CTRL_REG,PIN_NO_0);

       /*if the value of the time exceeds 1000 milli seconds we have to make a counter in the isr to check */
       /*RELOADING THE RELOAD REG WITH THE VALUE REQUIRED*/
       WRITE_REG( SYSTICK_RELOAD_REG , ((a_TimeInMilliSeconds * 16000) - 1) );






}


/*********************************************************************
 * Service Name:SysTick_StartBusyWait
 * Sync/Async:
 * Reentrancy:
 * Parameters (in):uint16 a_TimeInMilliSeconds
 * Parameters (inout):
 * Parameters (out):
 * Return value: void
 * Description:  Initialize the SysTick timer with the specified time in milliseconds using polling or busy-wait technique.
 *  The function should exit when the time is elapsed and stops the timer at the end.
**********************************************************************/

void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{

           /*CLEARING THE ENABLE BIT TO TURN OFF SYSTICK WHILE INITIALIZING*/
           CLR_PIN(SYSTICK_CTRL_REG,PIN_NO_0);

           /*CLEAR THE COUNTER REGISTER*/
           SYSTICK_CURRENT_REG = 0 ;

           /*CHOOSING THE CLOCK SOURCE BY MACROS  ... SYSTEM CLOCK  / INTERNAL(16MHZ ) DIVIDED BY 4 */
           #if SYSTICK_CLK_SRC == SYSTEM_CLOCK

               SET_PIN(SYSTICK_CTRL_REG,PIN_NO_2);
           #elif SYSTICK_CLK_SRC == INTERNAL_OSC_DIVIDED_BY_4

               CLR_PIN(SYSTICK_CTRL_REG,PIN_NO_2);
           #endif

           /*CHOOSDING THE INTERRUPT MODE .... ENABLE / DISABLE */

           #if INTERRUPT_MODE == ENABLE_INTERRUPT
               SET_PIN(SYSTICK_CTRL_REG,PIN_NO_1);
           #elif INTERRUPT_MODE == DISABLE_INTERRUPT
               CLR_PIN(SYSTICK_CTRL_REG,PIN_NO_1);
           #endif

           /*ENABLING THE SYSTICK TIMER*/
           SET_PIN(SYSTICK_CTRL_REG,PIN_NO_0);


           /*RELOADING THE RELOAD REG WITH THE VALUE REQUIRED*/
           uint32 number_of_counts_to_be_reloaded = 0 ;

           /*Assigning The Number Of Counts Have To Be Put In The Reload Register*/
           number_of_counts_to_be_reloaded = ( ( a_TimeInMilliSeconds * 16000 ) - 1 );

           /*IF THE VALUE EXCEEDS THE NUMBER OF COUNTS TO MAKE 1 SECOND SO WE HAVE TO PUT THE NUMBER OF COUNTS TO MAKE 1 SECOND INSTEAD */
           /*AND  We have to Make a Counter In The ISR To EXCUTE OUR ISR IN THE REQUIRED TIME*/
           if( number_of_counts_to_be_reloaded >= SYSTICK_MAX_RELOAD_N0_ )
           {
               WRITE_REG( SYSTICK_RELOAD_REG , SYSTICK_MAX_RELOAD_N0_ );
           }
           /*IF THE VALUE TO BE PUT IS LESS THAN REQUIRED COUNT TO MAKE ONE SECOND ....> WE WILL ASSIGN THE VALUE NORMALLY*/
           else if( number_of_counts_to_be_reloaded < SYSTICK_MAX_RELOAD_N0_ )
           {
               WRITE_REG( SYSTICK_RELOAD_REG , number_of_counts_to_be_reloaded );
           }

           /*Polling On the Flag till it finishes*/
           SYSTICK_vPolling_On_Count_Flag();

           /*Stop The Systick Timer At The End*/
           CLR_PIN(SYSTICK_CTRL_REG,PIN_NO_0);




}

/*********************************************************************
 * Service Name:SysTick_Handler
 * Sync/Async:
 * Reentrancy:
 * Parameters (in): void
 * Parameters (inout):
 * Parameters (out):
 * Return value: void
 * Description: Handler for SysTick interrupt use to call the call-back function.
**********************************************************************/
/*VALID*/
void SysTick_Handler(void)
{


/*IF YOUR RELOAD VALUE EXCEEDS 16 MILLION SO USE COUNTER TO MAKE SYSTICK EXCUTES YOUR ISR IN THE REQ TIME */


    /*Calling Function of callback*/
    Ptr_func ;


}

/*********************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async:
 * Reentrancy:
 * Parameters (in):
 * Parameters (inout):
 * Parameters (out):
 * Return value:
 * Description:
**********************************************************************/

void SysTick_SetCallBack(volatile void (*Ptr2Func) (void))
{



    Ptr_func = Ptr2Func ;



}

/*********************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async:
 * Reentrancy:
 * Parameters (in): void
 * Parameters (inout):
 * Parameters (out):
 * Return value: void
 * Description: Description: Stop the SysTick timer.
**********************************************************************/


void SysTick_Stop(void)
{

    /*STOP THE SYSTICK TIMER AT THE END*/
    CLR_PIN(SYSTICK_CTRL_REG,PIN_NO_0);


}

/*********************************************************************
 * Service Name: SysTick_Start
 * Sync/Async:
 * Reentrancy:
 * Parameters (in): void
 * Parameters (inout):
 * Parameters (out):
 * Return value: void
 * Description: Start/Resume the SysTick timer.
**********************************************************************/

void SysTick_Start(void)
{

    /*ENABLING THE SYSTICK TIMER*/
    SET_PIN(SYSTICK_CTRL_REG,PIN_NO_0);

}


/*********************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async:
 * Reentrancy:
 * Parameters (in):
 * Parameters (inout):
 * Parameters (out):
 * Return value:
 * Description: Function to De-initialize the SysTick Timer.
**********************************************************************/

void SysTick_DeInit(void)
{




}
