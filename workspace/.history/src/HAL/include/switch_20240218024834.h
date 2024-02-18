#ifndef SWITCH_H_
#define SWITCH_H_

#include <stdint.h>
#include "SWITCH_CFG.h"
/**
 * @brief this is the connection type of the switch
 * 
 */
#define SWITCH_FLOATING 0x00
#define SWITCH_PU       0x01
#define SWITCH_PD       0x02

/**
 * @brief this is struct of configuration 
 * 
 */
typedef struct
{
    volatile void* Port;
    uint32_t Pin;
    uint32_t Mode;
} SWITCH_t;

typedef enum
{
    SWITCH_WrongSwitch,
    SWITCH_isOk,
    SWITCH_NotOk
} SWITCH_errorStatus_t;
/**
 * @brief This function init the switch configured in SWICH_CFG.c
 * 
 */
void SWITCH_init(void);

/**
 * @brief This function return the state of the led (pressed or not)
 * 
 * @param SWITCH : input the switch you want to test
 * @param state : define a variable of this type and pass it by address to this function to return the switch state
 * @return SWITCH_errorStatus_t : the error status for this function
 */
SWITCH_errorStatus_t Get_Switch_State(volatile void* SWITCH, uint32_t* state);

#endif