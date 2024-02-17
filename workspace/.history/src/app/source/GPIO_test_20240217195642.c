#include "RCC.h"
#include "GPIO.h"

int main()
{

    GPIO_Pin_t Pin0 = {
        .Mode = GPIO_OUT_PP,
        .Speed = GPIO_SPEED_HIGH,
        .Port = GPIO_PORTA,
        .Pin = GPIO_PIN0
    };
        GPIO_Pin_t Pin1 = {
        .Mode = GPIO_IN_PD,
        .Speed = GPIO_SPEED_HIGH,
        .Port = GPIO_PORTA,
        .Pin = GPIO_PIN1
    };
    uint32_t status = -1;
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
    RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);



    
    return 0;
}