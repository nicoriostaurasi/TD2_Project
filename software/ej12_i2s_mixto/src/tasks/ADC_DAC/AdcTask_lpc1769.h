/*
 * AdcTask_lpc1769.h
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */

#ifndef TASKS_ADCTASK_LPC1769_H_
#define TASKS_ADCTASK_LPC1769_H_

#include "../DSP/filtrado.h"
#include "../../main/main.h"
#include "i2s_hw.h"

/*--------------------------------------------------------------------*-
--------------------------------------------------------------------

-*--------------------------------------------------------------------*/




// ------ Public constants -----------------------------------------

/*#define COEF_LP			21
#define TAM_BUFF_LP		8
#define TAM_OUT_LP		TAM_BUFF_LP
*/
// ------ Public data type declarations ----------------------------



// ------ Public function prototypes -------------------------------
void AdcDacI2S_Init(void);
void AdcDacI2S_Update(void);



/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/



#endif /* TASKS_ADCTASK_LPC1769_H_ */
