#include "SWITCH.h"
#include "GPIO.h"

SWITCH_t SWITCHS [_SWITCH_NO] = {
    [Switch_1] = {
        .Port = GPIO_PORTA,
        .Pin = GPIO_PIN0,
        .Mode = SWITCH_PU
    },
        [Switch_2] = {
        .Port = GPIO_PORTB,
        .Pin = GPIO_PIN4,
        .Mode = SWITCH_PD
    },
        [Switch_3] = {
        .Port = GPIO_PORTB,
        .Pin = GPIO_PIN5,
        .Mode = SWITCH_FLOATING
    }    
}