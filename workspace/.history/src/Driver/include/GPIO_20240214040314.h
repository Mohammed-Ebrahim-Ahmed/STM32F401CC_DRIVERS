#ifndef GPIO_H_
#define GPIO_H_


#include <stdint.h>

/*********************************************defines****************************************************************/


/********************************************************************************************************************/


/**********************************************types*****************************************************************/
typedef struct{
    uint32_t Pin;
    uint32_t Port;
    uint32_t Speed;
    uint32_t Mode;
}GPIOPin_t;

typedef enum{
    GPIO_isOk,
    GPIO_isNotOk,
    GPIO_WrongPin,
    GPIO_WrongPort,
    GPIO_WrongSpeed,
    GPIO_WrongMode
}GPIOErrorStatus_t;

/********************************************************************************************************************/

/*************************************************APIs***************************************************************/

GPIOErrorStatus_t GPIO_init


/*********************************************************************************************************************/

#endif