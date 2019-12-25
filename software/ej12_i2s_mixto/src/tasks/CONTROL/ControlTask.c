/*
 * ControlTask.c
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */

#include "ControlTask.h"



extern uint8_t ESTADO_TECLA_1;
extern uint8_t ESTADO_TECLA_2;
extern uint8_t ESTADO_TECLA_3;
extern uint8_t ESTADO_TECLA_4;
extern uint8_t ESTADO_TECLA_5;
extern uint8_t ESTADO_TECLA_6;
typedef enum{incremento_b,decremento_b,incremento_g,decremento_g,idle,wait,wait2,loopback,wait3,muteState,sum_eq,wait4}STATE_G;
volatile STATE_G control=idle;
volatile uint8_t banda=1;
volatile uint8_t gainLPF=1;
volatile uint8_t gainBPF=1;
volatile uint8_t gainHPF=1;

volatile uint8_t flag_display;


void Control_Update(void)
{
	static uint16_t TIME_IN_STATE=0;
switch(control)
{
	case idle:
	{
	if(ESTADO_TECLA_1==false)
	{
		control=incremento_g;
	}

	else if(ESTADO_TECLA_3==false)
	{
		control=incremento_b;
	}

	if(ESTADO_TECLA_2==false)
	{
		control=decremento_g;
	}

	else if(ESTADO_TECLA_4==false)
	{
		control=decremento_b;
	}
	else if(ESTADO_TECLA_5==false)
	{
		control=wait2;
	}
	else if(ESTADO_TECLA_6==false)
	{
		control=wait3;
	}

	break;
	}

	case incremento_b:
	{
	banda++;
	if(banda>3)
	{
	banda=1;
	}
	flag_display=1;
	control=wait;
	break;
	}

	case decremento_b:
	{
	banda--;
	if(banda<1)
	{
	banda=3;
	}
	flag_display=1;
	control=wait;
	break;
	}

	case incremento_g:
	{
	if(banda==1)
	{
		gainLPF++;
		if(gainLPF>5)
		{
		gainLPF=1;
		}
	}

	if(banda==2)
		{
			gainBPF++;
			if(gainBPF>5)
			{
			gainBPF=1;
			}
		}

	if(banda==3)
		{
			gainHPF++;
			if(gainHPF>5)
			{
			gainHPF=1;
			}
		}
	flag_display=1;
	control=wait;
	break;
	}

	case decremento_g:
	{
	if(banda==1)
	{
		gainLPF--;
		if(gainLPF<1)
		{
		gainLPF=5;
		}
	}

	if(banda==2)
		{
			gainBPF--;
			if(gainBPF<1)
			{
			gainBPF=5;
			}
		}

	if(banda==3)
		{
			gainHPF--;
			if(gainHPF<1)
			{
			gainHPF=5;
			}
		}
	flag_display=1;
	control=wait;
	break;
	}

	case wait:
	{
	TIME_IN_STATE++;
	if(TIME_IN_STATE>=1000)
	{
	TIME_IN_STATE=0;
	control=idle;
	}
	break;
	}

	case wait2:
	{
	TIME_IN_STATE++;
	if(TIME_IN_STATE>=1000)
	{
	TIME_IN_STATE=0;
	control=loopback;
	}
	break;
	}

	case wait3:
	{
	TIME_IN_STATE++;
	if(TIME_IN_STATE>=1000)
	{
	TIME_IN_STATE=0;
	control=muteState;
	}
	break;
	}
	case wait4:
	{
	TIME_IN_STATE++;
	if(TIME_IN_STATE>=1000)
	{
	TIME_IN_STATE=0;
	control=sum_eq;
	}
	break;
	}

	case loopback:
	{
		if(ESTADO_TECLA_5==false)
		{
		control=wait;
		}
		else if(ESTADO_TECLA_6==false)
		{
		control=wait3;
		}
		else if(ESTADO_TECLA_1==false)
		{
		control=wait4;
		}

	break;
	}

	case muteState:
	{
	if(ESTADO_TECLA_5==false)
	{
	control=wait;
	}

	break;
	}

	case sum_eq:
	{
		if(ESTADO_TECLA_5==false)
		{
		control=wait;
		}
	}

	default:
	{
	break;
	}

}

}
