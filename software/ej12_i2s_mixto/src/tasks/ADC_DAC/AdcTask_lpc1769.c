/*
 * AdcTask_lpc1769.c
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */
/*--------------------------------------------------------------------*-

    AdcTask_lpc1769.c (Released 2019-04)

  --------------------------------------------------------------------



-*--------------------------------------------------------------------*/


// Project header
#include "AdcTask_lpc1769.h"


// Task header


// ------ Public variable ------------------------------------------
// ------ Private constants ----------------------------------------
#define MAX_DURATION (1)

#define DWTINIT()		{DWT->CTRL|=DWT_CTRL_CYCCNTENA_Msk; DWT->CYCCNT=0;}
#define DWTRESET()		{DWT->CYCCNT=0;}
#define DWTREAD()		(DWT->CYCCNT)
// ------ Private data type ----------------------------------------
#define loopback 7
#define muteState 9
#define sum_eq 10

// ------ Private variable -----------------------------------------
static uint32_t Time_in_state_G,et=0,wcet=0,bcet=0;
static uint8_t Flag_ADC_Done=0;
static uint32_t vector_datos[TAM_BUFF_LP];
static uint16_t indice_lp=0;
static uint32_t vector_salida[TAM_BUFF_LP];
static uint32_t vector_lp[TAM_BUFF_LP];
static uint32_t vector_hp[TAM_BUFF_LP];
static uint32_t vector_bp[TAM_BUFF_LP];
extern volatile uint8_t control;
extern volatile uint8_t gainLPF;
extern volatile uint8_t gainHPF;
extern volatile uint8_t gainBPF;
extern volatile uint8_t banda;
/*------------------------------------------------------------------*-

    ADcTask_Init()

    Prepare for AdcTask_Init() function - see below.

-*------------------------------------------------------------------*/
void AdcDacI2S_Init(void)
{
	DWTINIT();
	Time_in_state_G=MAX_DURATION;
	InitI2S();

}


/*------------------------------------------------------------------*-



    Must schedule every 1 mili second (soft deadline).

-*------------------------------------------------------------------*/
void AdcDacI2S_Update(void)
{
	Time_in_state_G--;
	if(Time_in_state_G==0)
	{
		Time_in_state_G=MAX_DURATION;
/*	et=DWTREAD();
	if(wcet<et)wcet=et;
	if(et<bcet || bcet==0) bcet=et;*/
	}
}

/**
 * @brief	ADC interrupt handler sub-routine
 * @return	Nothing
 */

void I2S_IRQHandler(void)
{
	uint8_t contador200;
	uint32_t data;
	if(Chip_I2S_GetRxLevel(LPC_I2S))
	{
		data = Chip_I2S_Receive(LPC_I2S);		// Obtengo el dato recibido
		vector_datos[indice_lp]=data;
		indice_lp++;
		if(indice_lp>=TAM_BUFF_LP)
		{
			indice_lp=0;
			Flag_ADC_Done = 1;							// Flag que indica que hay un nuevo dato

			if(control==muteState)
			{
				muteOut(vector_datos,vector_salida,TAM_BUFF_LP);
			}

			else if(control==loopback)
			{
				loop_back(vector_datos,vector_salida,TAM_BUFF_LP);
			}

			else if(control==sum_eq)
			{
				LPF_filter(vector_datos,vector_lp, gainLPF-4);
				BPF_filter(vector_datos,vector_bp, gainBPF-4);
				HPF_filter(vector_datos,vector_hp, gainHPF-4);
				for(contador200=0;contador200<TAM_BUFF_LP;contador200++)
				{
				vector_salida[contador200]=vector_lp[contador200]+vector_bp[contador200]+vector_hp[contador200];
				}
			}

			else
			{
				switch(banda)
							{
							case 1:
								LPF_filter(vector_datos,vector_salida, gainLPF-3);
							break;
							case 2:
								BPF_filter(vector_datos,vector_salida, gainBPF-3);
							break;
							case 3:
								HPF_filter(vector_datos,vector_salida,gainHPF-3);
							break;
							default:
							break;
							}

			}
		}
		Chip_I2S_Send(LPC_I2S,vector_salida[indice_lp]);
//		Chip_I2S_Send(LPC_I2S,data);
	}
}



/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/


