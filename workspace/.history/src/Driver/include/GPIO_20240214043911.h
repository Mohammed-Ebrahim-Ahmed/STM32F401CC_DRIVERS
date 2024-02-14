#ifndef GPIO_H_
#define GPIO_H_


#include <stdint.h>

/*********************************************defines****************************************************************/

/**
 * @brief Available ports to select
 * 
 */
*/
#define GPIO_PORTA 0
#define GPIO_PORTB 1
#define GPIO_PORTC 2

/**
 * @brief Available pins to select
 * 
 */
#define GPIO_Pin0   0
#define GPIO_Pin1   1
#define GPIO_Pin2   2
#define GPIO_Pin3   3
#define GPIO_Pin4   4
#define GPIO_Pin5   5
#define GPIO_Pin6   6
#define GPIO_Pin7   7
#define GPIO_Pin8   8
#define GPIO_Pin9   9
#define GPIO_Pin10  10
#define GPIO_Pin11  11
#define GPIO_Pin12  12
#define GPIO_Pin13  13
#define GPIO_Pin14  14
#define GPIO_Pin15  15

/**
 * @brief pin mode select
 * 
 */
#define GPIO_INPUT  0x00
#define GPIO_OUTPUT 0x01
#define GPIO_AF     0x02
#define GPIO_ANALOG 0x03

/**
 * @brief pin output type
 * 
 */
#define GPIO_PP     0x0
#define GPIO_OD     0x1

/**
 * @brief pin output speed
 * 
 */
#define GPIO_LOW        0x00
#define GPIO_MEDIUM     0x01
#define GPIO_HIGH       0x02
#define GPIO_VERYHIGH   0x03

/**
 * @brief pin pull-up/pull-down
 * 
 */
#define GPIO_NOPUPD     0x00
#define GPIO_PU         0x01
#define GPIO_PD         0x02       

/**
 * @brief This is the Value read 
 * 
 */
*/
#define GPIO_PIN_IS_LOW  0x0
#define GPIO_PIN_IS_HIGH 0x1

/**
 * @brief This is the options to output a digital value on pin 
 * 
 */
#define GPIO_SET_PIN_LOW  0x0
#define GPIO_SET_PIN_HIGH 0x1


/********************************************************************************************************************/


/**********************************************types*****************************************************************/
typedef struct{
    uint32_t Pin;
    uint32_t Port;
    uint32_t Speed;
    uint32_t Mode;
}GPIO_Pin_t;

typedef enum{
    GPIO_isOk,
    GPIO_isNotOk,
    GPIO_WrongPin,
    GPIO_WrongPort,
    GPIO_WrongSpeed,
    GPIO_WrongMode
}GPIO_ErrorStatus_t;

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
GPIO_ErrorStatus_t GPIO_GetPinValue(uint32_t GPIO_Port, uint32_t GPIO_Pin);


/*********************************************************************************************************************/

#endif