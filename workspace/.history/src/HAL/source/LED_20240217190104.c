#include "LED.h"
#include "GPIO.h"

extern const LED_t LEDS [_LED_COUNT];
void LED_init(void)
{
    GPIO_Pin_t Pin ;
    Pin.Mode = GPIO_OUT_PP;
    Pin.Speed = GPIO_SPEED_LOW;
    int i = 0;

    for(i = 0; i <_LED_COUNT; i++)
    {
        Pin.Port = LEDS[i].Port;
        Pin.Pin =  LEDS[i].Pin;
        GPIO_init(&)
    }


}