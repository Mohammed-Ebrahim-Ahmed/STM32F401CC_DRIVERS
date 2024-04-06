#include "linmaster.h"
#include "GPIO.h"
#include "UART_DRIVER.h"
#include "RCC.h"
#include "NVIC.h"

#define SYN_BYTE 0x55

#ifndef NULL
#define NULL ((void *)0)
#endif

#define IDLE 0
#define SENDING_HEADER 1
#define SENDING_LAST_HEADER 2

extern LIN_UART_t LIN_UART;
extern schedTableEntry primary_sched_table[NUM_OF_MESSAGES];
uint8_t pid = 0;

void SendSYNWITHPID(void)
{
    uint8_t SYNK [2] = {SYN_BYTE, pid};
    UART_SentBufferZCASYNC(LIN_UART.UART_NO, SYNK, 2, NULL);
}
void LIN_initMaster(void)
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

static void LIN_SendHeader(void)
{
    UART_BrakeCB(LIN_UART.UART_NO, &SendSYNWITHPID);
    UART_Config_Generate_Brake(LIN_UART.UART_NO, BRAKE_11_BIT);
}

void LIN_MasterTask(void)
{
    static uint8_t time = 0;
    static uint8_t i = 0;
    static uint8_t state = SENDING_HEADER;

    time++;

    switch(state)
    {
        case SENDING_HEADER:
            pid = primary_sched_table[i].m->pid;
            LIN_SendHeader();    
            
            if(time == 1)
            {
                state = IDLE;
            }
            break;
        case IDLE:

            if(time == primary_sched_table[NUM_OF_MESSAGES-1].slotMS)
            {             
                i = 0;
                time = 0;
                state = SENDING_HEADER;
            }
            else if(time == primary_sched_table[i].slotMS)
            {
                i++;
                time = 0;
                state = SENDING_HEADER;          
            }
            else
            {

            }
            break;
        default:
            break;
    }


}