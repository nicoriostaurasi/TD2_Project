/*--------------------------------------------------------------------*-

  monittor_lpc1769.c (Released 2019-04)

  --------------------------------------------------------------------

  MoniTTor mechanism (internal) for LPC1769. Uses Timer 0.

-*--------------------------------------------------------------------*/


// Project header
#include "../main/main.h"


// ------ Private variable definitions -----------------------------

// ID of task that is currently being monitored
static uint32_t Task_ID_G;
static uint32_t Task_BCET_G;
static uint32_t Task_t_variation_G;


/*--------------------------------------------------------------------*-

  MONITTOR_I_Init()

  Set up Timer 0 as MoniTTor unit.

-*--------------------------------------------------------------------*/
void MONITTOR_I_Init(void)
{

	// Power-on Timer 0
	Chip_TIMER_Init(LPC_TIMER0);

	//Change Timer PCLK.
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_TIMER0,SYSCTL_CLKDIV_1);

	// Initialize Timer 0, prescale counter = 1 μs
	Chip_TIMER_PrescaleSet(LPC_TIMER0,TIM_PRESCALE_USVAL-1);

	// Use channel 0, MR0
	Chip_TIMER_SetMatch(LPC_TIMER0,0,0);

	// Set timer flag when MR0 matches the value in TC register
	Chip_TIMER_MatchEnableInt(LPC_TIMER0,0);

	// Enable reset on MR0: timer will reset if MR0 matches it
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0,0);

	// Stop timer if MR0 matches it
	Chip_TIMER_StopOnMatchEnable(LPC_TIMER0,0);

	// IMPORTANT:
	// Interrupt priorities must be set in Scheduler init function
	// [Not yet started timer]
}


/*--------------------------------------------------------------------*-

  MONITTOR_I_Start()

  Start monitoring a task (call just before task is released).

  ALLOWED_TIMING_VARIATION_us gives some flexibility in both
  WCET and BCET measurements.

-*--------------------------------------------------------------------*/
void MONITTOR_I_Start(const uint32_t TASK_ID,
					  const uint32_t TASK_WCET_us,
					  const uint32_t TASK_BCET_us,
					  const uint32_t ALLOWED_TIMING_VARIATION_us)
{
	Task_ID_G = TASK_ID;
	Task_BCET_G = TASK_BCET_us;
	Task_t_variation_G = ALLOWED_TIMING_VARIATION_us;

	// Timeout value (in microseconds)
	Chip_TIMER_SetMatch(LPC_TIMER0, 0, TASK_WCET_us + ALLOWED_TIMING_VARIATION_us);

	// Enable interrupt for Timer 0
	Chip_TIMER_ClearMatch(LPC_TIMER0,0);
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);

	// Reset & Start timer
	Chip_TIMER_Reset(LPC_TIMER0);
	Chip_TIMER_Enable(LPC_TIMER0);
}


/*--------------------------------------------------------------------*-

  MONITTOR_I_Stop()

  Stop monitoring a task (call just after task completes).

  Task has not overrun - need to check for possible underrun.

-*--------------------------------------------------------------------*/
uint32_t MONITTOR_I_Stop(void)
{
	uint32_t Execution_time_us;
	sTask *actual;

	// Stop the timer
	Chip_TIMER_Disable(LPC_TIMER0);

	// Check BCET (read timer value)
	// This value is in microseconds
	Execution_time_us = Chip_TIMER_ReadCount(LPC_TIMER0);

	if ((Execution_time_us + Task_t_variation_G) < Task_BCET_G)
	{
		// Task has completed too quickly
		// => Change mode
		SYSTEM_Change_Mode_Fault(FAULT_TASK_TIMING);

		// Not storing task ID here
		// Not distinguishing BCET / WCET faults
		// => either / both this can be done here, if required
		actual = SCH_Get_Current_Task_Pointer();
		actual->Debug.BCET = Execution_time_us;
		actual->Debug.LET = Execution_time_us;
		actual->Debug.State |= SCH_DEBUG_TASK_UNDERRUN;
	}

	return Execution_time_us;
}


/*--------------------------------------------------------------------*-

  MONITTOR_I_Disable()

  Disable the MoniTTor unit.

  Typically used in the event of an unrelated fault, prior to mode
  change, to avoid MoniTTor ISR being triggered erroneously.

-*--------------------------------------------------------------------*/
void MONITTOR_I_Disable(void)
{
	// Stop the timer
	Chip_TIMER_Disable(LPC_TIMER0);

	// Disable interrupt for Timer 0
	NVIC_DisableIRQ(TIMER0_IRQn);
}


/*--------------------------------------------------------------------*-

  TIMER0_IRQHandler()

  [Function name determined by CMIS standard.]

  This is the task overrun ISR.

  It will be triggered only if the monitored task exceeds its
  allowed WCET (and allowed overrun period)

-*--------------------------------------------------------------------*/
void TIMER0_IRQHandler(void)
{
	sTask *actual;
	// if MR0 interrupt, proceed
	if(Chip_TIMER_MatchPending(LPC_TIMER0,0))
	{
		// Clear MR0 interrupt flag
		Chip_TIMER_ClearMatch(LPC_TIMER0,0);

		// Task has completed too slowly
		// => Change mode
		SYSTEM_Change_Mode_Fault(FAULT_TASK_TIMING);

		// Not storing task ID here
		// Not distinguishing BCET / WCET faults
		// => either / both this can be done here, if required
		actual = SCH_Get_Current_Task_Pointer();
		actual->Debug.LET = actual->WCET;
		actual->Debug.WCET = actual->WCET;
		actual->Debug.State |= SCH_DEBUG_TASK_OVERRUN;
	}
}


/*------------------------------------------------------------------*-
---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
