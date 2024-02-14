/*******************************************************************includes******************************************************************/

#include "GPIO.h"

/*********************************************************************************************************************************************/

/********************************************************************defines******************************************************************/

#define GPIO_MODE_MASK  0x03
#define GPIO_TYPE_MASK  0x1
#define GPIO_SPEED_MASK 0x03
#define GPIO_PUPD_MASK  0x03
#define GPIO_AF_MASK    0xF

#define GPIO_PORTA ((volatile GPIO_Peri_t* const) 0x40020000)
#define GPIO_PORTB ((volatile GPIO_Peri_t* const) 0x40020400)
#define GPIO_PORTC ((volatile GPIO_Peri_t* const) 0x40020800)

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
    uint32_t GPIO_AFRH;
} GPIO_Peri_t;





/*********************************************************************************************************************************************/

/********************************************************************variables****************************************************************/

volatile GPIO_Peri_t*const GPIO[3] = 

/*********************************************************************************************************************************************/

/**************************************************************static_function_prototyes******************************************************/



/*********************************************************************************************************************************************/

/***********************************************************************APIs******************************************************************/



/*********************************************************************************************************************************************/