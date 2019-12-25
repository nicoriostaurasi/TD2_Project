/*
 * GpiosTask_lpc1769.c
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 *
 *
 */
#include "GpiosTask_lpc1769.h"

#define MAX_DURATION (1)


volatile uint8_t ESTADO_TECLA_1;
volatile uint8_t ESTADO_TECLA_2;
volatile uint8_t ESTADO_TECLA_3;
volatile uint8_t ESTADO_TECLA_4;
volatile uint8_t ESTADO_TECLA_5;
volatile uint8_t ESTADO_TECLA_6;

static uint8_t estado_ant1=0;
static uint8_t estado_ant2=0;
static uint8_t estado_ant3=0;
static uint8_t estado_ant4=0;
static uint8_t estado_ant5=0;
static uint8_t estado_ant6=0;

static uint8_t cant_estados_1;
static uint8_t cant_estados_2;
static uint8_t cant_estados_3;
static uint8_t cant_estados_4;
static uint8_t cant_estados_5;
static uint8_t cant_estados_6;

static uint32_t Time_in_state_G,et=0,wcet=0,bcet=0;

void GPIOS_Init(void)
{
	Chip_GPIO_SetPinDIR(LPC_GPIO,PUL_1, FALSE);
	Chip_GPIO_SetPinDIR(LPC_GPIO,PUL_2, FALSE);
	Chip_GPIO_SetPinDIR(LPC_GPIO,PUL_3, FALSE);
	Chip_GPIO_SetPinDIR(LPC_GPIO,PUL_4, FALSE);
	Chip_GPIO_SetPinDIR(LPC_GPIO,PUL_5, FALSE);
	Chip_GPIO_SetPinDIR(LPC_GPIO,PUL_6, FALSE);

	ESTADO_TECLA_1=true;
	ESTADO_TECLA_2=true;
	ESTADO_TECLA_3=true;
	ESTADO_TECLA_4=true;
	ESTADO_TECLA_5=true;
	ESTADO_TECLA_6=true;
}

void GPIOS_Update(void)
{
	if(Time_in_state_G==0)
	{
	//////////////////////////////////////////////////////////////////////////////
	if(Chip_GPIO_GetPinState(LPC_GPIO,PUL_1)==false)
	{
		if(estado_ant1==false)
		{
			cant_estados_1++;
			if(cant_estados_1>=ANTI_REBOTE)
			{
				cant_estados_1=0;
				ESTADO_TECLA_1=false;
			}
		}
		else
		{
			cant_estados_1=0;
		}
		estado_ant1=false;
	}
	else
	{
		if(estado_ant1==true)
				{
					cant_estados_1++;
					if(cant_estados_1>=ANTI_REBOTE)
					{
						cant_estados_1=0;
						ESTADO_TECLA_1=true;
					}
				}
				else
				{
					cant_estados_1=0;
				}
				estado_ant1=true;

	}
////////////////////////////////////////////////////////////////////////////////////

	if(Chip_GPIO_GetPinState(LPC_GPIO,PUL_2)==false)
	{
		if(estado_ant2==false)
		{
			cant_estados_2++;
			if(cant_estados_2>=ANTI_REBOTE)
			{
				cant_estados_2=0;
				ESTADO_TECLA_2=false;
			}
		}
		else
		{
			cant_estados_2=0;
		}
		estado_ant2=false;
	}
	else
	{
		if(estado_ant2==true)
				{
					cant_estados_2++;
					if(cant_estados_2>=ANTI_REBOTE)
					{
						cant_estados_2=0;
						ESTADO_TECLA_2=true;
					}
				}
				else
				{
					cant_estados_2=0;
				}
				estado_ant2=true;

	}

///////////////////////////////////////////////////////////////////////////////////

	if(Chip_GPIO_GetPinState(LPC_GPIO,PUL_3)==false)
	{
		if(estado_ant3==false)
		{
			cant_estados_3++;
			if(cant_estados_3>=ANTI_REBOTE)
			{
				cant_estados_3=0;
				ESTADO_TECLA_3=false;
			}
		}
		else
		{
			cant_estados_3=0;
		}
		estado_ant3=false;
	}
	else
	{
		if(estado_ant3==true)
				{
					cant_estados_3++;
					if(cant_estados_3>=ANTI_REBOTE)
					{
						cant_estados_3=0;
						ESTADO_TECLA_3=true;
					}
				}
				else
				{
					cant_estados_3=0;
				}
				estado_ant3=true;

	}

//////////////////////////////////////////////////////////////////////////////////

	if(Chip_GPIO_GetPinState(LPC_GPIO,PUL_4)==false)
	{
		if(estado_ant4==false)
		{
			cant_estados_4++;
			if(cant_estados_4>=ANTI_REBOTE)
			{
				cant_estados_4=0;
				ESTADO_TECLA_4=false;
			}
		}
		else
		{
			cant_estados_4=0;
		}
		estado_ant4=false;
	}
	else
	{
		if(estado_ant4==true)
				{
					cant_estados_4++;
					if(cant_estados_4>=ANTI_REBOTE)
					{
						cant_estados_4=0;
						ESTADO_TECLA_4=true;
					}
				}
				else
				{
					cant_estados_4=0;
				}
				estado_ant4=true;

	}

///////////////////////////////////////////////////////////////////////////////////
	if(Chip_GPIO_GetPinState(LPC_GPIO,PUL_5)==false)
	{
		if(estado_ant5==false)
		{
			cant_estados_5++;
			if(cant_estados_5>=ANTI_REBOTE)
			{
				cant_estados_5=0;
				ESTADO_TECLA_5=false;
			}
		}
		else
		{
			cant_estados_5=0;
		}
		estado_ant5=false;
	}
	else
	{
		if(estado_ant5==true)
				{
					cant_estados_5++;
					if(cant_estados_5>=ANTI_REBOTE)
					{
						cant_estados_5=0;
						ESTADO_TECLA_5=true;
					}
				}
				else
				{
					cant_estados_5=0;
				}
				estado_ant5=true;

	}
	////////////////////////////////////////////////////////////////////////

	if(Chip_GPIO_GetPinState(LPC_GPIO,PUL_6)==false)
	{
		if(estado_ant6==false)
		{
			cant_estados_6++;
			if(cant_estados_6>=ANTI_REBOTE)
			{
				cant_estados_6=0;
				ESTADO_TECLA_6=false;
			}
		}
		else
		{
			cant_estados_6=0;
		}
		estado_ant6=false;
	}
	else
	{
		if(estado_ant6==true)
				{
					cant_estados_6++;
					if(cant_estados_6>=ANTI_REBOTE)
					{
						cant_estados_6=0;
						ESTADO_TECLA_6=true;
					}
				}
				else
				{
					cant_estados_6=0;
				}
				estado_ant6=true;

	}

	//////////////////////////////////////////////////////////////////////
	Time_in_state_G=MAX_DURATION;
	}

	else
	{
	Time_in_state_G--;
	}
//////////////////////////////////////////////////////////////////////////////////
}



