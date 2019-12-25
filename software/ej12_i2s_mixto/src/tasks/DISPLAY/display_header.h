/*
 * diaplay_header.h
 *
 */

#ifndef DISPLAY_HEADER_H_
#define DISPLAY_HEADER_H_

#define DISPLAY_BUENO 1
#define DISPLAY_MALO 0
/*
#define DISPLAY_BUENO OFF
#define DISPLAY_MALO ON
*/

// ********* FUNCIONES ********** //
// ****************************** //
#include "board.h"
#include "chip.h"

// ***************** DEFINES ***************** //

		// LCD pinout
#if(DISPLAY_BUENO==1)
// LCD pinout
#define DB0		0,17
#define DB1		2,1
#define DB2		0,18
#define DB3		2,2
#define DB4		0,7
#define DB5		2,3
#define DB6		0,6
#define DB7		2,4
#define DB8		0,0
#define DB9		2,5
#define DB10	0,1
#define DB11	2,6
#define DB12	0,8
#define DB13	2,7
#define DB14	0,9
#define DB15	2,8

#define READ_DATA	0,4
#define RS		0,5
#define CS		0,10
#define WR		0,11
#define REST	2,0
#define BL		2,10

//#define BL			2,10

#endif


#if(DISPLAY_MALO==1)
#define DB0			0,6
#define DB1			2,1
#define DB2			0,0
#define DB3			2,2
#define DB4			0,1
#define DB5			2,3
#define DB6			0,18
#define DB7			2,4
#define DB8			0,17
#define DB9			2,5
#define DB10		0,15
#define DB11		2,6
#define DB12		0,16
#define DB13		2,7
#define DB14		0,23
#define DB15		2,8

#define READ_DATA	0,7
#define RS			0,8
#define CS			0,4
#define WR			0,5
#define REST		0,11
//#define BL			2,10
#endif

		// LCD size
		#define WINDOWWIDTHX2		230		//DISTANCIA DESDE EL SUPERIOR
		#define WINDOWHEIGTHX2		310		//DISTANCIA DESDE LA DERECHA
		#define WINDOWHEIGTHX1		85		//DISTANCIA DESDE LA IZQUIERDA
		#define WINDOWWIDTHX1		30		//DISTANCIA DESDE EL INFERIOR
		#define WINDOWMULTIPLIER    190
		#define RECTHEIGHT 			WINDOWHEIGTHX2-WINDOWHEIGTHX1

		// LCD settings
		#define ILI9341_WIDTH 		240		//Alto del display
		#define ILI9341_HEIGHT		320		//Ancho del display
		#define ILI9341_PIXEL		76800	//Cantidad de pixels en pantalla
		#define ILI9341_HFACTOR		4095	//Cantidad de cuentas del ADC (12bits)

		// LCD colours
		#define ILI9341_COLOR_WHITE			0xFFFF
		#define ILI9341_COLOR_BLACK			0x0000
		#define ILI9341_COLOR_RED			0xF800
		#define ILI9341_COLOR_GREEN			0x07E0
		#define ILI9341_COLOR_GREEN2		0xB723
		#define ILI9341_COLOR_BLUE			0x001F
		#define ILI9341_COLOR_BLUE2			0x051D
		#define ILI9341_COLOR_YELLOW		0xFFE0
		#define ILI9341_COLOR_ORANGE		0xFBE4
		#define ILI9341_COLOR_CYAN			0x07FF
		#define ILI9341_COLOR_MAGENTA		0xA254
		#define ILI9341_COLOR_GRAY			0x7BEF
		#define ILI9341_COLOR_BROWN			0xBBCA

		// LCD commands
		#define ILI9341_RESET				0x01
		#define ILI9341_SLEEP_OUT			0x11
		#define ILI9341_GAMMA				0x26
		#define ILI9341_DISPLAY_OFF			0x28
		#define ILI9341_DISPLAY_ON			0x29
		#define ILI9341_COLUMN_ADDR			0x2A
		#define ILI9341_PAGE_ADDR			0x2B
		#define ILI9341_GRAM				0x2C
		#define ILI9341_MAC					0x36
		#define ILI9341_PIXEL_FORMAT		0x3A
		#define ILI9341_WDB					0x51	// Write Display Brightness
		#define ILI9341_WCD					0x53	// Write CTRL Display
		#define ILI9341_WCABC				0x55	// Write Content Adaptative Brightness Control
		#define ILI9341_RGB_INTERFACE		0xB0
		#define ILI9341_FRC					0xB1
		#define ILI9341_BPC					0xB5
		#define ILI9341_DFC					0xB6
		#define ILI9341_POWER1				0xC0
		#define ILI9341_POWER2				0xC1
		#define ILI9341_VCOM1				0xC5
		#define ILI9341_VCOM2				0xC7
		#define ILI9341_POWERA				0xCB
		#define ILI9341_POWERB				0xCF
		#define ILI9341_PGAMMA				0xE0
		#define ILI9341_NGAMMA				0xE1
		#define ILI9341_DTCA				0xE8
		#define ILI9341_DTCB				0xEA
		#define ILI9341_POWER_SEQ			0xED
		#define ILI9341_3GAMMA_EN			0xF2
		#define ILI9341_INTERFACE			0xF6
		#define ILI9341_PRC					0xF7

// ******************************************* //


// *************** ESTRUCTURAS *************** //

		// Orientation: Used private
		typedef enum {
			TM_ILI9341_Landscape,
			TM_ILI9341_Portrait,
			TM_ILI9341_Orientation_Portrait_1,
			TM_ILI9341_Orientation_Portrait_2,
			TM_ILI9341_Orientation_Landscape_1,
			TM_ILI9341_Orientation_Landscape_2
		} TM_ILI9341_Orientation;

		// LCD options: Used private
		typedef struct {
			unsigned short int width;
			unsigned short int height;
			TM_ILI9341_Orientation orientation; // 1 = portrait; 0 = landscape
		} TM_ILI931_Options_t;

// ******************************************* //


// ************* VARIABLES GLOBALES ************* //

		extern volatile uint16_t ILI9341_x;
		extern volatile uint16_t ILI9341_y;

		extern volatile TM_ILI931_Options_t ILI9341_Opts;

		extern volatile uint8_t ILI9341_INT_CalledFromPuts;

		extern volatile uint8_t using_tft;

// ********************************************** //


// ************* HEADERS ************* //

		#include "fonts.h"
		#include "display_func.h"
		#include "display_init.h"

// ****************************************** //


#endif /* DISPLAY_HEADER_H_ */

