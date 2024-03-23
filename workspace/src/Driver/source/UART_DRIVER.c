#include "UART_DRIVER.h"
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#ifndef NULL
#define NULL (void*)0
#endif

#define TXE  0x80
#define RXNE 0x20
#define TXEIE 0x80
#define RXNEIE 0x20
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct {
    volatile uint32_t USART_SR;
    volatile uint32_t USART_DR;
    volatile uint32_t USART_BRR;
    volatile uint32_t USART_CR1;
    volatile uint32_t USART_CR2;
    volatile uint32_t USART_CR3;
}UART_t;

typedef struct {
    uint8_t* buffer;
    uint16_t len;
    uint16_t position;
} buffer_t;

typedef struct {
    buffer_t TXbuffer;
    uint8_t TXstate;
    TXCB_t TXCB;
} TX_Buffer_t;

typedef struct {
    buffer_t RXbuffer;
    uint8_t RXstate;
    RXCB_t RXCB;
} RX_Buffer_t;
/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
volatile static TX_Buffer_t TX_Buffer = {
    .TXbuffer = NULL,
    .TXCB = NULL,
    .TXstate = TX_READY
};

volatile static RX_Buffer_t RX_Buffer = {
    .RXbuffer = NULL,
    .RXCB = NULL,
    .RXstate = RX_READY
};

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

UART_errorStatus_t UART_SentBufferZCASYNC(volatile void* UART_Bus, uint8_t *buffer, uint16_t len, TXCB_t cb)
{
    UART_errorStatus_t UART_errorStatus = UART_NotOk;

    if(buffer == NULL)
    {
        UART_errorStatus = UART_Nullptr;
    }
    else if(UART_Bus != UART1 && UART_Bus != UART2 && UART_Bus != UART6)
    {
        UART_errorStatus = UART_WrongBus;
    }
    else if(len >  65535)
    {
        UART_errorStatus = UART_WrongLength;
    }
    else
    {
        UART_errorStatus = UART_Ok;

        if(TX_Buffer.TXstate == TX_READY)
        {
            TX_Buffer.TXstate = TX_BUSY;
            TX_Buffer.TXbuffer.buffer = buffer;
            TX_Buffer.TXbuffer.len = len;
            TX_Buffer.TXbuffer.position = 0;
            TX_Buffer.TXCB = cb;
            ((volatile UART_t * const)UART1)->USART_CR1 |= TXEIE;
            ((volatile UART_t * const)UART1)->USART_DR = TX_Buffer.TXbuffer.buffer[0];
            TX_Buffer.TXbuffer.position ++; 
        }
        

    }
    return UART_errorStatus;
}

UART_errorStatus_t UART_RecieveBufferZCASYNC(volatile void* UART_Bus, uint8_t *buffer, uint16_t len, RXCB_t cb)
{
    UART_errorStatus_t UART_errorStatus = UART_NotOk;

    if(buffer == NULL)
    {
        UART_errorStatus = UART_Nullptr;
    }
    else if(UART_Bus != UART1 && UART_Bus != UART2 && UART_Bus != UART6)
    {
        UART_errorStatus = UART_WrongBus;
    }
    else if(len >  65535)
    {
        UART_errorStatus = UART_WrongLength;
    }
    else
    {
        UART_errorStatus = UART_Ok;
        if(RX_Buffer.RXstate == RX_READY)
        {
            ((volatile UART_t * const)UART1)->USART_CR1 &= ~RXNEIE;
            RX_Buffer.RXstate = RX_BUSY;
            RX_Buffer.RXbuffer.buffer = buffer;
            RX_Buffer.RXbuffer.len = len;
            RX_Buffer.RXbuffer.position = 0;
            RX_Buffer.RXCB = cb;
            ((volatile UART_t * const)UART1)->USART_CR1 |= RXNEIE;
        }        
    }
    return UART_errorStatus;
}


void USART1_IRQHandler (void)
{
    if( (((volatile UART_t * const)UART1)->USART_DR & TXE) )
    {
        if(TX_Buffer.TXbuffer.position < TX_Buffer.TXbuffer.len)
        {
            ((volatile UART_t * const)UART1)->USART_DR = TX_Buffer.TXbuffer.buffer[TX_Buffer.TXbuffer.position];
            TX_Buffer.TXbuffer.position++;
        }
        else
        {
            TX_Buffer.TXstate = TX_READY;
            if(TX_Buffer.TXCB)
            {
                TX_Buffer.TXCB();
            }
            ((volatile UART_t * const)UART1)->USART_CR1 &= ~TXEIE;
        }
    }

    if( (((volatile UART_t * const)UART1)->USART_DR & RXNE) )
    {
        if(RX_Buffer.RXbuffer.position < RX_Buffer.RXbuffer.len)
        {
            RX_Buffer.RXbuffer.buffer[RX_Buffer.RXbuffer.position] = ((volatile UART_t * const)UART1)->USART_DR;
            RX_Buffer.RXbuffer.position++;
        }
        else
        {
            RX_Buffer.RXstate = RX_READY;
            ((volatile UART_t * const)UART1)->USART_CR1 &= ~RXNEIE;
            if(RX_Buffer.RXCB)
            {
                RX_Buffer.RXCB();
            }
            
        }
    }
}