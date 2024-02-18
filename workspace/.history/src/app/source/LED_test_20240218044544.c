#include "RCC.h"
#include "SWITCH.h"

int main()
{

    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);
    volatile uint32_t sw1_state = 0;
    uint32_t sw2_state = 0;
    SWITCH_init();

    Get_Switch_State(Switch_1, &sw1_state);
    Get_Switch_State(Switch_2, &sw2_state);    

    return 0;
}