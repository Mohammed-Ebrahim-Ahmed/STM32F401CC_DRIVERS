#include "LED.h"
#include "GPIO.h"

#ifndef NULL
#define NULL (void*)0
#endif

extern LED_t LEDS [_LED_MAX_COUNT];
void LED_init(void)
{
    GPIO_Pin_t* Pin = NULL;
    Pin->Mode = GPIO_OUT_PP;
    Pin->Speed = GPIO_SPEED_LOW;
    int i = 0;


}