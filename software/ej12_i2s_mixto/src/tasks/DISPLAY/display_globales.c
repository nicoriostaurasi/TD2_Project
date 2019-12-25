/*
 * display_globales.c
 *
 */

#include "display_header.h"


	volatile uint16_t ILI9341_x;
	volatile uint16_t ILI9341_y;

	volatile TM_ILI931_Options_t ILI9341_Opts;

	volatile uint8_t ILI9341_INT_CalledFromPuts = 0;

	volatile uint8_t using_tft = 0;

