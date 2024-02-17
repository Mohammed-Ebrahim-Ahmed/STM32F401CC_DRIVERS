#include "RCC.h"
#include "LED.h"

int main()
{

    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);
    void LED_init(void);

    LED_errorStatus_t LED_Set_state(uint32_t LED, uint32_t state);
    return 0;
}