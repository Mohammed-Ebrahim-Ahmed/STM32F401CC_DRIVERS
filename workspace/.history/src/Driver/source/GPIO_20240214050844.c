/*******************************************************************includes******************************************************************/

#include "GPIO.h"

/*********************************************************************************************************************************************/

/********************************************************************defines******************************************************************/

#define GPIO_MODE_MASK  0x03
#define GPIO_TYPE_MASK  0x1
#define GPIO_SPEED_MASK 0x03
#define GPIO_PUPD_MASK  0x03
#define GPIO_AF_MASK    0xF

/*********************************************************************************************************************************************/\

/*********************************************************************types*******************************************************************/
typedef struct{
    uint32_t GPIO_MODER;
    uint32_t GPIO_OTYPER;
    uint32_t GPIO_OSPEEDR;
    uint32_t GPIO_PUPDR;
    uint32_t GPIO_IDR;
    uint32_t GPIO_ODR;
    uint32_t GPIO_BSRR;
    uint32_t GPIO_LCKR;
    uint32_t GPIO_AFRL;
    
}


/*********************************************************************************************************************************************/

/********************************************************************variables****************************************************************/



/*********************************************************************************************************************************************/

/**************************************************************static_function_prototyes******************************************************/



/*********************************************************************************************************************************************/

/***********************************************************************APIs******************************************************************/



/*********************************************************************************************************************************************/