/*
 * Copyright 2022, 2025 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RTE_DEVICE_H
#define _RTE_DEVICE_H

extern void LPSPI1_InitPins();
extern void LPSPI1_DeinitPins();

extern void LPI2C3_InitPins();
extern void LPI2C3_DeinitPins();

extern void LPI2C9_InitPins();
extern void LPI2C9_DeinitPins();

/*Driver name mapping.*/
/* User needs to provide the implementation of LPSPIX_GetFreq/LPSPIX_InitPins/LPSPIX_DeinitPins for the enabled LPSPI
 * instance. */
#define RTE_SPI1        1
#define RTE_SPI1_DMA_EN 0

/* SPI configuration. */
#define RTE_SPI1_PCS_TO_SCK_DELAY       0
#define RTE_SPI1_SCK_TO_PSC_DELAY       0
#define RTE_SPI1_BETWEEN_TRANSFER_DELAY 0
#define RTE_SPI1_MASTER_PCS_PIN_SEL     (kLPSPI_MasterPcs1)
#define RTE_SPI1_SLAVE_PCS_PIN_SEL      (kLPSPI_SlavePcs1)
#define RTE_SPI1_PIN_INIT               LPSPI1_InitPins
#define RTE_SPI1_PIN_DEINIT             LPSPI1_DeinitPins
#define RTE_SPI1_DMA_TX_CH              0
#define RTE_SPI1_DMA_TX_PERI_SEL        (uint16_t) kDma0RequestMuxLpFlexcomm1Tx
#define RTE_SPI1_DMA_TX_DMA_BASE        DMA0
#define RTE_SPI1_DMA_RX_CH              1
#define RTE_SPI1_DMA_RX_PERI_SEL        (uint16_t) kDma0RequestMuxLpFlexcomm1Rx
#define RTE_SPI1_DMA_RX_DMA_BASE        DMA0

//
//
//#define RTE_USART0        0
//#define RTE_USART0_DMA_EN 0
//#define RTE_USART1        0
//#define RTE_USART1_DMA_EN 0
//#define RTE_USART2        0
//#define RTE_USART2_DMA_EN 0
//#define RTE_USART3        0
//#define RTE_USART3_DMA_EN 0
//#define RTE_USART4        0
//#define RTE_USART4_DMA_EN 0
//#define RTE_USART5        0
//#define RTE_USART5_DMA_EN 0
//#define RTE_USART6        0
//#define RTE_USART6_DMA_EN 0
//#define RTE_USART7        0
//#define RTE_USART7_DMA_EN 0
//
///* USART configuration. */
//#define USART_RX_BUFFER_LEN     64
//#define USART0_RX_BUFFER_ENABLE 0
//#define USART1_RX_BUFFER_ENABLE 0
//#define USART2_RX_BUFFER_ENABLE 0
//#define USART3_RX_BUFFER_ENABLE 0
//#define USART4_RX_BUFFER_ENABLE 0
//#define USART5_RX_BUFFER_ENABLE 0
//#define USART6_RX_BUFFER_ENABLE 0
//#define USART7_RX_BUFFER_ENABLE 0
//
//#define RTE_USART0_PIN_INIT        USART0_InitPins
//#define RTE_USART0_PIN_DEINIT      USART0_DeinitPins
//#define RTE_USART0_DMA_TX_CH       5
//#define RTE_USART0_DMA_TX_DMA_BASE DMA0
//#define RTE_USART0_DMA_RX_CH       4
//#define RTE_USART0_DMA_RX_DMA_BASE DMA0
//
//#define RTE_USART1_PIN_INIT        USART1_InitPins
//#define RTE_USART1_PIN_DEINIT      USART1_DeinitPins
//#define RTE_USART1_DMA_TX_CH       7
//#define RTE_USART1_DMA_TX_DMA_BASE DMA0
//#define RTE_USART1_DMA_RX_CH       6
//#define RTE_USART1_DMA_RX_DMA_BASE DMA0
//
//#define RTE_USART2_PIN_INIT        USART2_InitPins
//#define RTE_USART2_PIN_DEINIT      USART2_DeinitPins
//#define RTE_USART2_DMA_TX_CH       8
//#define RTE_USART2_DMA_TX_DMA_BASE DMA0
//#define RTE_USART2_DMA_RX_CH       9
//#define RTE_USART2_DMA_RX_DMA_BASE DMA0
//
//#define RTE_USART3_PIN_INIT        USART3_InitPins
//#define RTE_USART3_PIN_DEINIT      USART3_DeinitPins
//#define RTE_USART3_DMA_TX_CH       10
//#define RTE_USART3_DMA_TX_DMA_BASE DMA0
//#define RTE_USART3_DMA_RX_CH       11
//#define RTE_USART3_DMA_RX_DMA_BASE DMA0
//
//#define RTE_USART4_PIN_INIT        USART4_InitPins
//#define RTE_USART4_PIN_DEINIT      USART4_DeinitPins
//#define RTE_USART4_DMA_TX_CH       13
//#define RTE_USART4_DMA_TX_DMA_BASE DMA0
//#define RTE_USART4_DMA_RX_CH       12
//#define RTE_USART4_DMA_RX_DMA_BASE DMA0
//
//#define RTE_USART5_PIN_INIT        USART5_InitPins
//#define RTE_USART5_PIN_DEINIT      USART5_DeinitPins
//#define RTE_USART5_DMA_TX_CH       15
//#define RTE_USART5_DMA_TX_DMA_BASE DMA0
//#define RTE_USART5_DMA_RX_CH       14
//#define RTE_USART5_DMA_RX_DMA_BASE DMA0
//
//#define RTE_USART6_PIN_INIT        USART6_InitPins
//#define RTE_USART6_PIN_DEINIT      USART6_DeinitPins
//#define RTE_USART6_DMA_TX_CH       17
//#define RTE_USART6_DMA_TX_DMA_BASE DMA0
//#define RTE_USART6_DMA_RX_CH       16
//#define RTE_USART6_DMA_RX_DMA_BASE DMA0
//
//#define RTE_USART7_PIN_INIT        USART7_InitPins
//#define RTE_USART7_PIN_DEINIT      USART7_DeinitPins
//#define RTE_USART7_DMA_TX_CH       19
//#define RTE_USART7_DMA_TX_DMA_BASE DMA0
//#define RTE_USART7_DMA_RX_CH       18
//#define RTE_USART7_DMA_RX_DMA_BASE DMA0

/* I2C Select, I2C0 -I2C7*/
/* User needs to provide the implementation of I2CX_GetFreq/I2CX_InitPins/I2CX_DeinitPins for the enabled I2C instance.
 */
//#define RTE_I2C0        0
//#define RTE_I2C0_DMA_EN 0
//#define RTE_I2C1        0
//#define RTE_I2C1_DMA_EN 0
//#define RTE_I2C2        0
//#define RTE_I2C2_DMA_EN 0
#define RTE_I2C3        1
#define RTE_I2C3_DMA_EN 0
//#define RTE_I2C4        0
//#define RTE_I2C4_DMA_EN 0
//#define RTE_I2C5        0
//#define RTE_I2C5_DMA_EN 0
//#define RTE_I2C6        0
//#define RTE_I2C6_DMA_EN 0
//#define RTE_I2C7        0
//#define RTE_I2C7_DMA_EN 0
#define RTE_I2C9        1
#define RTE_I2C9_DMA_EN 0

/*I2C configuration*/
#define RTE_I2C3_PIN_INIT        LPI2C3_InitPins
#define RTE_I2C3_PIN_DEINIT      LPI2C3_DeinitPins

#define RTE_I2C9_PIN_INIT        LPI2C9_InitPins
#define RTE_I2C9_PIN_DEINIT      LPI2C9_DeinitPins
//
//#define RTE_I2C0_Master_DMA_BASE DMA0
//#define RTE_I2C0_Master_DMA_CH   1
//
//#define RTE_I2C1_Master_DMA_BASE DMA0
//#define RTE_I2C1_Master_DMA_CH   3
//
//#define RTE_I2C2_Master_DMA_BASE DMA0
//#define RTE_I2C2_Master_DMA_CH   5

#define RTE_I2C3_Master_DMA_BASE DMA0
#define RTE_I2C3_Master_DMA_CH   7

//#define RTE_I2C4_Master_DMA_BASE DMA0
//#define RTE_I2C4_Master_DMA_CH   9
//
//#define RTE_I2C5_Master_DMA_BASE DMA0
//#define RTE_I2C5_Master_DMA_CH   11
//
//#define RTE_I2C6_Master_DMA_BASE DMA0
//#define RTE_I2C6_Master_DMA_CH   13
//
//#define RTE_I2C7_Master_DMA_BASE DMA0
//#define RTE_I2C7_Master_DMA_CH   15

#define RTE_I2C9_Master_DMA_BASE DMA0
#define RTE_I2C9_Master_DMA_CH   19


#endif /* _RTE_DEVICE_H */
