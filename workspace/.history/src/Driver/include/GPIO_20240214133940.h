#ifndef GPIO_H_
#define GPIO_H_


#include <stdint.h>

/*********************************************defines****************************************************************/

/**
 * @brief Available ports to select
 * 
 */
#define GPIO_PORTA_SEL 0
#define GPIO_PORTB_SEL 1
#define GPIO_PORTC_SEL 2

/**
 * @brief Available pins to select
 * 
 */
#define GPIO_PIN0   0x0
#define GPIO_PIN1   0x1
#define GPIO_PIN2   0x2
#define GPIO_PIN3   0x3
#define GPIO_PIN4   0x4
#define GPIO_PIN5   0x5
#define GPIO_PIN6   0x6
#define GPIO_PIN7   0x7
#define GPIO_PIN8   0x8
#define GPIO_PIN9   0x9
#define GPIO_PIN10  0xA
#define GPIO_PIN11  0xB
#define GPIO_PIN12  0xC
#define GPIO_PIN13  0xD
#define GPIO_PIN14  0xE
#define GPIO_PIN15  0xF

/**
 * @brief pin mode select
 * 
 */
#define GPIO_MODE_INPUT  0x00
#define GPIO_MODE_OUTPUT 0x01
#define GPIO_MODE_AF     0x02
#define GPIO_MODE_ANALOG 0x03

/**
 * @brief pin output type
 * 
 */
#define GPIO_TYPE_PP     0x0
#define GPIO_TYPE_OD     0x1

/**
 * @brief pin output speed
 * 
 */
#define GPIO_SPEED_LOW        0x00
#define GPIO_SPEED_MEDIUM     0x01
#define GPIO_SPEED_HIGH       0x02
#define GPIO_SPEED_VERYHIGH   0x03

/**
 * @brief pin pull-up/pull-down
 * 
 */
#define GPIO_PUPD_NOPUPD     0x00
#define GPIO_PUPD_PU         0x01
#define GPIO_PUPD_PD         0x02       

/**
 * @brief This is the state read from the pin
 * 
 */
#define GPIO_PIN_IS_LOW  0x0
#define GPIO_PIN_IS_HIGH 0x1

/**
 * @brief This is the options to output a digital value on pin 
 * 
 */
#define GPIO_SET_PIN_LOW  0x0
#define GPIO_SET_PIN_HIGH 0x1

/**
 * @brief This special function to the pin which could be configured
 * AF0 (system)
 * AF1 (TIM1/TIM2)
 * AF2 (TIM3..5)
 * AF3 (TIM9..11)
 * AF4 (I2C1..3)
 * AF5 (SPI1..4)
 * AF6 (SPI3)
 * AF7 (USART1..2)
 * AF8 (USART6)
 * AF9 (I2C2..3)
 * AF10 (OTG_FS)
 * AF11
 * AF12 (SDIO)
 * AF13 
 * AF14 
 * AF15 (EVENTOUT)
 */
#define GPIO_AF_0  0x0
#define GPIO_AF_1  0x1
#define GPIO_AF_2  0x2
#define GPIO_AF_3  0x3
#define GPIO_AF_4  0x4
#define GPIO_AF_5  0x5
#define GPIO_AF_6  0x6
#define GPIO_AF_7  0x7
#define GPIO_AF_8  0x8
#define GPIO_AF_9  0x9
#define GPIO_AF_10 0xA
#define GPIO_AF_11 0xB
#define GPIO_AF_12 0xC
#define GPIO_AF_13 0xD
#define GPIO_AF_14 0xE
#define GPIO_AF_15 0xF

#define GPIO_OUT_PP     0x0
#define GPIO_OUT_PP_PU  0x1
#define GPIO_OUT_PP_PD  0x2
#define GPIO_OUT_OD     0x4
#define GPIO_OUT_OD_PU  0x5
#define GPIO_OUT_OD_PD  0x6
#define GPIO_AF_PP      0x0
#define GPIO_AF_PP_PU   0x1
#define GPIO_AF_PP_PD   0x2
#define GPIO_AF_P
/********************************************************************************************************************/


/**********************************************types*****************************************************************/
typedef struct{
    uint32_t Pin;
    uint32_t Port;
    uint32_t Speed;
    uint32_t Mode;
    uint32_t Type;

} GPIO_Pin_t;

typedef enum{
    GPIO_isOk,
    GPIO_isNotOk,
    GPIO_WrongPin,
    GPIO_WrongPort,
    GPIO_WrongSpeed,
    GPIO_WrongMode,
    GPIO_WrongType,
    GPIO_WrongSetValue,
    GPIO_WrongGetValue
} GPIO_ErrorStatus_t;

/********************************************************************************************************************/

/*************************************************APIs***************************************************************/

/**
 * @brief This function init the pin configuration
 * 
 * @param GPIO_Pin : This pointer to struct which the user pass to the function
 * @return GPIO_ErrorStatus_t : Error status
 */
GPIO_ErrorStatus_t GPIO_init(GPIO_Pin_t* GPIO_Pin);

/**
 * @brief This function set the pin value value which the user has init
 * 
 * @param GPIO_Port : The Port which the pin is related to
 * @param GPIO_Pin : the pin you want to set its value
 * @param GPIO_Val_Set : the value that you want on the pin
 * @return GPIO_ErrorStatus_t : Error status
 */
GPIO_ErrorStatus_t GPIO_SetPinValue(uint32_t GPIO_Port, uint32_t GPIO_Pin, uint32_t GPIO_Val_Set);

/**
 * @brief This function get the actual value on the pin
 * 
 * @param GPIO_Port : The Port which the pin is related to 
 * @param GPIO_Pin : the pin you want to get its value
 * @return GPIO_ErrorStatus_t : Error status
 */
GPIO_ErrorStatus_t GPIO_GetPinValue(uint32_t GPIO_Port, uint32_t GPIO_Pin, uint32_t* GPIO_Status);


/*********************************************************************************************************************/

#endif