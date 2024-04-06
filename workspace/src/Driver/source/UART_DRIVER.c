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

#define TE 0x08
#define TXE  0x80
#define TC 0x40
#define RXNE 0x20
#define TXEIE 0x80
#define RXNEIE 0x20
#define TCIE 0x40
#define UE 0x2000
#define RE 0x4

#define LBD  0x100
#define SBK  0x001
#define LINEN 0x4000
#define LBDIE 0x40
#define LBDL  0x20

#define MANTISSA_MAX 0xFFF
#define FRACTION_MAX 0xF
#define MANTISSA_SHIFT 4
#define BDR_MASK 0xFFFF
#define STOP_BITS_MASK 0x3000
#define PARITY_ENABLE 0x400

#define UART_1_CB 0
#define UART_2_CB 1
#define UART_6_CB 2
#define NUM_OF_UART 3
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

BrakeCB_t Brake_CB_FN[NUM_OF_UART] = {NULL,NULL,NULL};

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/
UART_errorStatus_t UART_init(volatile void* UART_Bus)
{
    UART_errorStatus_t UART_errorStatus = UART_NotOk;
    if(UART_Bus != UART1 && UART_Bus != UART2 && UART_Bus != UART6)
    {
        UART_errorStatus = UART_WrongBus;
    }
    else
    {
        UART_errorStatus = UART_Ok;
        ((volatile UART_t * const)UART_Bus)->USART_CR1 |= UE;

    }
    return UART_errorStatus;
}
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
            // ((volatile UART_t * const)UART_Bus)->USART_BRR |= 104 << 4;
            ((volatile UART_t * const)UART_Bus)->USART_CR1 |= TCIE;
            ((volatile UART_t * const)UART_Bus)->USART_CR1 |= TE;
            ((volatile UART_t * const)UART_Bus)->USART_DR = TX_Buffer.TXbuffer.buffer[0];
            TX_Buffer.TXbuffer.position++; 
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
            ((volatile UART_t * const)UART_Bus)->USART_CR1 &= ~RXNEIE;
            RX_Buffer.RXstate = RX_BUSY;
            RX_Buffer.RXbuffer.buffer = buffer;
            RX_Buffer.RXbuffer.len = len;
            RX_Buffer.RXbuffer.position = 0;
            RX_Buffer.RXCB = cb;
            ((volatile UART_t * const)UART_Bus)->USART_CR1 |= RXNEIE;
            ((volatile UART_t * const)UART_Bus)->USART_CR1 |= RE;
        }        
    }
    return UART_errorStatus;
}

UART_errorStatus_t UART_EnableDMA(volatile void* UART_Bus, uint8_t RECEIVETRANS)
{
    UART_errorStatus_t UART_errorStatus = UART_NotOk;    
    if(RECEIVETRANS != DMA_RECEIVE  && RECEIVETRANS !=DMA_TRANS)
    {
        UART_errorStatus = UART_WrongDMAConfig;
    }
    else if(UART_Bus != UART1 && UART_Bus != UART2 && UART_Bus != UART6)
    {
        UART_errorStatus = UART_WrongBus;
    }
    else
    {
        UART_errorStatus = UART_Ok;
        if(RECEIVETRANS == DMA_RECEIVE)
        {
            ((volatile UART_t * const)UART_Bus)->USART_CR3 |= DMA_RECEIVE;
        }
        else
        {
            ((volatile UART_t * const)UART_Bus)->USART_CR3 |= DMA_TRANS;
        }

    }
    return UART_errorStatus;
}
UART_errorStatus_t UART_Config(volatile void* UART_Bus, uint8_t WordLength, uint16_t stopbit, uint16_t OverSampling, uint16_t Baudrate)
{
    UART_errorStatus_t UART_errorStatus = UART_NotOk; 
    uint32_t LOC_VAR = 0;
    uint32_t LOC_baud = 0;
	uint32_t TempValue = 0;
	uint16_t TempMantissa = 0;
	uint16_t TempFraction = 0;
    if(UART_Bus != UART1 && UART_Bus != UART2 && UART_Bus != UART6)
    {
        UART_errorStatus = UART_WrongBus;
    }      
    else if(WordLength != WORDLENGTH_8BITS && WordLength != WORDLENGTH_9BITS )
    {
        UART_errorStatus = UART_WrongWordLength;
    }
    else if(stopbit != ONE_STOP_BIT && stopbit != HALF_STOP_BIT && stopbit != TWO_STOP_BIT && stopbit != ONE_HALF_STOP_BIT)
    {
        UART_errorStatus = UART_WrongStopBit;
    }
    else
    {
        UART_errorStatus = UART_Ok;
        ((volatile UART_t * const)UART_Bus)->USART_CR1 |= WordLength;
        ((volatile UART_t * const)UART_Bus)->USART_CR1 |= OverSampling;
        LOC_VAR = ((volatile UART_t * const)UART_Bus)->USART_CR2;
        LOC_VAR &= ~STOP_BITS_MASK;
        LOC_VAR |= stopbit;
        ((volatile UART_t * const)UART_Bus)->USART_CR2 = LOC_VAR;

		TempValue = ((uint64_t)F_CLK * 1000) / (Baudrate * (8 * (2 - OverSampling)));
		TempFraction = (TempValue % 1000) * (8 * (2 - OverSampling));
		TempFraction = TempFraction / 1000;
		if(TempFraction > 0xF)
		{
			TempMantissa += (TempFraction & 0xF0);
		}
		TempMantissa = TempValue / 1000;

        LOC_baud = ((volatile UART_t * const)UART_Bus)->USART_BRR;
        LOC_baud &= ~ BDR_MASK;
        LOC_baud |= TempMantissa << MANTISSA_SHIFT;
        LOC_baud |= TempFraction & 0x0F;
        ((volatile UART_t * const)UART_Bus)->USART_BRR = LOC_baud;

    } 
    return UART_errorStatus;
}

UART_errorStatus_t UART_ControlConfigParity(volatile void* UART_Bus, uint8_t parity)
{
    UART_errorStatus_t UART_errorStatus = UART_NotOk; 
    if(UART_Bus != UART1 && UART_Bus != UART2 && UART_Bus != UART6)
    {
        UART_errorStatus = UART_WrongBus;
    }      
    else if(parity != ODD_PARITY && parity != EVEN_PARITY)
    {
        UART_errorStatus = UART_WrongParity;
    }
    else
    {   
        UART_errorStatus = UART_Ok;
        ((volatile UART_t * const)UART_Bus)->USART_CR1 |= PARITY_ENABLE;
        ((volatile UART_t * const)UART_Bus)->USART_CR1 |= parity;
    }
    return UART_errorStatus;
}

UART_errorStatus_t UART_Config_Generate_Brake(volatile void* UART_Bus, uint8_t BrakeLength)
{
    UART_errorStatus_t UART_errorStatus = UART_NotOk; 
    uint32_t temp = 0;
    if(UART_Bus != UART1 && UART_Bus != UART2 && UART_Bus != UART6)
    {
        UART_errorStatus = UART_WrongBus;
    }
    else if(BrakeLength != BRAKE_10_BIT && BrakeLength != BRAKE_11_BIT)
    {
        UART_errorStatus = UART_WrongBrakeLength;
    }
    else
    {
        UART_errorStatus = UART_Ok;
        ((volatile UART_t * const)UART_Bus)->USART_CR2 |= LINEN;
        temp = ((volatile UART_t * const)UART_Bus)->USART_CR2;
        temp &= ~ LBDL;
        temp |= BrakeLength;
        ((volatile UART_t * const)UART_Bus)->USART_CR2 = temp;
        ((volatile UART_t * const)UART_Bus)->USART_CR2 |= LBDIE;
        ((volatile UART_t * const)UART_Bus)->USART_CR1 |= SBK;


    }
    return UART_errorStatus;
}      
UART_errorStatus_t UART_BrakeCB(volatile void* UART_Bus, BrakeCB_t BrakeCB)
{   
    UART_errorStatus_t UART_errorStatus = UART_NotOk; 
    uint8_t index = 0;
    if (BrakeCB == NULL)
    {
        UART_errorStatus = UART_Nullptr;
    }
    else if(UART_Bus == NULL)
    {
        UART_errorStatus = UART_Nullptr;
    }
    else
    {
        UART_errorStatus = UART_Ok;
        if((uint32_t)UART_Bus == UART1)
        {
            index = UART_1_CB;
        }
        else if((uint32_t)UART_Bus == UART2)
        {
            index = UART_2_CB;
        }
        else
        {
            index = UART_6_CB;
        }
        Brake_CB_FN[index] = BrakeCB;
    }
    return UART_errorStatus;
}
void USART1_IRQHandler (void)
{
    if((((volatile UART_t * const)UART1)->USART_SR & LBD))
    {
        if((Brake_CB_FN[UART_1_CB]) != NULL)
        {
            Brake_CB_FN[UART_1_CB]();
        }
            
    }
    else
    {
        if( (((volatile UART_t * const)UART1)->USART_SR & TC) )
        {
            ((volatile UART_t * const)UART1)->USART_SR &= ~TC ;
            if(TX_Buffer.TXbuffer.position < TX_Buffer.TXbuffer.len)
            {
                ((volatile UART_t * const)UART1)->USART_CR1 |= TE;
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

        if( (((volatile UART_t * const)UART1)->USART_SR & RXNE) )
        {
            if(RX_Buffer.RXbuffer.position < RX_Buffer.RXbuffer.len)
            {
                
                RX_Buffer.RXbuffer.buffer[RX_Buffer.RXbuffer.position] = ((volatile UART_t * const)UART1)->USART_DR;
                RX_Buffer.RXbuffer.position++;
                ((volatile UART_t * const)UART1)->USART_CR1 |= RE;
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

}

void USART2_IRQHandler (void)
{
    if((((volatile UART_t * const)UART2)->USART_SR & LBD))
    {
        if((Brake_CB_FN[UART_2_CB]) != NULL)
        {
            Brake_CB_FN[UART_2_CB]();
        }
    }
    else
    {
        if( (((volatile UART_t * const)UART2)->USART_SR & TC) )
        {
            ((volatile UART_t * const)UART2)->USART_SR &= ~TC ;
            if(TX_Buffer.TXbuffer.position < TX_Buffer.TXbuffer.len)
            {
                ((volatile UART_t * const)UART2)->USART_CR1 |= TE;
                ((volatile UART_t * const)UART2)->USART_DR = TX_Buffer.TXbuffer.buffer[TX_Buffer.TXbuffer.position];
                
                TX_Buffer.TXbuffer.position++;
            }
            else
            {
                TX_Buffer.TXstate = TX_READY;
                if(TX_Buffer.TXCB)
                {
                    TX_Buffer.TXCB();
                }
                ((volatile UART_t * const)UART2)->USART_CR1 &= ~TXEIE;
            }
        }

        if( (((volatile UART_t * const)UART2)->USART_SR & RXNE) )
        {
            if(RX_Buffer.RXbuffer.position < RX_Buffer.RXbuffer.len)
            {
                
                RX_Buffer.RXbuffer.buffer[RX_Buffer.RXbuffer.position] = ((volatile UART_t * const)UART2)->USART_DR;
                RX_Buffer.RXbuffer.position++;
                ((volatile UART_t * const)UART2)->USART_CR1 |= RE;
            }
            else
            {
                RX_Buffer.RXstate = RX_READY;
                ((volatile UART_t * const)UART2)->USART_CR1 &= ~RXNEIE;
                if(RX_Buffer.RXCB)
                {
                    RX_Buffer.RXCB();
                }
                
            }
        }
    }

}

void USART6_IRQHandler (void)
{
    if((((volatile UART_t * const)UART6)->USART_SR & LBD))
    {
        if((Brake_CB_FN[UART_6_CB]) != NULL)
        {
            Brake_CB_FN[UART_6_CB]();
        }
    }
    else
    {
        if( (((volatile UART_t * const)UART6)->USART_SR & TC) )
        {
            ((volatile UART_t * const)UART6)->USART_SR &= ~TC ;
            if(TX_Buffer.TXbuffer.position < TX_Buffer.TXbuffer.len)
            {
                ((volatile UART_t * const)UART6)->USART_CR1 |= TE;
                ((volatile UART_t * const)UART6)->USART_DR = TX_Buffer.TXbuffer.buffer[TX_Buffer.TXbuffer.position];
                
                TX_Buffer.TXbuffer.position++;
            }
            else
            {
                TX_Buffer.TXstate = TX_READY;
                if(TX_Buffer.TXCB)
                {
                    TX_Buffer.TXCB();
                }
                ((volatile UART_t * const)UART6)->USART_CR1 &= ~TXEIE;
            }
        }

        if( (((volatile UART_t * const)UART6)->USART_SR & RXNE) )
        {
            if(RX_Buffer.RXbuffer.position < RX_Buffer.RXbuffer.len)
            {
                
                RX_Buffer.RXbuffer.buffer[RX_Buffer.RXbuffer.position] = ((volatile UART_t * const)UART6)->USART_DR;
                RX_Buffer.RXbuffer.position++;
                ((volatile UART_t * const)UART6)->USART_CR1 |= RE;
            }
            else
            {
                RX_Buffer.RXstate = RX_READY;
                ((volatile UART_t * const)UART6)->USART_CR1 &= ~RXNEIE;
                if(RX_Buffer.RXCB)
                {
                    RX_Buffer.RXCB();
                }
                
            }
        }
    }

}