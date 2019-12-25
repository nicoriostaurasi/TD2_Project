/*
 * display_func.h
 *
 */


#ifndef DISPLAY_FUNC_H_
#define DISPLAY_FUNC_H_


#include "display_header.h"


// ********* FUNCIONES ********** //

	// ********* PRIVADAS ********** //
		// Simple delay - Parameters: volatile unsigned int delay: clock cycles
		void TM_ILI9341_Delay(volatile unsigned long int delay);
		// Send command to LCD via SPI - Called private - Parameters: uint8_t data: data to be sent
		void TM_ILI9341_SendCommand(uint16_t data);
		// Send data to LCD via SPI - Called private - Parameters: uint8_t data: data to be sent
		void TM_ILI9341_SendData(uint16_t data);
		//	unsigned char TM_SPI_Send (unsigned char byte_s);
		void TM_Send(uint16_t data);
	// ****************************** //

	// ********* PUBLICAS ********** //
		void backlight(uint32_t frecuencia , uint32_t duty);
		void TM_ILI9341_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
		void TM_ILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
		void TM_ILI9341_Fill(uint16_t color);
		void TM_ILI9341_Rotate(TM_ILI9341_Orientation orientation);
		void TM_ILI9341_Putc(uint16_t x, uint16_t y, uint8_t c, TM_FontDef_t *font, uint16_t foreground, uint16_t background);
		void TM_ILI9341_Puts(uint16_t x, uint16_t y, char *str, TM_FontDef_t *font, uint16_t foreground, uint16_t background);
		void TM_ILI9341_GetStringSize(uint8_t *str, TM_FontDef_t *font, uint16_t *width, uint16_t *height);
		void TM_ILI9341_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
		void TM_ILI9341_DrawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
		void TM_ILI9341_DrawFilledRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
		void TM_ILI9341_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
		void TM_ILI9341_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

	// ****************************** //
// ****************************** //


// ***************** DEFINES ***************** //
// ******************************************* //


// *************** ESTRUCTURAS *************** //
// ******************************************* //


// ************* VARIABLES GLOBALES ************* //
// ********************************************** //


// ************* HEADERS ************* //


// ****************************************** //


#endif /* DISPLAY_FUNC_H_ */
