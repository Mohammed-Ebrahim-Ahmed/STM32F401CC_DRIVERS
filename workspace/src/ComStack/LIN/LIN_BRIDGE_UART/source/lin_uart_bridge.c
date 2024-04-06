#include "lin_uart_bridge.h"
#include "GPIO.h"
#include "UART_DRIVER.h"
#include "RCC.h"
#include "NVIC.h"

#define SYN_BYTE 0x55

#ifndef NULL
#define NULL ((void *)0)
#endif

extern LIN_UART_t LIN_UART;
uint8_t pid = 0;

void SendSYNWITHPID()
{
    uint8_t SYNK [2] = {SYN_BYTE, pid};
    UART_SentBufferZCASYNC(LIN_UART.UART_NO, SYNK, 2, NULL);
}
void LIN_initUART()
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

void LIN_SendBrake()
{
    UART_BrakeCB(LIN_UART.UART_NO, &SendSYNWITHPID);
    UART_Config_Generate_Brake(LIN_UART.UART_NO, BRAKE_11_BIT);
}