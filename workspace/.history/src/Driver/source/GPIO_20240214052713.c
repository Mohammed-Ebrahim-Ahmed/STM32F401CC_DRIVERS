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

volatile GPIO_Peri_t* const GPIO[3] = {GPIO_PORTA, GPIO_PORTB, GPIO_PORTC}; 

/*********************************************************************************************************************************************/

/**************************************************************static_function_prototyes******************************************************/



/*********************************************************************************************************************************************/

/***********************************************************************APIs******************************************************************/
GPIO_ErrorStatus_t GPIO_init(GPIO_Pin_t* GPIO_Pin)
{
    GPIO_ErrorStatus_t LOC_ErrorStatus = GPIO_isNotOk;

    if((GPIO_Pin->Pin != GPIO_PIN0) &&
       (GPIO_Pin->Pin != GPIO_PIN1) && 
       (GPIO_Pin->Pin != GPIO_PIN2) &&
       (GPIO_Pin->Pin != GPIO_PIN3) &&
       (GPIO_Pin->Pin != GPIO_PIN4) &&
       (GPIO_Pin->Pin != GPIO_PIN5) &&
       (GPIO_Pin->Pin != GPIO_PIN6) &&
       (GPIO_Pin->Pin != GPIO_PIN7) &&
       (GPIO_Pin->Pin != GPIO_PIN8) &&
       (GPIO_Pin->Pin != GPIO_PIN9) &&
       (GPIO_Pin->Pin != GPIO_PIN10) &&
       (GPIO_Pin->Pin != GPIO_PIN11) &&
       (GPIO_Pin->Pin != GPIO_PIN12) &&
       (GPIO_Pin->Pin != GPIO_PIN13) && 
       (GPIO_Pin->Pin != GPIO_PIN14) &&
       (GPIO_Pin->Pin != GPIO_PIN15) )
    {
        LOC_ErrorStatus = GPIO_WrongPin;
    }
    else if(GPIO_Pin->Port != GPIO)

}


/*********************************************************************************************************************************************/