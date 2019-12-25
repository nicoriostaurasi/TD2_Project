/*
 * scheduler_lpc1769.h
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */

#ifndef C_TDS_SCHEDULER_LPC1769_H_
#define C_TDS_SCHEDULER_LPC1769_H_


/*------------------------------------------------------------------*-

    scheduler-lpc1769.h (Released 2019-03)

  ------------------------------------------------------------------

    See scheduler_lpc1769.c for details.

-*------------------------------------------------------------------*/

// ------ Public constants -----------------------------------------
// The maximum number of tasks required at any one time
// during the execution of the program
//
// MUST BE CHECKED FOR EACH PROJECT (*not* dynamic)
#define SCH_MAX_TASKS (20)

#define SCH_DEBUG_TASK_RUN_OK		(1<<0)
#define SCH_DEBUG_TASK_UNDERRUN		(1<<1)
#define SCH_DEBUG_TASK_OVERRUN		(1<<2)


// ------ Public data type -----------------------------------------
// User-define type to store required data for each task
typedef struct
{
    uint32_t WCET;
    uint32_t BCET;
    uint32_t LET;
    uint32_t RunTimes;
	uint32_t State;
} debugInfo;


typedef struct
{
    // Pointer to the task (must be a 'void (void)' function)
    void (*pTask) (void);
    // Delay (ticks) until the task will (next) be run
    // - see SCH_Add_Task() for further details
    uint32_t Delay;
    // Interval (ticks) between subsequent runs.
    // - see SCH_Add_Task() for further details
    uint32_t Period;
    // Worst-case execution time (microseconds)
    uint32_t WCET;
    // Best-case execution time (microseconds)
    uint32_t BCET;
    //Debug Info.
    debugInfo Debug;
} sTask;


// ------ Public function prototypes -------------------------------
void SCH_Init(const uint32_t TICKms);			// Tick interval (ms)
void SCH_Start(void);
void SCH_Dispatch_Tasks(void);

uint32_t SCH_Add_Task(void (* pTask)(),
                      const uint32_t DELAY,		// Offset (in ticks)
                      const uint32_t PERIOD,	// Ticks
                      const uint32_t WCET,		// Microseconds
                      const uint32_t BCET		// Microseconds
);

uint32_t SCH_Get_Current_Task(void);
sTask* SCH_Get_Current_Task_Pointer(void);


static INLINE void DWT_Init(void)
{
	DWT->CTRL |=DWT_CTRL_CYCCNTENA_Msk;
	DWT->CYCCNT=0;
}


static INLINE uint32_t DWT_GetTime(void)
{
	return (10 * DWT->CYCCNT);		// (10E9 / SystemCoreClock) => nS
}


static INLINE void DWT_Clear(void)
{
	DWT->CYCCNT=0;
}



/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/



#endif /* C_TDS_SCHEDULER_LPC1769_H_ */
