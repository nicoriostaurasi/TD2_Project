/*
 * task-heartbeat_lpc1769.c
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */
/*--------------------------------------------------------------------*-

    task-heartbeat_lpc1769.c (Released 2019-04)

  --------------------------------------------------------------------

    Simple 'Heartbeat' task for LPC1769.

    If everything is OK, flashes at 0.5 Hz

    If there is a fault code active, this is displayed.

-*--------------------------------------------------------------------*/


// Project header
#include "../../main/main.h"


// Task header
#include "task-heartbeat_lpc1769.h"


// ------ Public variable ------------------------------------------

// See scheduler for definition
extern uint32_t Fault_code_G;


// ------ Private constants ----------------------------------------


// ------ Private variable -----------------------------------------

extern volatile uint8_t banda;
extern volatile uint8_t control;
#define loopback 7
#define muteState 9
#define sum_eq 10
/*------------------------------------------------------------------*-

    HEARTBEAT_Init()

    Prepare for HEARTBEAT_Update() function - see below.
-*------------------------------------------------------------------*/
void HEARTBEAT_Init(void)
{
	// Set up LED2 as an output pin
	Chip_IOCON_PinMux(LPC_IOCON, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN, HEARTBEAT_LED_PIN_MODE, HEARTBEAT_LED_PIN_FUNC);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN);

	Chip_IOCON_PinMux(LPC_IOCON,LED_VERDE, HEARTBEAT_LED_PIN_MODE, HEARTBEAT_LED_PIN_FUNC);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,LED_VERDE );

	Chip_IOCON_PinMux(LPC_IOCON,LED_AZUL , HEARTBEAT_LED_PIN_MODE, HEARTBEAT_LED_PIN_FUNC);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,LED_AZUL );


}


/*------------------------------------------------------------------*-

    HEARTBEAT_Update()

    Flashes at 0.5 Hz if fault code is 0 (i.e. no fault code).

    Otherwise, displays fault code.

    Must schedule every second (soft deadline).

-*------------------------------------------------------------------*/
void HEARTBEAT_Update(void)
{
    static uint32_t Heartbeat_state = 0;
    static uint32_t Fault_state = 0;

    if (Fault_code_G == 0)
	{
        // No faults recorded
        // - just flash at 0.5 Hz
        // Change the LED from OFF to ON (or vice versa)
        if (Heartbeat_state == 1)
        {
            Heartbeat_state = 0;

            if(control==loopback)
            {
       		Chip_GPIO_WritePortBit(LPC_GPIO, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN, false);
            Chip_GPIO_WritePortBit(LPC_GPIO,LED_VERDE , false);
            Chip_GPIO_WritePortBit(LPC_GPIO,LED_AZUL , false);
            }
            else if(control==muteState)
            {
       		Chip_GPIO_WritePortBit(LPC_GPIO, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN, true);
            Chip_GPIO_WritePortBit(LPC_GPIO,LED_VERDE , true);
            Chip_GPIO_WritePortBit(LPC_GPIO,LED_AZUL , true);
            }
            else if(control==sum_eq)
            {
            Chip_GPIO_WritePortBit(LPC_GPIO, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN, true);
            Chip_GPIO_WritePortBit(LPC_GPIO,LED_VERDE , false);
            Chip_GPIO_WritePortBit(LPC_GPIO,LED_AZUL , true);
            }
            else
           {
            if(banda==1)
            {
    		Chip_GPIO_WritePortBit(LPC_GPIO, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN, false);
    		Chip_GPIO_WritePortBit(LPC_GPIO,LED_VERDE , true);
    		Chip_GPIO_WritePortBit(LPC_GPIO,LED_AZUL , true);
            }
            if(banda==2)
            {
    		Chip_GPIO_WritePortBit(LPC_GPIO, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN, true);
    		Chip_GPIO_WritePortBit(LPC_GPIO,LED_VERDE , false);
    		Chip_GPIO_WritePortBit(LPC_GPIO,LED_AZUL , true);
            }
            if(banda==3)
            {
    		Chip_GPIO_WritePortBit(LPC_GPIO, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN, true);
            Chip_GPIO_WritePortBit(LPC_GPIO,LED_VERDE , true);
            Chip_GPIO_WritePortBit(LPC_GPIO,LED_AZUL , false);
            }
           }
        }
        else
        {
            Heartbeat_state = 1;

    		Chip_GPIO_WritePortBit(LPC_GPIO, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN, true);
    		Chip_GPIO_WritePortBit(LPC_GPIO, LED_VERDE, true);
    		Chip_GPIO_WritePortBit(LPC_GPIO, LED_AZUL , true);



        }
	}
    else
	{
        // If we are here, there is a (non-zero) fault code ...
        Fault_state++;
        if (Fault_state < Fault_code_G*2)
        {
            Heartbeat_state = 0;
    		Chip_GPIO_WritePortBit(LPC_GPIO, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN, false);
        }
        else
        {
            if (Fault_state < Fault_code_G*4)
            {
            	// Change the LED from OFF to ON (or vice versa)
            	if (Heartbeat_state == 1)
            		{
            		Heartbeat_state = 0;
            		Chip_GPIO_WritePortBit(LPC_GPIO, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN, false);
            		}
            	else
            	{
            		Heartbeat_state = 1;
            		Chip_GPIO_WritePortBit(LPC_GPIO, HEARTBEAT_LED_PORT, HEARTBEAT_LED_PIN, true);
            	}
            }
            else
            {
            	Fault_state = 0;
            }
        }
	}
}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
