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
    
}

/********************************************************************************************************************/

/*************************************************APIs***************************************************************/



/*********************************************************************************************************************/

#endif