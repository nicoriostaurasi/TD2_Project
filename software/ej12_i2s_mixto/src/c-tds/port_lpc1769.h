/*------------------------------------------------------------------*-

    port_lpc1769.h (Released 2019-04)

  ------------------------------------------------------------------

    This is the "Port Header" file: it documents usage of port pins
    in the project.

-*------------------------------------------------------------------*/

#ifndef _PORT_H
#define _PORT_H 1


// ------ Public constants -----------------------------------------
#define TIM_PRESCALE_USVAL	(100)


// Car wash Controller
#define SENSOR_ON	(true)
#define SENSOR_OFF	(false)
#define LOCK_ON	(true)
#define LOCK_OFF	(false)


// Allows Active Low or Active High led to be used (or other wiring variations)
#define LED_ON	(false)
#define LED_OFF	(true)


// Heartbeat LED
// Connected to "LED2" on LPC1769 board
// Port 0, Pin 22
#define HEARTBEAT_LED_PORT (0)
#define HEARTBEAT_LED_PIN (22)
#define HEARTBEAT_LED_PIN_MODE (IOCON_MODE_INACT)
#define HEARTBEAT_LED_PIN_FUNC (IOCON_FUNC0)
#define LED_VERDE 3,25
#define LED_AZUL 3,26

#define LOCK1_LED_PORT (2)
#define LOCK1_LED_PIN (11)
#define LOCK1_LED_PIN_MODE (IOCON_MODE_INACT)
#define LOCK1_LED_PIN_FUNC (IOCON_FUNC0)

#define RG1_LED_PORT (2)
#define RG1_LED_PIN (12)
#define RG1_LED_PIN_MODE (IOCON_MODE_INACT)
#define RG1_LED_PIN_FUNC (IOCON_FUNC0)


#define RG2_LED_PORT (2)
#define RG2_LED_PIN (4)
#define RG2_LED_PIN_MODE (IOCON_MODE_INACT)
#define RG2_LED_PIN_FUNC (IOCON_FUNC0)

#define LOCK2_LED_PORT (0)
#define LOCK2_LED_PIN (4)
#define LOCK2_LED_PIN_MODE (IOCON_MODE_INACT)
#define LOCK2_LED_PIN_FUNC (IOCON_FUNC0)

// RGB LED
// Connected to "BLUE" on LPC1769 board
// Port 0, Pin 26


// Allows NO or NC switch to be used (or other wiring variations)
#define SW_PRESSED		(false)
#define SW_NOT_PRESSED	(true)


// SW2-PRESS SWITCH
// Connected to "SW2 PRESS" on LPCXpresso baseboard
// Port 0, Pin 17
#define EM_SWITCH_PORT (0)
#define EM_SWITCH_PIN (7)
#define EM_SWITCH_PIN_MODE (IOCON_MODE_PULLUP)
#define EM_SWITCH_PIN_FUNC (IOCON_FUNC0)


// SW2-UP SWITCH
// Connected to "SW2 UP" on LPCXpresso baseboard
// Port 2, Pin 3
#define DOOR1_SWITCH_PORT (0)
#define DOOR1_SWITCH_PIN (18)
#define DOOR1_SWITCH_PIN_MODE (IOCON_MODE_PULLUP)
#define DOOR1_SWITCH_PIN_FUNC (IOCON_FUNC0)


// SW2-DOWN SWITCH
// Connected to "SW2 DOWN" on LPCXpresso baseboard
// Port 0, Pin 15


// SW2-LEFT SWITCH
// Connected to "SW2 LEFT" on LPCXpresso baseboard
// Port 2, Pin 4


// SW2-RIGHT SWITCH
// Connected to "SW2 RIGHT" on LPCXpresso baseboard
// Port 0, Pin 16


// SW3 SWITCH
// Connected to "SW3" on LPCXpresso baseboard
// Port 2, Pin 10
#define DOOR2_SWITCH_PORT (0)
#define DOOR2_SWITCH_PIN (1)
#define DOOR2_SWITCH_PIN_MODE (IOCON_MODE_PULLUP)
#define DOOR2_SWITCH_PIN_FUNC (IOCON_FUNC0)


// SW4 SWITCH
// Connected to "SW4" on LPCXpresso baseboard
// Port 1, Pin 31
#define S3_SWITCH_PORT (1)
#define S3_SWITCH_PIN (31)
#define S3_SWITCH_PIN_MODE (IOCON_MODE_PULLUP)
#define S3_SWITCH_PIN_FUNC (IOCON_FUNC0)


// Add jumper wire on baseboard to control WDT
// WDT is enabled *only* if jumper is in place.
// (Jumper is read at init phase only)
// Port 2, Pin 3 => Connected to "SW2 UP" on LPCXpresso baseboard
#define WDT_JUMPER_PORT (0)
#define WDT_JUMPER_PIN (23)
#define WDT_JUMPER_PIN_MODE (IOCON_MODE_PULLUP)
#define WDT_JUMPER_PIN_FUNC (IOCON_FUNC0)


// ------ Public data type declarations ----------------------------


// ------ Public function prototypes -------------------------------


#endif


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
