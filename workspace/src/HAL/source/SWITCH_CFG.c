#include "SWITCH.h"
#include "GPIO.h"

SWITCH_t SWITCHS [_SWITCH_NO] = {
    [Switch_1] = {
        .Port = GPIO_PORTA,
        .Pin = GPIO_PIN0,
        .Mode = SWITCH_HIGH_CON
    },
    //     [Switch_2] = {
    //     .Port = GPIO_PORTB,
    //     .Pin = GPIO_PIN4,
    //     .Mode = SWITCH_LOW_CON
    // },

};