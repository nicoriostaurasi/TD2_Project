/*
 * DisplayTASK.c
 *
 *  Created on: 20 dic. 2019
 *      Author: nicol
 */
#include "DisplayTASK.h"

extern uint8_t flag_display;
extern uint8_t banda;
extern uint8_t gainLPF;
extern uint8_t gainBPF;
extern uint8_t gainHPF;

void DisplayInit(void)
{
	TM_ILI9341_Init();
	TM_ILI9341_InitLCD();
	welcome_screen();
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_1);
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	OUT_EQH(1,1,1);

}

void DisplayUpdate(void)
{
static uint8_t gainLPFs=1,gainBPFs=1,gainHPFs=1;
if(flag_display==1)
{
			switch(gainLPF)
			{
			case 1:
				gainLPFs=5;
				break;
			case 2:
				gainLPFs=4;
				break;
			case 3:
				gainLPFs=3;
				break;
			case 4:
				gainLPFs=2;
				break;
			case 5:
				gainLPFs=1;
				break;
			}

			switch(gainLPF)
			{
			case 1:
				gainLPFs=5;
				break;
			case 2:
				gainLPFs=4;
				break;
			case 3:
				gainLPFs=3;
				break;
			case 4:
				gainLPFs=2;
				break;
			case 5:
				gainLPFs=1;
				break;
			}

			switch(gainHPF)
			{
			case 1:
				gainHPFs=5;
				break;
			case 2:
				gainHPFs=4;
				break;
			case 3:
				gainHPFs=3;
				break;
			case 4:
				gainHPFs=2;
				break;
			case 5:
				gainHPFs=1;
				break;
			}

			switch(gainBPF)
			{
			case 1:
				gainBPFs=5;
				break;
			case 2:
				gainBPFs=4;
				break;
			case 3:
				gainBPFs=3;
				break;
			case 4:
				gainBPFs=2;
				break;
			case 5:
				gainBPFs=1;
				break;
			}

Update_EQH(gainLPFs,gainBPFs,gainHPFs,25,banda);
flag_display=0;
}

}
