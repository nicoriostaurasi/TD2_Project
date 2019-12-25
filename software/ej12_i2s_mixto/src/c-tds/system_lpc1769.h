/*
 * system_lpc1796.h
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */

#ifndef C_TDS_SYSTEM_LPC1769_H_
#define C_TDS_SYSTEM_LPC1769_H_

/*------------------------------------------------------------------*-

    system_lpc1769.h (Released 2019-03)

  ------------------------------------------------------------------

    See system_lpc1769.c for details.

-*------------------------------------------------------------------*/

// ------ Public constants -----------------------------------------
// Required system operating frequency (in Hz)
// Will be checked in the scheduler initialization file
#define Required_SystemCoreClock (96000000)	// 96MHz

#define SysTick_RateHz	(1000000)				// 1000 ticks per second

#define SysTick_RatemS	(1000 / SysTick_RateHz)		// 1mS
#define SysTick_RateuS	(1000 * SysTick_RatemS)		// 1000uS

#define WatchDog_RateuS ((11 * SysTick_RateuS)/10)	// 1100uS


//------------------------------------------------------------------
// System fault codes
//------------------------------------------------------------------

// Scheduler fault codes
#define FAULT_SCH_TOO_MANY_TASKS (1)
#define FAULT_SCH_ONE_SHOT_TASK (2)

// Other fault codes may be added here, if required

//------------------------------------------------------------------
// Project constants
//------------------------------------------------------------------

#define RETURN_NORMAL 0
#define RETURN_FAULT 1


// Three possible system modes
typedef enum {FAIL_SILENT, NORMAL, FAULT_TASK_TIMING} eSystem_mode;


// ------ Public data type declarations ----------------------------


// ------ Public function prototypes -------------------------------
void SYSTEM_Init(void);
void SYSTEM_Perform_Safe_Shutdown(void);
void SYSTEM_Change_Mode_Fault(eSystem_mode mode);
eSystem_mode SYSTEM_Get_Mode(void);



/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/


#endif /* C_TDS_SYSTEM_LPC1769_H_ */
