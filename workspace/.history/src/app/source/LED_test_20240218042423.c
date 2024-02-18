#include "RCC.h"
#include "SWITCH.h"

int main()
{

    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);
    uinit32_t sw1_state = 0;
    u
    SWITCH_init();


    return 0;
}