#include "linslave.h"
#include "GPIO.h"
#include "UART_DRIVER.h"
#include "RCC.h"
#include "NVIC.h"

extern LIN_UART_t LIN_UART;

void LIN_initSlave(void)
{
    uint32_t LOC_AF = 0;
    switch((uint32_t)LIN_UART.TxUart_pin.Port)
    {
        case (uint32_t)GPIO_PORTA:
            RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
            break;
        case (uint32_t)GPIO_PORTB:
            RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
            break;
        case (uint32_t)GPIO_PORTC:
            RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);
            break;   
        default:
            break;
    }

    switch((uint32_t)LIN_UART.RxUart_pin.Port)
    {
        case (uint32_t)GPIO_PORTA:
            RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
            break;
        case (uint32_t)GPIO_PORTB:
            RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
            break;
        case (uint32_t)GPIO_PORTC:
            RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);
            break;   
        default:
            break;
    }

    switch((uint32_t)LIN_UART.UART_NO)
    {
        case (uint32_t)UART1:
            RCC_enableAPBPeriCLK(RCC_APB2_USART1);
            NVIC_EnableIRQ(NVIC_USART1_INTERRUPT);
            LOC_AF = GPIO_AF_7;
            break;
        case (uint32_t)UART2:
            RCC_enableAPBPeriCLK(RCC_APB1_USART2);
            NVIC_EnableIRQ(NVIC_USART2_INTERRUPT);
            LOC_AF = GPIO_AF_7;
            break;
        case (uint32_t)UART6:
            RCC_enableAPBPeriCLK(RCC_APB2_USART6);
            NVIC_EnableIRQ(NVIC_USART6_INTERRUPT);
            LOC_AF = GPIO_AF_8;
            break;
    }

    GPIO_init(&LIN_UART.TxUart_pin);
    GPIO_init(&LIN_UART.RxUart_pin);
    GPIO_SetAlernateFunction(LIN_UART.TxUart_pin.Port, LIN_UART.TxUart_pin.Pin, LOC_AF);
    GPIO_SetAlernateFunction(LIN_UART.RxUart_pin.Port, LIN_UART.RxUart_pin.Pin, LOC_AF);

    UART_init(LIN_UART.UART_NO);
    UART_Config(LIN_UART.UART_NO, LIN_UART.wordLength, LIN_UART.stopBits, LIN_UART.oversampling, LIN_UART.baudrate);    
}

static uint8_t pid_Calc (uint8_t ID)
{
	if (ID > 0x3F) Error_Handler();
	uint8_t IDBuf[6];
	for (int i=0; i<6; i++)
	{
		IDBuf[i] = (ID>>i)&0x01;
	}
	uint8_t P0 = (IDBuf[0]^IDBuf[1]^IDBuf[2]^IDBuf[4])&0x01;
	uint8_t P1 = ~((IDBuf[1]^IDBuf[3]^IDBuf[4]^IDBuf[5])&0x01);
	ID = ID | (P0<<6) | (P1<<7);
	return ID;
}

static uint8_t checksum_Calc (uint8_t PID, uint8_t *data, int size)
{
	uint8_t buffer[size+2];
	uint16_t sum = 0;
	buffer[0] = PID;
	for (int i=0; i<size; i++)
	{
		buffer[i+1] = data[i];
	}

	for (int i=0; i<size+1; i++)
	{
		sum += buffer[i];
		if (sum>0xff) sum = sum-0xFF;
	}

	sum = 0xFF-sum;
	return sum;
}
