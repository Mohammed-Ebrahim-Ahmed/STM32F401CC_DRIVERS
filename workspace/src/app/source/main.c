
#include "scheduler.h"
#include "UART_DRIVER.h"
#include "RCC.h"
#include "NVIC.h"
#include "GPIO.h"

void Dummy(void);
int main()
{   static int x = 0;
    GPIO_Pin_t Uart_pin ;
    Uart_pin.Mode = GPIO_OUT_PP;
    Uart_pin.Port = GPIO_PORTB;
    Uart_pin.Pin = GPIO_PIN6;
    Uart_pin.Speed = GPIO_SPEED_MEDIUM;
    RCC_enableAPBPeriCLK(RCC_AHB1_GPIOB);
    GPIO_init(&Uart_pin);
    GPIO_SetAlernateFunction(GPIO_PORTB, GPIO_PIN6, GPIO_AF_7);
    // SCH_init();
    // SCH_Start();
    uint8_t buffer [10] = {'1','2','3','4','5','6','7','8','9','a'};
    RCC_enableAPBPeriCLK(RCC_APB2_USART1);
    NVIC_EnableIRQ(NVIC_USART1_INTERRUPT);

    UART_SentBufferZCASYNC(UART1, buffer, 10, &Dummy );
    while(1)
    {
        x++ ;
    }
}

void Dummy(void)
{
    volatile uint8_t x = 0;
    x++;
}   