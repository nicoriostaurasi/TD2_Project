/*
 * display_int.c
 *
 */


#include "display_header.h"




	void TIMER1_IRQHandler( void )
	{

	   if( Chip_TIMER_MatchPending( LPC_TIMER1 , 0 ) )
	   {
		  Chip_TIMER_ClearMatch( LPC_TIMER1 , 0 );
//		  Chip_GPIO_SetPinOutHigh( LPC_GPIO , BL );
	   }
	   if( Chip_TIMER_MatchPending( LPC_TIMER1 , 1 ) )
	   {
		  Chip_TIMER_ClearMatch( LPC_TIMER1 , 1 );
//		  Chip_GPIO_SetPinOutLow( LPC_GPIO , BL );
	   }
	}


