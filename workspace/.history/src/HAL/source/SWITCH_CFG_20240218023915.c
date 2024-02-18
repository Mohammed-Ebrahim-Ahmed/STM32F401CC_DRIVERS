#include "SWITCH.h"
#include "GPIO.h"

SWITCH_t SWITCHS [_SWITCH_NO] = {
    [Switch_1] = {
        .Port = GPIO_PORTA,
        .Pin = GPIO_P
    },
        [Switch_2] = {
        .Port = GPIO_PORTB,
        .Pin = GPIO_PIN4,
        .Mode = SWITCH_PD
    }
}