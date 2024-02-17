/*******************************************************************includes******************************************************************/

#include "GPIO.h"

/*********************************************************************************************************************************************/

/********************************************************************defines******************************************************************/

#define GPIO_MODE_MASK  0x03
#define GPIO_TYPE_MASK  0x1
#define GPIO_SPEED_MASK 0x03
#define GPIO_PUPD_MASK  0x03
#define GPIO_AF_MASK    0xF
#define GPIO_Bit_MASK 0x01
#define GPIO_SHIFT_LOW 0
#define GPIO_SHIFT_HIGH 16
#define BIT_WIDTH_2 2
#define BIT_WIDTH_4 4

/**
 * @brief This the input, output, special function and analog configurations
 * 
 */
#define GPIO_OUT_AF_CONFIG_MASK        0x7
#define GPIO_IN_CONFIG_MASK            0x3
#define GPIO_ANALOG_CONFIG_MASK        0x3

/*
#define GPIO_PORTA ((volatile GPIO_Peri_t* const) 0x40020000)
#define GPIO_PORTB ((volatile GPIO_Peri_t* const) 0x40020400)
#define GPIO_PORTC ((volatile GPIO_Peri_t* const) 0x40020800)
*/

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

//volatile GPIO_Peri_t* const GPIO[3] = {GPIO_PORTA, GPIO_PORTB, GPIO_PORTC}; 

/*********************************************************************************************************************************************/

/**************************************************************static_function_prototyes******************************************************/



/*********************************************************************************************************************************************/

/***********************************************************************APIs******************************************************************/
GPIO_ErrorStatus_t GPIO_init(GPIO_Pin_t* GPIO_Pin)
{
    uint32_t LOC_Mode = 0;
    uint32_t LOC_Speed = 0;
    uint32_t LOC_Type = 0;
    uint32_t LOC_Mode_MODER = 0;
    uint32_t LOC_Mode_OTYPER = 0;
    uint32_t LOC_Mode_PUPD

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
    else if((((volatile uint32_t* const)GPIO_Pin->Port) != GPIO_PORTA) &&
            (((volatile uint32_t* const)GPIO_Pin->Port) != GPIO_PORTB) &&
            (((volatile uint32_t* const)GPIO_Pin->Port) != GPIO_PORTC) )
    {
        LOC_ErrorStatus = GPIO_WrongPort;
    }
    else if((GPIO_Pin->Mode != GPIO_OUT_PP)      &&
            (GPIO_Pin->Mode != GPIO_OUT_PP_PU)   &&
            (GPIO_Pin->Mode != GPIO_OUT_PP_PD)   &&
            (GPIO_Pin->Mode != GPIO_OUT_OD)      &&
            (GPIO_Pin->Mode != GPIO_OUT_OD_PU)   &&
            (GPIO_Pin->Mode != GPIO_OUT_OD_PD)   &&
            (GPIO_Pin->Mode != GPIO_AF_PP)       &&
            (GPIO_Pin->Mode != GPIO_AF_PP_PU)    &&
            (GPIO_Pin->Mode != GPIO_AF_PP_PD)    &&
            (GPIO_Pin->Mode != GPIO_AF_OD)       &&
            (GPIO_Pin->Mode != GPIO_AF_OD_PU)    &&
            (GPIO_Pin->Mode != GPIO_AF_OD_PD)    &&
            (GPIO_Pin->Mode != GPIO_IN_Float)    &&
            (GPIO_Pin->Mode != GPIO_IN_PU)       &&
            (GPIO_Pin->Mode != GPIO_IN_PD)       &&
            (GPIO_Pin->Mode != GPIO_IN_OUT_ANALOG))

    {
        LOC_ErrorStatus = GPIO_WrongMode;
    }
    else if((GPIO_Pin->Speed != GPIO_SPEED_LOW)      &&
            (GPIO_Pin->Speed != GPIO_SPEED_MEDIUM)   &&
            (GPIO_Pin->Speed != GPIO_SPEED_HIGH)     &&
            (GPIO_Pin->Speed != GPIO_SPEED_VERYHIGH)  )
    {
        LOC_ErrorStatus = GPIO_WrongSpeed;
    }
    else
    {
        LOC_ErrorStatus = GPIO_isOk;

        LOC_Mode =  ((volatile GPIO_Peri_t* const)(GPIO_Pin->Port))->GPIO_MODER;
        LOC_Speed = ((volatile GPIO_Peri_t* const)(GPIO_Pin->Port))->GPIO_OSPEEDR;
        LOC_Type =  ((volatile GPIO_Peri_t* const)(GPIO_Pin->Port))->GPIO_OTYPER;

        LOC_Mode  &= ~(GPIO_MODE_MASK << ((GPIO_Pin->Pin * BIT_WIDTH_2)));
        LOC_Speed &= ~(GPIO_SPEED_MASK << ((GPIO_Pin->Pin * BIT_WIDTH_2)));
        LOC_Type  &= ~(GPIO_TYPE_MASK << (GPIO_Pin->Pin ));

        LOC_Mode  |= ((GPIO_Pin->Mode) << ((GPIO_Pin->Pin * BIT_WIDTH_2)));
        LOC_Speed |= ((GPIO_Pin->Speed) << ((GPIO_Pin->Pin * BIT_WIDTH_2)));
        LOC_Type  |= ((GPIO_Pin->Type) << (GPIO_Pin->Pin ));   

        ((volatile GPIO_Peri_t* const)(GPIO_Pin->Port))->GPIO_MODER = LOC_Mode;
        ((volatile GPIO_Peri_t* const)(GPIO_Pin->Port))->GPIO_OSPEEDR = LOC_Speed;
        ((volatile GPIO_Peri_t* const)(GPIO_Pin->Port))->GPIO_OTYPER = LOC_Type;        

    }
    return LOC_ErrorStatus;
}

GPIO_ErrorStatus_t GPIO_SetPinValue(uint32_t GPIO_Port, uint32_t GPIO_Pin, uint32_t GPIO_Val_Set)
{
    GPIO_ErrorStatus_t LOC_ErrorStatus = GPIO_isNotOk;

    if((GPIO_Pin != GPIO_PIN0) &&
       (GPIO_Pin != GPIO_PIN1) && 
       (GPIO_Pin != GPIO_PIN2) &&
       (GPIO_Pin != GPIO_PIN3) &&
       (GPIO_Pin != GPIO_PIN4) &&
       (GPIO_Pin != GPIO_PIN5) &&
       (GPIO_Pin != GPIO_PIN6) &&
       (GPIO_Pin != GPIO_PIN7) &&
       (GPIO_Pin != GPIO_PIN8) &&
       (GPIO_Pin != GPIO_PIN9) &&
       (GPIO_Pin != GPIO_PIN10) &&
       (GPIO_Pin != GPIO_PIN11) &&
       (GPIO_Pin != GPIO_PIN12) &&
       (GPIO_Pin != GPIO_PIN13) && 
       (GPIO_Pin != GPIO_PIN14) &&
       (GPIO_Pin != GPIO_PIN15) )
    {
        LOC_ErrorStatus = GPIO_WrongPin;
    }
    else if((((volatile uint32_t* const)GPIO_Port) != GPIO_PORTA) &&
            (((volatile uint32_t* const)GPIO_Port) != GPIO_PORTB) &&
            (((volatile uint32_t* const)GPIO_Port) != GPIO_PORTC) )
    {
        LOC_ErrorStatus = GPIO_WrongPort;
    }
    else if((GPIO_Val_Set != GPIO_SET_PIN_LOW) &&
            (GPIO_Val_Set != GPIO_SET_PIN_HIGH) )
    {
        LOC_ErrorStatus = GPIO_WrongSetValue;
    }
    else
    {
        LOC_ErrorStatus = GPIO_isOk;

        if(GPIO_Val_Set == GPIO_SET_PIN_LOW)
        {
            ((volatile GPIO_Peri_t* const)(GPIO_Port))->GPIO_BSRR |= (GPIO_Bit_MASK << GPIO_Pin << GPIO_SHIFT_HIGH);
        }
        else
        {
            ((volatile GPIO_Peri_t* const)(GPIO_Port))->GPIO_BSRR |= (GPIO_Bit_MASK << GPIO_Pin << GPIO_SHIFT_LOW);
        }
    }
    return LOC_ErrorStatus;
}

GPIO_ErrorStatus_t GPIO_GetPinValue(uint32_t GPIO_Port, uint32_t GPIO_Pin, uint32_t* GPIO_Status)
{
    GPIO_ErrorStatus_t LOC_ErrorStatus = GPIO_isNotOk;

    if((GPIO_Pin != GPIO_PIN0) &&
       (GPIO_Pin != GPIO_PIN1) && 
       (GPIO_Pin != GPIO_PIN2) &&
       (GPIO_Pin != GPIO_PIN3) &&
       (GPIO_Pin != GPIO_PIN4) &&
       (GPIO_Pin != GPIO_PIN5) &&
       (GPIO_Pin != GPIO_PIN6) &&
       (GPIO_Pin != GPIO_PIN7) &&
       (GPIO_Pin != GPIO_PIN8) &&
       (GPIO_Pin != GPIO_PIN9) &&
       (GPIO_Pin != GPIO_PIN10) &&
       (GPIO_Pin != GPIO_PIN11) &&
       (GPIO_Pin != GPIO_PIN12) &&
       (GPIO_Pin != GPIO_PIN13) && 
       (GPIO_Pin != GPIO_PIN14) &&
       (GPIO_Pin != GPIO_PIN15) )
    {
        LOC_ErrorStatus = GPIO_WrongPin;
    }
    else if((((volatile uint32_t* const)GPIO_Port) != GPIO_PORTA) &&
            (((volatile uint32_t* const)GPIO_Port) != GPIO_PORTB) &&
            (((volatile uint32_t* const)GPIO_Port) != GPIO_PORTC) )
    {
        LOC_ErrorStatus = GPIO_WrongPort;
    }
    else
    {
        *GPIO_Status = ((((volatile GPIO_Peri_t* const)(GPIO_Port))->GPIO_IDR >> GPIO_Pin) & GPIO_Bit_MASK);
    }
    return LOC_ErrorStatus;
}
/*********************************************************************************************************************************************/