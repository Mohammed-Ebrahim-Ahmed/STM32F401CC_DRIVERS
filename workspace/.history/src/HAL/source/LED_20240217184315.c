#include "LED.h"
#include "GPIO.h"

extern LED_t LEDS [_LED_MAX_COUNT];
void LED_init(void)
{
    GPIO_Pin_t* Pin ;
    Pin->Mode = GPIO_OUT_PP;
    Pin->Speed = GPIO

}