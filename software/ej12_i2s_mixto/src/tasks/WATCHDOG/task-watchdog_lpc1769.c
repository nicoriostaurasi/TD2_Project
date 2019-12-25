/*
 * task-watchdog_lpc1769.c
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */


/*--------------------------------------------------------------------*-

    task-watchdog_lpc1769.c (Released 2015-04)

  --------------------------------------------------------------------

    'Watchdog' library for LPC1769.
    ** Jumper controlled (see below) **

-*--------------------------------------------------------------------*/


// Project header
#include "../../main/main.h"


// Task header
#include "task-watchdog_lpc1769.h"


// ------ Public variable declarations -----------------------------
// See scheduler module for definition
extern uint32_t Fault_code_G;


/*------------------------------------------------------------------*-

    WATCHDOG_Init()

    Set up watchdog timer on LPC1769.

    *****************************************************************
    * Handle with care - if WDT is running, debug links may be lost *
    * In this design, WDT is enable only when jumper is inserted.   *
    *****************************************************************

    The watchdog timer is driven by the Internal RC Oscillator:
    the minimum available timeout is 256 microS.

-*------------------------------------------------------------------*/
void WATCHDOG_Init(const uint32_t WDT_TIMEOUTus)
{
    uint32_t wdt_ticks = 0;
    bool Jumper_input;

    // *If* WDT jumper is in place, we start the WDT
    // Read WDT jumper setting
    // Set up jumper pin for input
	Chip_IOCON_PinMux(LPC_IOCON, WDT_JUMPER_PORT, WDT_JUMPER_PIN, WDT_JUMPER_PIN_MODE, WDT_JUMPER_PIN_FUNC);
    Chip_GPIO_SetPinDIRInput(LPC_GPIO, WDT_JUMPER_PORT, WDT_JUMPER_PIN);

    // Note: we only read the jumper during system init phase
    Jumper_input = Chip_GPIO_ReadPortBit(LPC_GPIO, WDT_JUMPER_PORT,WDT_JUMPER_PIN); //Chip_GPIO_ReadDirBit(LPC_GPIO, WDT_JUMPER_PORT, WDT_JUMPER_PIN);

    if (Jumper_input != WDT_JUMPER_INSERTED)
    {
        // Jumper not inserted - don't enable WDT
        return;
    }

    // If we are here, we are setting up the WDT
    // Drive WDT from internal RC timer (IRC)
    Chip_WWDT_SelClockSource(LPC_WWDT, WWDT_CLKSRC_IRC);

    // Calculate required tick count for WDT timeout
    wdt_ticks = (((WDT_PCLK) / WDT_US_INDEX) * (WDT_TIMEOUTus / 4));

    // Check if tick count is within allowed range
    if ((wdt_ticks >= WDT_TIMEOUT_MIN) && (wdt_ticks <= WDT_TIMEOUT_MAX))
    {
    	// LPC_WDT->WDTC = wdt_ticks;
    	Chip_WWDT_SetTimeOut(LPC_WWDT, wdt_ticks);
    }
    else
    {
        // We simply "stop" if WDT values are wrong
        // - other solutions may make sense for your application
        // - for example, use closest available timeout.
        while(1);
    }

    /* Configure WWDT to reset on timeout */
	Chip_WWDT_SetOption(LPC_WWDT, WWDT_WDMOD_WDRESET);

	/* Clear watchdog warning and timeout interrupts */
	Chip_WWDT_ClearStatusFlag(LPC_WWDT, WWDT_WDMOD_WDTOF | WWDT_WDMOD_WDINT);

	/* Start watchdog */
	Chip_WWDT_Start(LPC_WWDT);


    // Feed watchdog
    WATCHDOG_Update();
}


/*------------------------------------------------------------------*-

    WATCHDOG_Update()

    Feed the watchdog timer.

    See Watchdog_Init() for further information.

-*------------------------------------------------------------------*/
void WATCHDOG_Update(void)
{
    // Feed the watchdog
    __disable_irq(); // Avoid possible interruption
    Chip_WWDT_Feed(LPC_WWDT);
    __enable_irq();
}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
