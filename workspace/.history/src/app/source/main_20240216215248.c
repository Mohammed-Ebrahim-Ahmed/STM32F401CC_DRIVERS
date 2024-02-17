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
    GPIO_Pin_t Pin0 = {
        .Mode = GPIO_OUT_OD,
        .Speed = GPIO_SPEED_HIGH,
        .Port = GPIO_PORTA,
        .Pin = GPIO_PIN0
    };
        GPIO_Pin_t Pin1 = {
        .Mode = GPIO_IN_PU,
        .Speed = GPIO_SPEED_HIGH,
        .Port = GPIO_PORTA,
        .Pin = GPIO_PIN1
    };
    uint32_t status = -1;
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);

    GPIO_init(&Pin0);
    GPIO_init(&Pin1);
    GPIO_SetPinValue(GPIO_PORTA, GPIO_PIN0, GPIO_PIN0);
    GPIO_GetPinValue(GPIO_PORTA, GPIO_PIN1,&status);

    if()
    return 0;
}