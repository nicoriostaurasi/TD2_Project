/*
 * filtrado.c
 *
 *  Created on: 19 dic. 2019
 *      Author: nigomez
 */

//Filtrado

#include "filtrado.h"

float32_t coeffHP[]={0.159443263531322,	-0.318886527062644,	0.159443263531322,	0.462938025291041,	0.209715357756555};
float32_t coeffBP[]={0.0759844338617454,	0,	-0.0759844338617454,	-0.993470115648710,	0.804379905113461};
float32_t coeffLP[]={0.0873222795360372,	0.174644559072074,	0.0873222795360372,	-0.942809041582063,	0.333333333333333};


q31_t coeffTable[5];




void LPF_filter(q31_t* inputF32,q31_t* outputF32, uint8_t gain)
{
	//Transformo los coeficientes a q31
	arm_float_to_q31(coeffLP, coeffTable , 5);

	//Se declara el buffer de estados (4 * la cantidad de celdas de 2do orden)
	static q31_t biquadState[4*NUMSTAGES];

	//Creo estructura para instanciaciÃ³n del filtro
	static arm_biquad_casd_df1_inst_q31 S1;

	//Se desplaza la señal a derecha para evitar overflow
	for(int i=0; i<BLOCKSIZE; i++)
	{
		inputF32[i] = inputF32[i] >> 4;
	}

	//InicializaciÃ³n de la instancia de filtrado
	arm_biquad_cascade_df1_init_q31(&S1,NUMSTAGES,coeffTable,biquadState,0);

	//arm_biquad_cascade_df1_f32(&S1,inputF32,outputF32,BLOCKSIZE);
	//arm_biquad_cascade_df1_fast_q31	(&S1,inputF32,outputF32,BLOCKSIZE);
	arm_biquad_cascade_df1_q31	(&S1,inputF32,outputF32,BLOCKSIZE);
	//Desplazamiento en función de la ganancia
	for(int i=0; i<BLOCKSIZE; i++)
	{
			outputF32[i] = outputF32[i] << (3+gain);
	}

}

void BPF_filter(q31_t* inputF32,q31_t* outputF32, uint8_t gain)
{

	//Transformo los coeficientes a q31
	arm_float_to_q31(coeffBP, coeffTable , 5);

	//Se declara el buffer de estados (4 * la cantidad de celdas de 2do orden)
	static q31_t biquadState[4*NUMSTAGES];

	//Creo estructura para instanciaciÃ³n del filtro
	static arm_biquad_casd_df1_inst_q31 S1;

	//Se desplaza la señal a derecha para evitar overflow
	for(int i=0; i<BLOCKSIZE; i++)
	{
		inputF32[i] = inputF32[i] >> 5;
	}

	//InicializaciÃ³n de la instancia de filtrado
	arm_biquad_cascade_df1_init_q31(&S1,NUMSTAGES,coeffTable,biquadState,0);

	//Función de filtrado
//	arm_biquad_cascade_df1_fast_q31	(&S1,inputF32,outputF32,BLOCKSIZE);
	arm_biquad_cascade_df1_q31	(&S1,inputF32,outputF32,BLOCKSIZE);
	//Desplazamiento en función de la ganancia
	for(int i=0; i<BLOCKSIZE; i++)
	{
			outputF32[i] = outputF32[i] << (3+gain);
	}

}

void HPF_filter(q31_t* inputF32,q31_t* outputF32, uint8_t gain)
{

	//Transformo los coeficientes a q31
	arm_float_to_q31(coeffHP, coeffTable , 5);

	//Se declara el buffer de estados (4 * la cantidad de celdas de 2do orden)
	static q31_t biquadState[4*NUMSTAGES];


	//Creo estructura para instanciaciÃ³n del filtro

	static arm_biquad_casd_df1_inst_q31 S1;

	//Se desplaza la señal a derecha para evitar overflow
	for(int i=0; i<BLOCKSIZE; i++)
	{
		inputF32[i] = inputF32[i] >> 8;
	}

	//InicializaciÃ³n de la instancia de filtrado
	arm_biquad_cascade_df1_init_q31(&S1,NUMSTAGES,coeffTable,biquadState,0);

	//Función de filtrado
//	arm_biquad_cascade_df1_fast_q31	(&S1,inputF32,outputF32,BLOCKSIZE);
	arm_biquad_cascade_df1_q31	(&S1,inputF32,outputF32,BLOCKSIZE);
	//Desplazamiento en función de la ganancia
	for(int i=0; i<BLOCKSIZE; i++)
	{
			outputF32[i] = outputF32[i] << (7+gain);
	}

}

void loop_back(uint32_t *in, uint32_t *out, uint8_t BUFF)
{
	uint8_t i;
	for(i=0; i<BUFF; i++)
	{
	out[i]=in[i];
	}
}

void muteOut(uint32_t *in,uint32_t *out,uint8_t BUFF)
{
	uint8_t i;
		for(i=0; i<BUFF; i++)
		{
		out[i]=0x00000000;
		}
}
