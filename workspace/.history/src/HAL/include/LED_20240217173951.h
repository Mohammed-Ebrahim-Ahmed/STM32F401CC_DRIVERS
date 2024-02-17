#ifndef LED_H_
#define LED_H_

#include <stdint.h>

#define

typedef enum {
    LED_NotOk,
    LED_isOk,
    LED_WrongPort,
    LED_WrongPin,
    LED_WrongConnection,
    LED_WrongState
}LED_errorStatus_t;

typedef struct
{
    volatile void* const Port;
    uint32_t Pin;
    uint8_t Connection;
    uint8_t Default_State;
}
LED_errorStatus_t LED_init()
#endif