/*
 * main.c
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */
/*--------------------------------------------------------------------*-

    main.c (Released 2019-04)

--------------------------------------------------------------------

    main file for Co-operative - Time Driven System - Project for LPC1769.

    See readme.txt for project information.

-*--------------------------------------------------------------------*/


// Project header
#include "main.h"


/*------------------------------------------------------------------*/
int main(void)
{

	// Check mode, add tasks to schedule
    DisplayInit();
    SYSTEM_Init();

    // Start the scheduler
    SCH_Start();

    while(1)
    {
    SCH_Dispatch_Tasks();
    }

    return (RETURN_FAULT);
}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/


