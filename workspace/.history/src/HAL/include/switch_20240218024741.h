#ifndef SWITCH_H_
#define SWITCH_H_

#include <stdint.h>
#include "SWITCH_CFG.h"

#define SWITCH_FLOATING 0x00
#define SWITCH_PU       0x01
#define SWITCH_PD       0x02

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
 * @brief 
 * 
 * @param SWITCH 
 * @param state 
 * @return SWITCH_errorStatus_t 
 */
SWITCH_errorStatus_t Get_Switch_State(volatile void* SWITCH, uint32_t* state);

#endif