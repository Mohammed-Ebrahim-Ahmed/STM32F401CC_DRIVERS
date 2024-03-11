#include "LED.h"
#include "GPIO.h"

const LED_t LEDS [_LED_COUNT] = {
    [greenLed]={
        .Port = GPIO_PORTA,
        .Pin = GPIO_PIN1,
        .Connection = LED_FORWARD,
        .Default_State = LED_SET_LOW
    },
    [blueLed] ={
        .Port = GPIO_PORTB,
        .Pin = GPIO_PIN0,
        .Connection = LED_REVERSE,
        .Default_State = LED_SET_HIGH
    }
};