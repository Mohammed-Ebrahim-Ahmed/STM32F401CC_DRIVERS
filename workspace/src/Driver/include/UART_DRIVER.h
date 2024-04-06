#ifndef DRIVER_INCLUDE_UART_H_
#define DRIVER_INCLUDE_UART_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "stdint.h"

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define UART1 ((volatile void* const) 0x40011000)
#define UART2 ((volatile void* const) 0x40011400)
#define UART6 ((volatile void* const) 0x40004400)

#define TX_BUSY  0
#define TX_READY 1

#define RX_BUSY  0
#define RX_READY 1

#define WORDLENGTH_8BITS 0x0000
#define WORDLENGTH_9BITS 0x1000 

#define ONE_STOP_BIT      0x0000
#define HALF_STOP_BIT     0x1000
#define TWO_STOP_BIT      0x2000
#define ONE_HALF_STOP_BIT 0x3000

#define DMA_TRANS     0x80
#define DMA_RECEIVE   0x40

#define OVERSAMPLING_16 0x0000
#define OVERSAMPLING_8  0x8000

#define EVEN_PARITY 0x0
#define ODD_PARITY  0x200

#define BRAKE_10_BIT 0x00
#define BRAKE_11_BIT 0x20

#define F_CLK 16000000
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef enum{
    UART_Nullptr,
    UART_WrongLength,
    UART_WrongBus,
    UART_Ok,
    UART_NotOk,
    UART_WrongDMAConfig,
    UART_WrongWordLength,
    UART_WrongStopBit,
    UART_WrongMantissa,
    UART_WrongFraction,
    UART_WrongParity,
    UART_WrongBrakeLength
}UART_errorStatus_t;


typedef void (*TXCB_t)(void);
typedef void (*RXCB_t)(void);
typedef void (*BrakeCB_t)(void);

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/
UART_errorStatus_t UART_init(volatile void* UART_Bus);
UART_errorStatus_t UART_EnableDMA(volatile void* UART_Bus, uint8_t RECEIVETRANS); 
UART_errorStatus_t UART_SentBufferZCASYNC(volatile void* UART_Bus, uint8_t* buffer, uint16_t len, TXCB_t cb );
UART_errorStatus_t UART_RecieveBufferZCASYNC(volatile void* UART_Bus, uint8_t* buffer, uint16_t len, RXCB_t cb );
UART_errorStatus_t UART_Config(volatile void* UART_Bus, uint8_t WordLength, uint16_t stopbit, uint16_t OverSampling, uint16_t Baudrate);
UART_errorStatus_t UART_ControlConfigParity(volatile void* UART_Bus, uint8_t parity);
UART_errorStatus_t UART_Config_Generate_Brake(volatile void* UART_Bus, uint8_t BrakeLength);
UART_errorStatus_t UART_BrakeCB(volatile void* UART_Bus, BrakeCB_t BrakeCB);

#endif // DRIVER_INCLUDE_UART_H_