
#include "scheduler.h"
#include "UART_DRIVER.h"
#include "RCC.h"
#include "NVIC.h"
#include "GPIO.h"
#include "DMA_Driver.h"
#include "LCD_HAL.h"

volatile uint8_t buffer2 [5] = {0};
void Dummy(void);
int main()
{   //static int x = 0;
//     GPIO_Pin_t TxUart_pin ;
//     TxUart_pin.Mode = GPIO_AF_PP;
//     TxUart_pin.Port = GPIO_PORTB;
//     TxUart_pin.Pin = GPIO_PIN6;
//     TxUart_pin.Speed = GPIO_SPEED_HIGH;
//     RCC_enableAPBPeriCLK(RCC_APB2_USART1);
//     RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
//     GPIO_SetAlernateFunction(GPIO_PORTB, GPIO_PIN6, GPIO_AF_7);
//     GPIO_init(&TxUart_pin);
//     GPIO_Pin_t RxUart_pin ;
//     RxUart_pin.Mode = GPIO_AF_PP;
//     RxUart_pin.Port = GPIO_PORTB;
//     RxUart_pin.Pin = GPIO_PIN7;
//     RxUart_pin.Speed = GPIO_SPEED_HIGH;
//     GPIO_init(&RxUart_pin);
//     GPIO_SetAlernateFunction(GPIO_PORTB, GPIO_PIN7, GPIO_AF_7);   
    LCD_GPIO_init();
    SCH_init();
    SCH_Start();
    // uint8_t buffer [10] = {'1','2','3','4','5','6','7','8','9','a'};
    
    // NVIC_EnableIRQ(NVIC_USART1_INTERRUPT);
    // UART_init(UART1);
    // UART_Config(UART1, WORDLENGTH_8BITS, ONE_STOP_BIT, OVERSAMPLING_16, 9600);
    // UART_SentBufferZCASYNC(UART1, buffer, 10, &Dummy );
    // UART_RecieveBufferZCASYNC(UART1, buffer2, 5, &Dummy);
    // while(1)
    // {
    //     x++ ;
    // }
}

void Dummy(void)
{
    volatile uint8_t x = 0;
    x++;
}   