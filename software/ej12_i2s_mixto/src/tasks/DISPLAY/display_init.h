/*
 * display_init.h
 *
 */

#ifndef DISPLAY_INIT_H_
#define DISPLAY_INIT_H_


#include "display_header.h"
#define USE_DISPLAY 1

#if (USE_DISPLAY)

	STATIC INLINE void TM_ILI9341_InitLCD(void)
	{
		Chip_GPIO_SetPinState(LPC_GPIO, REST,0);
		Chip_GPIO_SetPinState(LPC_GPIO, REST,1);

		TM_ILI9341_SendCommand(ILI9341_RESET);
		TM_ILI9341_Delay(2000000);

		TM_ILI9341_SendCommand(ILI9341_POWERA);
		TM_ILI9341_SendData(0x39);
		TM_ILI9341_SendData(0x2C);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x34);
		TM_ILI9341_SendData(0x02);
		TM_ILI9341_SendCommand(ILI9341_POWERB);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0xC1);
		TM_ILI9341_SendData(0x30);
		TM_ILI9341_SendCommand(ILI9341_DTCA);
		TM_ILI9341_SendData(0x85);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x78);
		TM_ILI9341_SendCommand(ILI9341_DTCB);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendCommand(ILI9341_POWER_SEQ);
		TM_ILI9341_SendData(0x64);
		TM_ILI9341_SendData(0x03);
		TM_ILI9341_SendData(0x12);
		TM_ILI9341_SendData(0x81);
		TM_ILI9341_SendCommand(ILI9341_PRC);
		TM_ILI9341_SendData(0x20);
		TM_ILI9341_SendCommand(ILI9341_POWER1);
		TM_ILI9341_SendData(0x23);
		TM_ILI9341_SendCommand(ILI9341_POWER2);
		TM_ILI9341_SendData(0x10);
		TM_ILI9341_SendCommand(ILI9341_VCOM1);
		TM_ILI9341_SendData(0x3E);
		TM_ILI9341_SendData(0x28);
		TM_ILI9341_SendCommand(ILI9341_VCOM2);
		TM_ILI9341_SendData(0x86);
		TM_ILI9341_SendCommand(ILI9341_MAC);
		TM_ILI9341_SendData(0x48);
		TM_ILI9341_SendCommand(ILI9341_PIXEL_FORMAT);
		TM_ILI9341_SendData(0x55);
		TM_ILI9341_SendCommand(ILI9341_FRC);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x18);
		TM_ILI9341_SendCommand(ILI9341_DFC);
		TM_ILI9341_SendData(0x08);
		TM_ILI9341_SendData(0x82);
		TM_ILI9341_SendData(0x27);
		TM_ILI9341_SendCommand(ILI9341_3GAMMA_EN);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendCommand(ILI9341_COLUMN_ADDR);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0xEF);
		TM_ILI9341_SendCommand(ILI9341_PAGE_ADDR);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x01);
		TM_ILI9341_SendData(0x3F);
		TM_ILI9341_SendCommand(ILI9341_GAMMA);
		TM_ILI9341_SendData(0x01);
		TM_ILI9341_SendCommand(ILI9341_PGAMMA);
		TM_ILI9341_SendData(0x0F);
		TM_ILI9341_SendData(0x31);
		TM_ILI9341_SendData(0x2B);
		TM_ILI9341_SendData(0x0C);
		TM_ILI9341_SendData(0x0E);
		TM_ILI9341_SendData(0x08);
		TM_ILI9341_SendData(0x4E);
		TM_ILI9341_SendData(0xF1);
		TM_ILI9341_SendData(0x37);
		TM_ILI9341_SendData(0x07);
		TM_ILI9341_SendData(0x10);
		TM_ILI9341_SendData(0x03);
		TM_ILI9341_SendData(0x0E);
		TM_ILI9341_SendData(0x09);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendCommand(ILI9341_NGAMMA);
		TM_ILI9341_SendData(0x00);
		TM_ILI9341_SendData(0x0E);
		TM_ILI9341_SendData(0x14);
		TM_ILI9341_SendData(0x03);
		TM_ILI9341_SendData(0x11);
		TM_ILI9341_SendData(0x07);
		TM_ILI9341_SendData(0x31);
		TM_ILI9341_SendData(0xC1);
		TM_ILI9341_SendData(0x48);
		TM_ILI9341_SendData(0x08);
		TM_ILI9341_SendData(0x0F);
		TM_ILI9341_SendData(0x0C);
		TM_ILI9341_SendData(0x31);
		TM_ILI9341_SendData(0x36);
		TM_ILI9341_SendData(0x0F);
		TM_ILI9341_SendCommand(ILI9341_WCD);
		TM_ILI9341_SendData(0x2C);
		TM_ILI9341_SendCommand(0xC0);
		TM_ILI9341_SendData(0x09);
		TM_ILI9341_SendCommand(ILI9341_SLEEP_OUT);

		TM_ILI9341_Delay(1000000);

		TM_ILI9341_SendCommand(ILI9341_DISPLAY_ON);
		TM_ILI9341_SendCommand(ILI9341_GRAM);
	}

	STATIC INLINE void TM_ILI9341_Init(void)
	{
		// Inicializacion de los pines utilizados por la TFT
		Chip_IOCON_PinMux(LPC_IOCON, DB0, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB0);
		Chip_GPIO_SetPinState(LPC_GPIO, DB0,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB1, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB1);
		Chip_GPIO_SetPinState(LPC_GPIO, DB1,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB2, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB2);
		Chip_GPIO_SetPinState(LPC_GPIO, DB2,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB3, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB3);
		Chip_GPIO_SetPinState(LPC_GPIO, DB3,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB4, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB4);
		Chip_GPIO_SetPinState(LPC_GPIO, DB4,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB5, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB5);
		Chip_GPIO_SetPinState(LPC_GPIO, DB5,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB6, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB6);
		Chip_GPIO_SetPinState(LPC_GPIO, DB6,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB7, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB7);
		Chip_GPIO_SetPinState(LPC_GPIO, DB7,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB8, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB8);
		Chip_GPIO_SetPinState(LPC_GPIO, DB8,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB9, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB9);
		Chip_GPIO_SetPinState(LPC_GPIO, DB9,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB10, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB10);
		Chip_GPIO_SetPinState(LPC_GPIO, DB10,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB11, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB11);
		Chip_GPIO_SetPinState(LPC_GPIO, DB11,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB13, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB12);
		Chip_GPIO_SetPinState(LPC_GPIO,DB12,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB13, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB13);
		Chip_GPIO_SetPinState(LPC_GPIO, DB13,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB14, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB14);
		Chip_GPIO_SetPinState(LPC_GPIO, DB14,0);

		Chip_IOCON_PinMux(LPC_IOCON, DB15, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, DB15);
		Chip_GPIO_SetPinState(LPC_GPIO, DB15,0);

		Chip_IOCON_PinMux(LPC_IOCON, CS, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, CS);
		Chip_GPIO_SetPinState(LPC_GPIO, CS,1);					// Activa en bajo

		Chip_IOCON_PinMux(LPC_IOCON, RS, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, RS);
		Chip_GPIO_SetPinState(LPC_GPIO, RS,0);

		Chip_IOCON_PinMux(LPC_IOCON, WR, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, WR);
		Chip_GPIO_SetPinState(LPC_GPIO, WR,1);					// Activa en bajo

		Chip_IOCON_PinMux(LPC_IOCON, READ_DATA, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, READ_DATA);
		Chip_GPIO_SetPinState(LPC_GPIO, READ_DATA,1);			// Activa en bajo

		Chip_IOCON_PinMux(LPC_IOCON, REST, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, REST);
		Chip_GPIO_SetPinState(LPC_GPIO, REST,1);				// Activa en bajo

/*		Chip_IOCON_PinMux(LPC_IOCON, BL, IOCON_MODE_INACT, IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, BL);
		Chip_GPIO_SetPinState(LPC_GPIO,BL,0);
*/
		// Envio de comandos de inicializacion
		TM_ILI9341_InitLCD();

		ILI9341_x = ILI9341_y = 0;
		ILI9341_Opts.width = ILI9341_WIDTH;
		ILI9341_Opts.height = ILI9341_HEIGHT;
		ILI9341_Opts.orientation = TM_ILI9341_Portrait;

//		TM_ILI9341_Fill(ILI9341_COLOR_CYAN);
	}


	STATIC INLINE void backlight_init( void )
	{
	    Chip_TIMER_Init( LPC_TIMER1 );
	    Chip_TIMER_PrescaleSet( LPC_TIMER1 , Chip_Clock_GetPeripheralClockRate( SYSCTL_PCLK_TIMER1 ) / 1000000 - 1 );
	}

	STATIC INLINE void welcome_screen(void)
	{
		//TM_ILI9341_Orientation peperota=TM_ILI9341_Landscape ;
			/* MODOS DE ORIENTACION (funcion TM_ILI9341_Rotate())
			 * 0: MAL
			 * 1: MAL
			 * 2: Vertical con pines arriba
			 * 3: Vertical con pines abajo
			 * 4: Apaisado con pines hacia la izquierda
			 * 5: Apaisado con pines hacia la derecha
			 */

		TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_1);
		TM_ILI9341_Fill(ILI9341_COLOR_WHITE);

		TM_ILI9341_Puts(50, +10, "Tecnicas Digitales 2", &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);

		TM_ILI9341_Puts(100, +70, "R4053-2019", &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);

		TM_ILI9341_Puts(50, +120, "\"EQH GRAFICO\"", &TM_Font_16x26,ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);

		TM_ILI9341_Puts(0, 180, "-Rios Taurasi, Nicolas", &TM_Font_7x10, ILI9341_COLOR_BLUE2, ILI9341_COLOR_WHITE);

		TM_ILI9341_Puts(0, 191, "-Gomez, Nicolas", &TM_Font_7x10, ILI9341_COLOR_BLUE2, ILI9341_COLOR_WHITE);

		TM_ILI9341_Puts(0, 202, "-Laborde, Santiago", &TM_Font_7x10, ILI9341_COLOR_BLUE2, ILI9341_COLOR_WHITE);

	}

/*#define K 25
#define uinicialx 150
#define uinicialy 50
*/
	STATIC INLINE void pantalla_por_defecto(uint8_t barra,uint16_t uinicialx, uint16_t uinicialy, uint8_t K)
	{

//		TM_ILI9341_Puts(0, +10, "A TODOO O NADA", &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);

		switch(barra)
		{

		case 1:

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1,uinicialx+50,uinicialy+24,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5,uinicialx+45,uinicialy+20, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+K,uinicialx+50,uinicialy+24+K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+K,uinicialx+45,uinicialy+20+K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+2*K,uinicialx+50,uinicialy+24+2*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+2*K,uinicialx+45,uinicialy+20+2*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+3*K,uinicialx+50,uinicialy+24+3*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+3*K,uinicialx+45,uinicialy+20+3*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+4*K,uinicialx+50,uinicialy+24+4*K,ILI9341_COLOR_BLACK);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+4*K,uinicialx+45,uinicialy+20+4*K, ILI9341_COLOR_BLACK);

		break;

		case 2:

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1,uinicialx+50,uinicialy+24,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5,uinicialx+45,uinicialy+20, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+K,uinicialx+50,uinicialy+24+K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+K,uinicialx+45,uinicialy+20+K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+2*K,uinicialx+50,uinicialy+24+2*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+2*K,uinicialx+45,uinicialy+20+2*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+3*K,uinicialx+50,uinicialy+24+3*K,ILI9341_COLOR_BLACK);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+3*K,uinicialx+45,uinicialy+20+3*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+4*K,uinicialx+50,uinicialy+24+4*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+4*K,uinicialx+45,uinicialy+20+4*K, ILI9341_COLOR_BLACK);

		break;
		case 3:
		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1,uinicialx+50,uinicialy+24,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5,uinicialx+45,uinicialy+20, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+K,uinicialx+50,uinicialy+24+K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+K,uinicialx+45,uinicialy+20+K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+2*K,uinicialx+50,uinicialy+24+2*K,ILI9341_COLOR_BLACK);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+2*K,uinicialx+45,uinicialy+20+2*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+3*K,uinicialx+50,uinicialy+24+3*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+3*K,uinicialx+45,uinicialy+20+3*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+4*K,uinicialx+50,uinicialy+24+4*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+4*K,uinicialx+45,uinicialy+20+4*K, ILI9341_COLOR_BLACK);

		break;
		case 4:
		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1,uinicialx+50,uinicialy+24,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5,uinicialx+45,uinicialy+20, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+K,uinicialx+50,uinicialy+24+K,ILI9341_COLOR_BLACK);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+K,uinicialx+45,uinicialy+20+K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+2*K,uinicialx+50,uinicialy+24+2*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+2*K,uinicialx+45,uinicialy+20+2*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+3*K,uinicialx+50,uinicialy+24+3*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+3*K,uinicialx+45,uinicialy+20+3*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+4*K,uinicialx+50,uinicialy+24+4*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+4*K,uinicialx+45,uinicialy+20+4*K, ILI9341_COLOR_BLACK);

		break;

		case 5:
		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1,uinicialx+50,uinicialy+24,ILI9341_COLOR_BLACK);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5,uinicialx+45,uinicialy+20, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+K,uinicialx+50,uinicialy+24+K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+K,uinicialx+45,uinicialy+20+K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+2*K,uinicialx+50,uinicialy+24+2*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+2*K,uinicialx+45,uinicialy+20+2*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+3*K,uinicialx+50,uinicialy+24+3*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+3*K,uinicialx+45,uinicialy+20+3*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+4*K,uinicialx+50,uinicialy+24+4*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+4*K,uinicialx+45,uinicialy+20+4*K, ILI9341_COLOR_BLACK);

		break;

		default:
		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1,uinicialx+50,uinicialy+24,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5,uinicialx+45,uinicialy+20, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+K,uinicialx+50,uinicialy+24+K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+K,uinicialx+45,uinicialy+20+K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+2*K,uinicialx+50,uinicialy+24+2*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+2*K,uinicialx+45,uinicialy+20+2*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+3*K,uinicialx+50,uinicialy+24+3*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+3*K,uinicialx+45,uinicialy+20+3*K, ILI9341_COLOR_BLACK);

		TM_ILI9341_DrawRectangle(uinicialx,uinicialy+1+4*K,uinicialx+50,uinicialy+24+4*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawFilledRectangle(uinicialx+5,uinicialy+5+4*K,uinicialx+45,uinicialy+20+4*K, ILI9341_COLOR_BLACK);

		break;
		}
}


#define inic 35

	STATIC INLINE void OUT_EQH(uint8_t LPF_State,uint8_t BPF_State,uint8_t HPF_State)
	{

		TM_ILI9341_Puts(60, +10, "Grafico de Bandas", &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);

		pantalla_por_defecto(LPF_State,inic,50,25);

		TM_ILI9341_Puts(inic+10, 180, "LPF", &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);

		pantalla_por_defecto(LPF_State,inic+100,50,25);

		TM_ILI9341_Puts(inic+10+100, 180, "BPF", &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);

		pantalla_por_defecto(HPF_State,inic+2*100,50,25);

		TM_ILI9341_Puts(inic+10+2*100, 180, "HPF", &TM_Font_11x18, ILI9341_COLOR_BLUE, ILI9341_COLOR_WHITE);


	}

	STATIC INLINE void Update_EQH(uint8_t LPF_State,uint8_t BPF_State,uint8_t HPF_State,uint8_t K,uint8_t banda)
	{
	static uint8_t LPF_State_Ant=1;
	static uint8_t BPF_State_Ant=1;
	static uint8_t HPF_State_Ant=1;

	if(LPF_State_Ant!=LPF_State)
	{
	TM_ILI9341_DrawRectangle(35,50+1+(LPF_State-1)*K,35+50,50+24+(LPF_State-1)*K,ILI9341_COLOR_GREEN);
	TM_ILI9341_DrawRectangle(35,50+1+(LPF_State_Ant-1)*K,35+50,50+24+(LPF_State_Ant-1)*K,ILI9341_COLOR_WHITE);
	TM_ILI9341_DrawRectangle(135,50+1+(BPF_State-1)*K,135+50,50+24+(BPF_State-1)*K,ILI9341_COLOR_BLACK);
	TM_ILI9341_DrawRectangle(235,50+1+(HPF_State-1)*K,235+50,50+24+(HPF_State-1)*K,ILI9341_COLOR_BLACK);
	}

	if(BPF_State_Ant!=BPF_State)
	{
		TM_ILI9341_DrawRectangle(135,50+1+(BPF_State-1)*K,135+50,50+24+(BPF_State-1)*K,ILI9341_COLOR_RED);
		TM_ILI9341_DrawRectangle(135,50+1+(BPF_State_Ant-1)*K,135+50,50+24+(BPF_State_Ant-1)*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawRectangle(35,50+1+(LPF_State-1)*K,35+50,50+24+(LPF_State-1)*K,ILI9341_COLOR_BLACK);
		TM_ILI9341_DrawRectangle(235,50+1+(HPF_State-1)*K,235+50,50+24+(HPF_State-1)*K,ILI9341_COLOR_BLACK);
	}

	if(HPF_State_Ant!=HPF_State)
	{
		TM_ILI9341_DrawRectangle(235,50+1+(HPF_State-1)*K,235+50,50+24+(HPF_State-1)*K,ILI9341_COLOR_BLUE);
		TM_ILI9341_DrawRectangle(235,50+1+(HPF_State_Ant-1)*K,235+50,50+24+(HPF_State_Ant-1)*K,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawRectangle(35,50+1+(LPF_State-1)*K,35+50,50+24+(LPF_State-1)*K,ILI9341_COLOR_BLACK);
		TM_ILI9341_DrawRectangle(135,50+1+(BPF_State-1)*K,135+50,50+24+(BPF_State-1)*K,ILI9341_COLOR_BLACK);
	}

	if(banda==1)
	{
		TM_ILI9341_DrawLine(inic,205,inic+50,205,ILI9341_COLOR_BLACK);
		TM_ILI9341_DrawLine(inic+100,205,inic+100+50,205,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawLine(inic+2*100,205,inic+2*100+50,205,ILI9341_COLOR_WHITE);

	}

	if(banda==2)
	{
		TM_ILI9341_DrawLine(inic,205,inic+50,205,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawLine(inic+100,205,inic+100+50,205,ILI9341_COLOR_BLACK);
		TM_ILI9341_DrawLine(inic+2*100,205,inic+2*100+50,205,ILI9341_COLOR_WHITE);

	}

	if(banda==3)
	{
		TM_ILI9341_DrawLine(inic,205,inic+50,205,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawLine(inic+100,205,inic+100+50,205,ILI9341_COLOR_WHITE);
		TM_ILI9341_DrawLine(inic+2*100,205,inic+2*100+50,205,ILI9341_COLOR_BLACK);

	}

	LPF_State_Ant=LPF_State;
	BPF_State_Ant=BPF_State;
	HPF_State_Ant=HPF_State;

	}


#endif



#endif /* DISPLAY_INIT_H_ */
