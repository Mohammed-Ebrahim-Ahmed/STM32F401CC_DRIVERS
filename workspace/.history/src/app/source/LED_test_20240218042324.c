#include "RCC.h"
#include "SWITCH.h"

int main()
{

    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);
    LED_init();

    LED_Set_state(greenLed, LED_SET_HIGH);
    LED_Set_state(blueLed, LED_SET_LOW);
    return 0;
}