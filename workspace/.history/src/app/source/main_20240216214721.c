#include "RCC.h"
#include "GPIO.h"

int main()
{
    // volatile uint32_t sysClk = -1;
    // volatile uint32_t indicator = 0;
    // RCC_enableClock(RCC_CLKENABLEHSE);
    // RCC_selectSYSCLK(RCC_SYSCLK_HSE);
    // RCC_selectSYSCLK(RCC_SYSCLK_HSI);
    // RCC_selectPLLCLK(RCC_PLL_CLKSOURCEHSE);
    // RCC_configurePLLCLK( 8, 336, 8, 14);
    // RCC_selectSYSCLK(RCC_SYSCLK_PLL);

    // sysClk=RCC_getSYSCLK();

    // switch(sysClk)
    // {
    //     case -1:
    //         indicator = 1;
    //         break;
    //     case RCC_SYSCLKRETURN_HSI:
    //         indicator = RCC_SYSCLKRETURN_HSI;
    //         break;
    //     case RCC_SYSCLKRETURN_HSE:
    //         indicator = RCC_SYSCLKRETURN_HSE;
    //         break;
    //     case RCC_SYSCLKRETURN_PLL:
    //         indicator = RCC_SYSCLKRETURN_PLL;
    //         break;
    //     default:
    //         break;
    // }
    GPIO_Pin_t Pin = {
        .Mode = GPIO_OUT_OD,
        .Speed = GPIO_SPEED_HIGH,
        .Port = GPIO_PORTA,
        .Pin = GPIO_PIN0
    };
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);

    GPIO_init(&Pin);
    GPIO_SetPinValue(uint32_t GPIO_Port, uint32_t GPIO_Pin, uint32_t GPIO_Val_Set);
    return 0;
}