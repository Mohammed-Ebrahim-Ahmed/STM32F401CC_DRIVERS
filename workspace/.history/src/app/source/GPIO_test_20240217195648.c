#include "RCC.h"
#include "GPIO.h"

int main()
{

    uint32_t status = -1;
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);



    
    return 0;
}