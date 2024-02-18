#include "RCC.h"
#include "SWITCH.h"

int main()
{

    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);
    uint32_t sw1_state = 0;
    uint32_t sw2_state = 0;
    SWITCH_init();

    sw1_state = Get_Switch_State()

    return 0;
}