/*
 * i2s_hw.h
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */

#ifndef I2S_HW_H_
#define I2S_HW_H_


// DAC: PCM 1802
#define I2SRX_CLK			0,23
#define I2SRX_WS			0,24
#define I2SRX_SDA			0,25
#define RX_MCLK				4,28

// DAC: PCM 1781
#define I2STX_CLK			2,11
#define I2STX_WS			2,12
#define I2STX_SDA			2,13
#define TX_MCLK				4,29

Status mi_getClkDiv(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format, uint16_t *pxDiv, uint16_t *pyDiv, uint32_t *pN);
Status mi_Chip_I2S_TxConfig(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format);
Status mi_Chip_I2S_RxConfig(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format);
void InitI2S(void);



#endif /* I2S_HW_H_ */
