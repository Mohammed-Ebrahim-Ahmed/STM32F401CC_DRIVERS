#ifndef LED_H_
#define LED_H_

#include <stdint.h>

/**
 * @brief Choose between these state to set the led and the default set for it too.
 * 
 */
#define LED_SET_LOW 0
#define LED_SET_HIGH 1

/**
 * @brief choose between the physical hardware connection for the led
 * 
 */
#define LED_FORWARD 0
#define LED_REVERSE 1

/**
 * @brief This is the error status from the function please check if it ok before continue
 * 
 */
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