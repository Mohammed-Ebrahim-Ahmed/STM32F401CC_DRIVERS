#include <NVIC.h>
#include <RCC.h>

volatile uint32_t x = 5;

int main()
{
    uint32_t PendingState = 0;
    RCC_enableAPBPeriCLK(RCC_APB1_I2C3);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    NVIC_EnableIRQ(NVIC_I2C3_EV_INTERRUPT);
    NVIC_SetPendingIRQ(NVIC_I2C3_EV_INTERRUPT);
    NVIC_GetPendingIRQ(NVIC_I2C3_EV_INTERRUPT, &PendingState);
    NVIC_SetPriorityGrouping(PRIORITY_4_LEVELS); 
    NVIC_SetPriority (NVIC_I2C3_EV_INTERRUPT, GROUP_3, SUBGROUP_2);
    while(1)
    {
        
    }


}

void I2C3_EV_IRQHandler(void)
{
    volatile uint32_t PendingState = 0;
    NVIC_GetPendingIRQ(NVIC_I2C3_EV_INTERRUPT, (uint32_t*)&PendingState);
    x++;
}