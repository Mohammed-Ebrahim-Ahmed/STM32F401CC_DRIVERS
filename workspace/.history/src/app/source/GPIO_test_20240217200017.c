#include "RCC.h"
#include "LED.h"

int main()
{

    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);
    LED_init();

    LED_Set_state(greenLed, set);
    return 0;
}