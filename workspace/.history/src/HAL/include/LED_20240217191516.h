#ifndef LED_H_
#define LED_H_

#include <stdint.h>

#include "LED_CFG.h"

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
    LED_WrongState<
    
}LED_errorStatus_t;

/**
 * @brief this is struct of configuration for the led
 * 
 */
typedef struct
{
    volatile void* const Port;
    uint32_t Pin;
    uint8_t Connection;
    uint8_t Default_State;
}LED_t;

/**
 * @brief This is the init function for the LED please use LED_CFG.c and LED_CFG.h before using this function
 * 
 */
void LED_init(void);

LED_errorStatus_t LED_Set_state(uint32_t LED, uint32_t state);

#endif