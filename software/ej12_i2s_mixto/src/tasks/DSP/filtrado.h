/*
 * filtrado.h
 *
 *  Created on: 19 dic. 2019
 *      Author: nicol
 */

#ifndef FILTRADO_H_
#define FILTRADO_H_
#include "../../CMSIS_DSPLIB_CM3/inc/arm_math.h"

#define TAM_BUFF_LP		8
#define BLOCKSIZE 	8 //Cantidad de muestras
#define NUMSTAGES 	1 //Cantidad de celdas de 2do orden

void LPF_filter(q31_t* inputF32,q31_t* outputF32, uint8_t gain);
void BPF_filter(q31_t* inputF32,q31_t* outputF32, uint8_t gain);
void HPF_filter(q31_t* inputF32,q31_t* outputF32, uint8_t gain);
void loop_back(uint32_t *in, uint32_t *out, uint8_t BUFF);
void muteOut(uint32_t *in,uint32_t *out,uint8_t BUFF);
#endif /* FILTRADO_H_ */
