/*
 * GpiosTask_lpc1769.h
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */

#ifndef TASKS_GPIOSTASK_LPC1769_H_
#define TASKS_GPIOSTASK_LPC1769_H_

#include "chip.h"
#include "board.h"
#define ANTI_REBOTE 5
#define PUL_1	1,20
#define PUL_2	1,23
#define PUL_3	1,19
#define PUL_4	1,18
#define PUL_5	1,21
#define PUL_6   2,10
#define ON
#define OFF

void GPIOS_Init(void);
void GPIOS_Update(void);



#endif /* TASKS_GPIOSTASK_LPC1769_H_ */
