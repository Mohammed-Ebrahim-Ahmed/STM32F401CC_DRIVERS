#include "RCC.h"

int main()
{
    volatile uint32_t sysClk = -1;
    volatile uint32_t indicator = 0;
    RCC_enableClock(RCC_CLKENABLEHSE);
    RCC_selectSYSCLK(RCC_SYSCLK_HSE);
    RCC_selectSYSCLK(RCC_SYSCLK_HSI);
    RCC_selectPLLCLK(RCC_PLL_CLKSOURCEHSE);
    RCC_configurePLLCLK( 4, 192, 4, 14);
    RCC_enableClock(RCC_CLKENABLEPLL);
    RCC_selectSYSCLK(RCC_SYSCLK_PLL);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);
    sysClk=RCC_getSYSCLK();

    switch(sysClk)
    {
        case -1:
            indicator = 1;
            break;
        case RCC_SYSCLKRETURN_HSI:
            indicator = RCC_SYSCLKRETURN_HSI;
            break;
        case RCC_SYSCLKRETURN_HSE:
            indicator = RCC_SYSCLKRETURN_HSE;
            break;
        case RCC_SYSCLKRETURN_PLL:
            indicator = RCC_SYSCLKRETURN_PLL;
            break;
        default:
            break;
    }

    return 0;
}