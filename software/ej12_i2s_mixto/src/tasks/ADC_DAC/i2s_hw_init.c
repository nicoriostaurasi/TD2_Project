/*
 * i2s_hw_init.c
 *
 *  Created on: 16 dic. 2019
 *      Author: nicol
 */


/*
 * i2s_hw_init.c
 *
 *  Created on: 14 dic. 2019
 *      Author: nicol
 */
#include "board.h"
#include "chip.h"
#include "i2s_hw.h"

Status mi_getClkDiv(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format, uint16_t *pxDiv, uint16_t *pyDiv, uint32_t *pN)
	{
		uint32_t pClk;
		uint32_t x, y;
		uint64_t divider;
		uint16_t dif;
		uint16_t xDiv = 0, yDiv = 0;
		uint32_t N;
		uint16_t err, ErrorOptimal = 0xFFFF;

	#if defined(CHIP_LPC175X_6X)
		pClk = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_I2S);
	#else
		pClk = Chip_Clock_GetPeripheralClockRate();
	#endif

		/* divider is a fixed point number with 16 fractional bits */
		divider = (((uint64_t) (format->SampleRate) * 2 * (format->WordWidth) * 2) << 16) / pClk;
		/* find N that make x/y <= 1 -> divider <= 2^16 */
		for (N = 64; N > 0; N--) {
			if ((divider * N) < (1 << 16)) {
				break;
			}
		}
		if (N == 0) {
			return ERROR;
		}
		divider *= N;
		for (y = 255; y > 0; y--) {
			x = y * divider;
			if (x & (0xFF000000)) {
				continue;
			}
			dif = x & 0xFFFF;
			if (dif > 0x8000) {
				err = 0x10000 - dif;
			}
			else {
				err = dif;
			}
			if (err == 0) {
				yDiv = y;
				break;
			}
			else if (err < ErrorOptimal) {
				ErrorOptimal = err;
				yDiv = y;
			}
		}
		xDiv = ((uint64_t) yDiv * (format->SampleRate) * 2 * (format->WordWidth) * N * 2) / pClk;
		if (xDiv >= 256) {
			xDiv = 0xFF;
		}
		if (xDiv == 0) {
			xDiv = 1;
		}

		*pxDiv = xDiv;
		*pyDiv = yDiv;
		*pN = N;
		return SUCCESS;
	}



Status mi_Chip_I2S_RxConfig(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format)
{
	uint32_t temp;
	uint16_t xDiv, yDiv;
	uint32_t N;

	if (mi_getClkDiv(pI2S, format, &xDiv, &yDiv, &N) == ERROR) {
		return ERROR;
	}

	temp = pI2S->DAI & (~(I2S_DAI_WORDWIDTH_MASK | I2S_DAI_MONO | I2S_DAI_SLAVE | I2S_DAI_WS_HALFPERIOD_MASK));
	if (format->WordWidth <= 8)
	{
		temp |= I2S_WORDWIDTH_8;
	}
	else if (format->WordWidth <= 16)
	{
		temp |= I2S_WORDWIDTH_16;
	}
	else
	{
		temp |= I2S_WORDWIDTH_32;
	}

	temp |= (format->ChannelNumber) == 1 ? I2S_MONO : I2S_STEREO;
	temp |= I2S_MASTER_MODE;
	temp |= I2S_DAI_WS_HALFPERIOD(format->WordWidth - 1);
	pI2S->DAI = temp;
	pI2S->RXMODE = 0x8;
	Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_I2S);
	xDiv = 32;
	yDiv = 125;
	pI2S->RXBITRATE = 5;
	pI2S->RXRATE = yDiv | (xDiv << 8);
	return SUCCESS;
}

Status mi_Chip_I2S_TxConfig(LPC_I2S_T *pI2S, I2S_AUDIO_FORMAT_T *format)
{
	uint32_t temp;
	uint16_t xDiv, yDiv;
	uint32_t N;


	if (mi_getClkDiv(pI2S, format, &xDiv, &yDiv, &N) == ERROR)
	{
		return ERROR;
	}

	temp = pI2S->DAO & (~(I2S_DAO_WORDWIDTH_MASK | I2S_DAO_MONO | I2S_DAO_SLAVE | I2S_DAO_WS_HALFPERIOD_MASK));
	if (format->WordWidth <= 8)
	{
		temp |= I2S_WORDWIDTH_8;
	}
	else if (format->WordWidth <= 16)
	{
		temp |= I2S_WORDWIDTH_16;
	}
	else
	{
		temp |= I2S_WORDWIDTH_32;
	}

	temp |= (format->ChannelNumber) == 1 ? I2S_MONO : I2S_STEREO;
	temp |= I2S_MASTER_MODE;
	temp |= I2S_DAO_WS_HALFPERIOD(format->WordWidth - 1);
	pI2S->DAO = temp;

	pI2S->TXMODE = 0x8;

	Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_I2S);

	xDiv = 32;
	yDiv = 125;

	pI2S->TXBITRATE = 5;

	pI2S->TXRATE = yDiv | (xDiv << 8);
	return SUCCESS;
}

void InitI2S(void)
{
	// Configuro el timer del micro en 96MHz
	Chip_SetupXtalClocking();
	Chip_SYSCTL_SetFLASHAccess(FLASHTIM_120MHZ_CPU);

	SystemCoreClockUpdate();

	// Inicializacion del I2S
	// Configuro los pines de RX de P0, ver defines
	Chip_IOCON_PinMux(LPC_IOCON, I2SRX_CLK, MD_PLN, IOCON_FUNC2);
	Chip_IOCON_PinMux(LPC_IOCON, I2SRX_SDA, MD_PLN, IOCON_FUNC2);
	Chip_IOCON_PinMux(LPC_IOCON, I2SRX_WS, MD_PLN, IOCON_FUNC2);
	Chip_IOCON_PinMux(LPC_IOCON, RX_MCLK, MD_PLN, IOCON_FUNC1);
	// Configuro los pibes del TX de P0, ver defines
	Chip_IOCON_PinMux(LPC_IOCON, I2STX_CLK, MD_PLN, IOCON_FUNC3);
	Chip_IOCON_PinMux(LPC_IOCON, I2STX_SDA, MD_PLN, IOCON_FUNC3);
	Chip_IOCON_PinMux(LPC_IOCON, I2STX_WS, MD_PLN, IOCON_FUNC3);
	Chip_IOCON_PinMux(LPC_IOCON, TX_MCLK, MD_PLN, IOCON_FUNC1);

	// Configuro I2S_TX usando la estructura I2S_AUDIO_FORMAT_T y modifico la función
	I2S_AUDIO_FORMAT_T audio_Config_rx;
	audio_Config_rx.SampleRate = 32000;
	audio_Config_rx.ChannelNumber = 2;			// 1 mono 2 stereo
	audio_Config_rx.WordWidth = 32;				// Word Len


	I2S_AUDIO_FORMAT_T audio_Config_tx;
	audio_Config_tx.SampleRate = 32000;
	audio_Config_tx.ChannelNumber = 2;			// 1 mono 2 stereo
	audio_Config_tx.WordWidth = 32;				// Word Len


	// Configuro el clk del periférico para que trabaje a 96MHz
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_I2S, SYSCTL_CLKDIV_1);

	Chip_I2S_Init(LPC_I2S);

	Chip_I2S_RxStop(LPC_I2S);
	Chip_I2S_TxStop(LPC_I2S);
	Chip_I2S_EnableMute(LPC_I2S);


	Chip_I2S_DisableMute(LPC_I2S);
	Chip_I2S_RxStart(LPC_I2S);
	Chip_I2S_TxStart(LPC_I2S);

	Chip_I2S_Int_RxCmd(LPC_I2S, ENABLE, 1);
	Chip_I2S_Int_TxCmd(LPC_I2S, ENABLE, 1);
	// Configuro modo RX
	mi_Chip_I2S_RxConfig(LPC_I2S, &audio_Config_rx);
	// Configuro modo TX
	mi_Chip_I2S_TxConfig(LPC_I2S, &audio_Config_tx);

	NVIC_EnableIRQ(I2S_IRQn);
}
