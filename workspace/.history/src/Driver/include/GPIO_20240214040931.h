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
 * @param GPIO_Pin This pointer to struct which the user pass to the function
 * @return GPIO_ErrorStatus_t : Error status
 */
GPIO_ErrorStatus_t GPIO_init(GPIO_Pin_t* GPIO_Pin);

/**
 * @brief This function set the pin value value which the user has init
 * 
 * @param GPIO_Port : the sele
 * @param GPIO_Pin 
 * @param GPIO_Val_Set 
 * @return GPIO_ErrorStatus_t 
 */
GPIO_ErrorStatus_t GPIO_SetPinValue(uint32_t GPIO_Port, uint32_t GPIO_Pin, uint32_t GPIO_Val_Set);

GPIO_ErrorStatus_t GPIO_GetPinValue(uint32_t GPIO_Port, uint32_t GPIO_Pin);


/*********************************************************************************************************************/

#endif