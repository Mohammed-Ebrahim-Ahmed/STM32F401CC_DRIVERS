#include "LED.h"
#include "GPIO.h"

LED_t LEDS [_LED_MAX_COUNT] = {
    [greenLed]={
        .Port = GPIO_PORTA,
        .Pin = GPIO_PIN1,
        .Connection = LED_FORWARD
    },
    [blueLed] ={
        .Port = GPIO_Por
    }
};