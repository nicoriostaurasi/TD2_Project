/*
 * scheduler_lpc1769.c
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */
/*--------------------------------------------------------------------*-

    scheduler_lpc1769.c (Released 2019-03)

--------------------------------------------------------------------

    Co-operative - Time Driven System (C-TDS) task scheduler for LPC1769.

-*--------------------------------------------------------------------*/


// Project header
#include "../main/main.h"
#include <string.h>


// ------ Public variable definitions ------------------------------

// May be used (for example) to report faults using Heartbeat LED
// See Heartbeat task (if used) for basic fault-reporting mechanism
uint32_t Fault_code_G;


// ------ Private variable definitions -----------------------------
// The array of tasks
// Check array size in scheduler header file
sTask SCH_tasks_G[SCH_MAX_TASKS];

// The current tick count
static volatile uint32_t Tick_count_G = 0;

static volatile uint32_t ITask;


// ------ Private constant definitions -----------------------------
#define	ALLOWED_TIMING_VARIATION_us (20)


// ------ Private function prototypes ------------------------------
static void SCH_Go_To_Sleep(void);

void SysTick_Handler(void);


/*------------------------------------------------------------------*-

    SCH_Init()

    Scheduler initialization function. Prepares scheduler
    data structures and sets up timer interrupts every TICKms
    milliseconds.

    You must call this function before using the scheduler.

    [Required_SystemCoreClock frequency can be found in
    system_lpc1769.h.]

-*------------------------------------------------------------------*/
void SCH_Init(const uint32_t TICKms)
{
    uint32_t i;
    // Reset the global fault variable
    Fault_code_G = 0;

    for (i = 0; i < SCH_MAX_TASKS; i++)
    {
    	SCH_tasks_G[i].pTask = 0;
    	memset(&(SCH_tasks_G[i].Debug),0,sizeof(debugInfo));
    }

    // Using LPCOpen

    // Must check board oscillator frequency, etc
    //
    // *If* these values have been set correctly for your hardware
    // SystemCoreClock gives the system operating frequency (in Hz)
    if (SystemCoreClock != Required_SystemCoreClock)
    {
    	// Fatal fault
    	SYSTEM_Perform_Safe_Shutdown();
    }

    // Now to set up SysTick timer for "ticks" at interval TICKms
    if (SysTick_Config(TICKms * SystemCoreClock / SysTick_RateHz))
    {
    	// Fatal fault
    	SYSTEM_Perform_Safe_Shutdown();
    }

    NVIC_SetPriority(SysTick_IRQn, 0x0);

    // Timer is started by SysTick_Config():
    // we need to disable SysTick timer and SysTick interrupt until
    // all tasks have been added to the schedule.
    SysTick->CTRL &= 0xFFFFFFFC;

    // Inicialize Data Watchpoint and Trace System Clock Counter
    DWT_Init();
}


/*------------------------------------------------------------------*-

    SCH_Start()

    Starts the scheduler, by enabling SysTick interrupt.

    NOTES:
    * All tasks must be added before starting scheduler.
    * Any other interrupts MUST be synchronized to this tick.

-*------------------------------------------------------------------*/
void SCH_Start(void)
{
    // Enable SysTick timer
    SysTick->CTRL |= 0x01;

    // Enable SysTick interrupt
    SysTick->CTRL |= 0x02;
}


/*------------------------------------------------------------------*-

    SysTick_Handler()

    [Function name determined by CMIS standard.]
    This is the scheduler ISR. It is called at a rate
    determined by the timer settings in the SCH_Init() function.

-*------------------------------------------------------------------*/
void SysTick_Handler(void)
{
    // Increment tick count (only)
    Tick_count_G++;
}


/*------------------------------------------------------------------*-
    SCH_Dispatch_Tasks()

    This is the 'dispatcher' function. When a task (function)
    is due to run, SCH_Dispatch_Tasks() will run it.
    This function must be called (repeatedly) from the main loop.

-*------------------------------------------------------------------*/
#define TEST_1 (1)	/* Test one task */
#define TEST_2 (2)	/* Test more than one task */
#define TEST_3 (3)	/* Test monittor */

#define TEST (TEST_3)


#if (TEST == TEST_1)	/* Test one task */
void SCH_Dispatch_Tasks(void)
{
    uint32_t Index;
    uint32_t Update_required = 0;

    __disable_irq(); // Protect shared resource (Tick_count_G)
    if (Tick_count_G > 0)
        {
        Tick_count_G--;
        Update_required = 1;
    }
    __enable_irq();

    while (Update_required)
    {
        // Go for the 1st task of the task array
    	Index = 0;

    	// Check if there is a task at this location
        if (SCH_tasks_G[Index].pTask)
        {
        	ITask = Index;

            (*SCH_tasks_G[Index].pTask)(); // Run the task

            // All tasks are periodic in this design
			// - schedule task to run again
			SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
        }

        __disable_irq(); // Protect shared resource (Tick_count_G)
        if (Tick_count_G > 0)
        {
            Tick_count_G--;
            Update_required = 1;
        }
        else
        {
            Update_required = 0;
        }
        __enable_irq();
	}

	if(SYSTEM_Get_Mode() == FAIL_SILENT)
	{
		SYSTEM_Perform_Safe_Shutdown();
	}

	SCH_Go_To_Sleep();
}
#endif

#if (TEST == TEST_2)	/* Test more than one task */
void SCH_Dispatch_Tasks(void)
{
    uint32_t Index;
    uint32_t Update_required = 0;

    __disable_irq(); // Protect shared resource (Tick_count_G)
    if (Tick_count_G > 0)
        {
        Tick_count_G--;
        Update_required = 1;
    }
    __enable_irq();

    while (Update_required)
        {
        // Go through the task array
        for (Index = 0; Index < SCH_MAX_TASKS; Index++)
            {
            // Check if there is a task at this location
            if (SCH_tasks_G[Index].pTask)
                {
                if (--SCH_tasks_G[Index].Delay == 0)
                    {
                		ITask = Index;

						(*SCH_tasks_G[Index].pTask)(); // Run the task

						// All tasks are periodic in this design
						// - schedule task to run again

						SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
                    }
                }
            }
        __disable_irq();
        if (Tick_count_G > 0)
            {
            Tick_count_G--;
            Update_required = 1;
            }
        else
            {
            Update_required = 0;
            }
        __enable_irq();
        }

		if(SYSTEM_Get_Mode() == FAIL_SILENT)
		{
			SYSTEM_Perform_Safe_Shutdown();
		}

        SCH_Go_To_Sleep();
    }
#endif


#if (TEST == TEST_3)	/* Test monittor */
void SCH_Dispatch_Tasks(void)
{
    uint32_t Index;
    uint32_t Update_required = 0;
    uint32_t time_SCH;

    __disable_irq(); // Protect shared resource (Tick_count_G)
    if (Tick_count_G > 0)
        {
        Tick_count_G--;
        Update_required = 1;
    }
    __enable_irq();

    while (Update_required)
        {
        // Go through the task array
        for (Index = 0; Index < SCH_MAX_TASKS; Index++)
            {
            // Check if there is a task at this location
            if (SCH_tasks_G[Index].pTask)
                {
                if (--SCH_tasks_G[Index].Delay == 0)
                    {
            			// Start of Task Dispatch Time Measurement
            			DWT_Clear();

            			ITask = Index;
                		SCH_tasks_G[Index].Debug.State = 0;

						MONITTOR_I_Start(	(uint32_t)SCH_tasks_G[Index].pTask,
											SCH_tasks_G[Index].WCET,
											SCH_tasks_G[Index].BCET,
											ALLOWED_TIMING_VARIATION_us);

						(*SCH_tasks_G[Index].pTask)(); // Run the task

						// All tasks are periodic in this design
						// - schedule task to run again

						SCH_tasks_G[Index].Debug.LET = MONITTOR_I_Stop();
						SCH_tasks_G[Index].Debug.State |= SCH_DEBUG_TASK_RUN_OK;
						SCH_tasks_G[Index].Debug.RunTimes++;

						if(SCH_tasks_G[Index].Debug.LET < SCH_tasks_G[Index].Debug.BCET)
							SCH_tasks_G[Index].Debug.BCET = SCH_tasks_G[Index].Debug.LET;

						if(SCH_tasks_G[Index].Debug.LET > SCH_tasks_G[Index].Debug.WCET)
							SCH_tasks_G[Index].Debug.WCET = SCH_tasks_G[Index].Debug.LET;

						SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;

                		// Stop of Task Dispatch Time Measurement
						time_SCH = DWT_GetTime()/1000 - SCH_tasks_G[Index].Debug.LET;
                    }
                }
            }
        __disable_irq();
        if (Tick_count_G > 0)
            {
            Tick_count_G--;
            Update_required = 1;
            }
        else
            {
            Update_required = 0;
            }
        __enable_irq();
        }

		if(SYSTEM_Get_Mode() == FAIL_SILENT)
		{
			MONITTOR_I_Disable();
			SYSTEM_Perform_Safe_Shutdown();
		}

        SCH_Go_To_Sleep();
    }
#endif

/*------------------------------------------------------------------*-
    SCH_Add_Task()

    Causes a task (function) to be executed at regular intervals.

    pTask - The name of the task (function) to be scheduled.
            NOTE: All scheduled functions must be 'void, void' -
            that is, they must take no parameters, and have
            a void return type (in this design).

    DELAY - The interval (ticks) before the task is first executed.

    PERIOD - Task period (in ticks). Must be > 0.

    WCET - Worst-Case Execution Time (microseconds)
           [Used only for documentation in this design.]

    BCET - Best-Case Execution Time (microseconds)
           [Used only for documentation in this design.]

    RETURN VALUE:
    Returns the position in the task array at which the task has been
    added. If the return value is SCH_MAX_TASKS then the task could
    not be added to the array (there was insufficient space, or the
    requested task period was 0).
    If the return value is < SCH_MAX_TASKS, then the task was added
    successfully.

    Note: this return value may be used (in later designs) to
    support the use of backup tasks.

-*------------------------------------------------------------------*/

#if (TEST == TEST_1)	/* Test one task */
uint32_t SCH_Add_Task(void (* pTask)(),
                      const uint32_t DELAY,
                      const uint32_t PERIOD,
                      const uint32_t WCET,
                      const uint32_t BCET
                      )
{
    uint32_t Index = 0;

	SCH_tasks_G[Index].pTask = pTask;

    SCH_tasks_G[Index].Delay = DELAY + 1;
    SCH_tasks_G[Index].Period = PERIOD;
    SCH_tasks_G[Index].WCET = WCET;
    SCH_tasks_G[Index].BCET = BCET;

    return Index;
}
#endif

#if (TEST != TEST_1) 	/* Test more than one task or Test monittor */
uint32_t SCH_Add_Task(void (* pTask)(),
                      const uint32_t DELAY,
                      const uint32_t PERIOD,
                      const uint32_t WCET,
                      const uint32_t BCET
                      )

    {
    uint32_t Return_value = 0;
    uint32_t Index = 0;

    // First find a gap in the array (if there is one)
    while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
        {
        Index++;
    }

    // Have we reached the end of the list?
    if (Index == SCH_MAX_TASKS)
        {
        // Task list is full
        //
        // Set the global fault variable
        Fault_code_G = FAULT_SCH_TOO_MANY_TASKS;

        // Also return a fault code
        Return_value = SCH_MAX_TASKS;
        }

    // Check for "one shot" tasks
    // - not permitted in this design
    if (PERIOD == 0)
        {
        // Set the global fault variable
        Fault_code_G = FAULT_SCH_ONE_SHOT_TASK;

        // Also return a fault code
        Return_value = SCH_MAX_TASKS;
        }

    if (Return_value != SCH_MAX_TASKS)
        {

        // If we're here, there is a space in the task array
        // and the task to be added is periodic
        SCH_tasks_G[Index].pTask = pTask;

        SCH_tasks_G[Index].Delay = DELAY + 1;
        SCH_tasks_G[Index].Period = PERIOD;
        SCH_tasks_G[Index].WCET = WCET;
        SCH_tasks_G[Index].BCET = BCET;

        Return_value = Index;
        }

    return Return_value;
    }
#endif

/*------------------------------------------------------------------*-

    SCH_Go_To_Sleep()

    This scheduler enters 'sleep mode' between clock ticks
    to [i] reduce tick jitter; and [ii] save power.

    The next clock tick will return the processor
    to the normal operating state.

    Note: a slight performance improvement may be achieved
    if this code is pasted into the 'Dispatch' function
    (this may be at the cost of code readability & portability)

    *** May be able to make further improvements to the jitter
    *** behaviour depending on the target hardware architecture

    *** Various power-saving options can be added
    *** (e.g. shut down unused peripherals)

-*------------------------------------------------------------------*/
void SCH_Go_To_Sleep()
    {
    // Enter sleep mode = "Wait For Interrupt"
    __WFI();
    }


uint32_t SCH_Get_Current_Task(void)
{
	return	ITask;
}


sTask* SCH_Get_Current_Task_Pointer(void)
{
	return &SCH_tasks_G[ITask];
}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/


