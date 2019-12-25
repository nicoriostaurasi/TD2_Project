/*
 * display_func.c
 *
 */


#include "display_header.h"




	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Funciones publicas
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void backlight(uint32_t frecuencia , uint32_t duty)
	{
		uint32_t tmp = 1000000/frecuencia;
		// Match 0 (period)
		Chip_TIMER_MatchEnableInt( LPC_TIMER1 , 0 );
		Chip_TIMER_ResetOnMatchEnable( LPC_TIMER1 , 0 );
		Chip_TIMER_StopOnMatchDisable( LPC_TIMER1 , 0 );
		Chip_TIMER_SetMatch( LPC_TIMER1 , 0 , tmp );

		// Match 1 (duty)
		Chip_TIMER_MatchEnableInt( LPC_TIMER1 , 1 );
		Chip_TIMER_ResetOnMatchDisable( LPC_TIMER1 , 1 );
		Chip_TIMER_StopOnMatchDisable( LPC_TIMER1 , 1 );
		Chip_TIMER_SetMatch( LPC_TIMER1 , 1 , tmp*duty/100 );
		Chip_TIMER_Reset( LPC_TIMER1 );
		Chip_TIMER_Enable( LPC_TIMER1 );
		NVIC_EnableIRQ( TIMER1_IRQn );
	}

	void TM_ILI9341_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
	{
		TM_ILI9341_SendCommand(ILI9341_COLUMN_ADDR);
		TM_ILI9341_SendData(x1 >> 8);
		TM_ILI9341_SendData(x1 & 0xFF);
		TM_ILI9341_SendData(x2 >> 8);
		TM_ILI9341_SendData(x2 & 0xFF);

		TM_ILI9341_SendCommand(ILI9341_PAGE_ADDR);
		TM_ILI9341_SendData(y1 >> 8);
		TM_ILI9341_SendData(y1 & 0xFF);
		TM_ILI9341_SendData(y2 >> 8);
		TM_ILI9341_SendData(y2 & 0xFF);
	}

	void TM_ILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
	{
		TM_ILI9341_SetCursorPosition(x, y, x, y);
		TM_ILI9341_SendCommand(ILI9341_GRAM);
		TM_ILI9341_SendData(color);
	}

	void TM_ILI9341_Fill(uint16_t color)
	{
		if(using_tft) return;

		using_tft = 1;

		uint32_t n = 0;

		TM_ILI9341_SetCursorPosition(0, 0, ILI9341_Opts.width - 1, ILI9341_Opts.height - 1);

		TM_ILI9341_SendCommand(ILI9341_GRAM);

		for (n = 0; n < ILI9341_PIXEL; n++)
			TM_ILI9341_SendData(color);

		using_tft = 0;
	}

	void TM_ILI9341_Rotate(TM_ILI9341_Orientation orientation)
	{
		if(using_tft) return;

		using_tft = 1;

		TM_ILI9341_SendCommand(ILI9341_MAC);

		if (orientation == TM_ILI9341_Orientation_Portrait_1)
			TM_ILI9341_SendData(0x58);
		else if (orientation == TM_ILI9341_Orientation_Portrait_2)
			TM_ILI9341_SendData(0x88);
		else if (orientation == TM_ILI9341_Orientation_Landscape_1)
			TM_ILI9341_SendData(0x28);
		else if (orientation == TM_ILI9341_Orientation_Landscape_2)
			TM_ILI9341_SendData(0xE8);

		if (orientation == TM_ILI9341_Orientation_Portrait_1 || orientation == TM_ILI9341_Orientation_Portrait_2)
		{
			ILI9341_Opts.width = ILI9341_WIDTH;
			ILI9341_Opts.height = ILI9341_HEIGHT;
			ILI9341_Opts.orientation = TM_ILI9341_Portrait;
		}
		else
		{
			ILI9341_Opts.width = ILI9341_HEIGHT;
			ILI9341_Opts.height = ILI9341_WIDTH;
			ILI9341_Opts.orientation = TM_ILI9341_Landscape;
		}

		using_tft = 0;
	}

	void TM_ILI9341_Putc(uint16_t x, uint16_t y, uint8_t c, TM_FontDef_t *font, uint16_t foreground, uint16_t background)
	{
		uint32_t i = 0, b = 0, j = 0;

		// Set coordinates
		ILI9341_x = x;
		ILI9341_y = y;

		if ((ILI9341_x + font->FontWidth) > ILI9341_Opts.width)
		{
			//If at the end of a line of display, go to new line and set x to 0 position
			ILI9341_y += font->FontHeight;
			ILI9341_x = 0;
		}

		for (i = 0; i < font->FontHeight; i++)
		{
			b = font->data[(c - 32) * font->FontHeight + i];
			for (j = 0; j < font->FontWidth; j++)
			{
				if ((b << j) & 0x8000)
					TM_ILI9341_DrawPixel(ILI9341_x + j, (ILI9341_y + i), foreground);
				else
					TM_ILI9341_DrawPixel(ILI9341_x + j, (ILI9341_y + i), background);
			}
		}

		ILI9341_x += font->FontWidth;
	}

	void TM_ILI9341_Puts(uint16_t x, uint16_t y, char *str, TM_FontDef_t *font, uint16_t foreground, uint16_t background)
	{
		if(using_tft) return;

		using_tft = 1;

		// Set X and Y coordinates
		ILI9341_x = x;
		ILI9341_y = y;

		while (*str)
		{
//			//New line
//			if (*str == '\n') {
//				ILI9341_y += font->FontHeight + 1;
//				//if after \n is also \r, than go to the left of the screen
//				if (*(str + 1) == '\r') {
//					ILI9341_x = 0;
//					str++;
//				} else {
//					ILI9341_x = startX;
//				}
//				str++;
//				continue;
//			} else if (*str == '\r') {
//				str++;
//				continue;
//			}

			TM_ILI9341_Putc(ILI9341_x, ILI9341_y, *str++, font, foreground, background);
		}

		using_tft = 0;
	}

	void TM_ILI9341_GetStringSize(uint8_t *str, TM_FontDef_t *font, uint16_t *width, uint16_t *height)
	{
		uint16_t w = 0;

		*height = font->FontHeight;

		while (*str++)
			w += font->FontWidth;

		*width = w;
	}

	void TM_ILI9341_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
	{
		int16_t dx, dy, sx, sy, err, e2;


		if (x0 >= ILI9341_Opts.width)
			x0 = ILI9341_Opts.width - 1;

		if (x1 >= ILI9341_Opts.width)
			x1 = ILI9341_Opts.width - 1;

		if (y0 >= ILI9341_Opts.height)
			y0 = ILI9341_Opts.height - 1;

		if (y1 >= ILI9341_Opts.height)
			y1 = ILI9341_Opts.height - 1;

		dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
		dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);
		sx = (x0 < x1) ? 1 : -1;
		sy = (y0 < y1) ? 1 : -1;
		err = ((dx > dy) ? dx : -dy) / 2;

		while (1)
		{
			TM_ILI9341_DrawPixel(x0, y0, color);

			if (x0 == x1 && y0 == y1)
				break;

			e2 = err;

			if (e2 > -dx)
			{
				err -= dy;
				x0 += sx;
			}

			if (e2 < dy)
			{
				err += dx;
				y0 += sy;
			}
		}
	}

	void TM_ILI9341_DrawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
	{
		if(using_tft) return;

		using_tft = 1;

		TM_ILI9341_DrawLine(x0, y0, x1, y0, color); //Top
		TM_ILI9341_DrawLine(x0, y0, x0, y1, color);	//Left
		TM_ILI9341_DrawLine(x1, y0, x1, y1, color);	//Right
		TM_ILI9341_DrawLine(x0, y1, x1, y1, color);	//Bottom

		using_tft = 0;
	}

	void TM_ILI9341_DrawFilledRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
	{
		if(using_tft) return;

		using_tft = 1;

		for (; y0 < y1; y0++)
			TM_ILI9341_DrawLine(x0, y0, x1, y0, color);

		using_tft = 0;
	}

	void TM_ILI9341_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
	{
		if(using_tft) return;

		using_tft = 1;

		int16_t f = 1 - r;
		int16_t ddF_x = 1;
		int16_t ddF_y = -2 * r;
		int16_t x = 0;
		int16_t y = r;

		TM_ILI9341_DrawPixel(x0, y0 + r, color);
		TM_ILI9341_DrawPixel(x0, y0 - r, color);
		TM_ILI9341_DrawPixel(x0 + r, y0, color);
		TM_ILI9341_DrawPixel(x0 - r, y0, color);

		while (x < y)
		{
			if (f >= 0)
			{
				y--;
				ddF_y += 2;
				f += ddF_y;
			}

			x++;
			ddF_x += 2;
			f += ddF_x;

			TM_ILI9341_DrawPixel(x0 + x, y0 + y, color);
			TM_ILI9341_DrawPixel(x0 - x, y0 + y, color);
			TM_ILI9341_DrawPixel(x0 + x, y0 - y, color);
			TM_ILI9341_DrawPixel(x0 - x, y0 - y, color);

			TM_ILI9341_DrawPixel(x0 + y, y0 + x, color);
			TM_ILI9341_DrawPixel(x0 - y, y0 + x, color);
			TM_ILI9341_DrawPixel(x0 + y, y0 - x, color);
			TM_ILI9341_DrawPixel(x0 - y, y0 - x, color);
		}

		using_tft = 0;
	}

	void TM_ILI9341_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
	{
		if(using_tft) return;

		using_tft = 1;

		int16_t f = 1 - r;
		int16_t ddF_x = 1;
		int16_t ddF_y = -2 * r;
		int16_t x = 0;
		int16_t y = r;

		TM_ILI9341_DrawPixel(x0, y0 + r, color);
		TM_ILI9341_DrawPixel(x0, y0 - r, color);
		TM_ILI9341_DrawPixel(x0 + r, y0, color);
		TM_ILI9341_DrawPixel(x0 - r, y0, color);
		TM_ILI9341_DrawLine(x0 - r, y0, x0 + r, y0, color);

		while (x < y)
		{
			if (f >= 0)
			{
				y--;
				ddF_y += 2;
				f += ddF_y;
			}

			x++;
			ddF_x += 2;
			f += ddF_x;

			TM_ILI9341_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
			TM_ILI9341_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, color);

			TM_ILI9341_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, color);
			TM_ILI9341_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, color);
		}

		using_tft = 0;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Funciones privadas
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void TM_ILI9341_Delay(volatile unsigned long int delay)
	{
		for (; delay != 0; delay--);
	}

	void TM_ILI9341_SendCommand(uint16_t data)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, READ_DATA, 1);
		Chip_GPIO_SetPinState(LPC_GPIO, RS, 0);
		Chip_GPIO_SetPinState(LPC_GPIO, WR, 0);
		Chip_GPIO_SetPinState(LPC_GPIO, CS, 0);
		TM_Send(data);
		Chip_GPIO_SetPinState(LPC_GPIO, CS, 1);
		Chip_GPIO_SetPinState(LPC_GPIO, WR, 1);
	}

	void TM_ILI9341_SendData(uint16_t data)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, RS, 1);
		Chip_GPIO_SetPinState(LPC_GPIO, WR, 0);
		Chip_GPIO_SetPinState(LPC_GPIO, CS, 0);
		TM_Send(data);
		// Segun stm32
		Chip_GPIO_SetPinState(LPC_GPIO, CS, 1);
		Chip_GPIO_SetPinState(LPC_GPIO, WR, 1);
	}

	void TM_Send(uint16_t data)
	{
			Chip_GPIO_SetPinState(LPC_GPIO, DB0, (data >> 0) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB1, (data >> 1) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB2, (data >> 2) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB3, (data >> 3) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB4, (data >> 4) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB5, (data >> 5) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB6, (data >> 6) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB7, (data >> 7) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB8, (data >> 8) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB9, (data >> 9) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB10, (data >> 10) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB11, (data >> 11) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB12, (data >> 12) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB13, (data >> 13) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB14, (data >> 14) & 1);
			Chip_GPIO_SetPinState(LPC_GPIO, DB15, (data >> 15) & 1);
	}


