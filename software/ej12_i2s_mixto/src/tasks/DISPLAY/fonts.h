/*
 * fonts.h
 *
 */

#ifndef FONTS_H_
#define FONTS_H_

#include "display_header.h"


// ********* FUNCIONES ********** //
	// ****************************** //


// ***************** DEFINES ***************** //
	// ******************************************* //


// *************** ESTRUCTURAS *************** //

		// Font struct
		typedef struct {
			unsigned char FontWidth;
			unsigned char FontHeight;
			const uint16_t *data;
		} TM_FontDef_t;


// ******************************************* //


// ************* VARIABLES GLOBALES ************* //

		extern TM_FontDef_t TM_Font_7x10;
		extern TM_FontDef_t TM_Font_11x18;
		extern TM_FontDef_t TM_Font_16x26;

// ********************************************** //


// ************* HEADERS ************* //


// ****************************************** //






#endif /* FONTS_H_ */
