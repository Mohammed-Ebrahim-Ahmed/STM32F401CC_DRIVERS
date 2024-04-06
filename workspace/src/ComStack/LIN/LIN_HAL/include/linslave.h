#ifndef COMSTACK_LIN_LIN_HAL_INCLUDE_LINSLAVE_H_
#define COMSTACK_LIN_LIN_HAL_INCLUDE_LINSLAVE_H_
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include <stdint.h>
#include "GPIO.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define SENDER 0
#define RECEIVER 1
#define NUM_OF_MESSAGES
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct {
    GPIO_Pin_t TxUart_pin ;
    GPIO_Pin_t RxUart_pin ;
    volatile void *  UART_NO;
    uint8_t wordLength;
    uint16_t stopBits;
    uint16_t oversampling;
    uint16_t baudrate;
}LIN_UART_t;

typedef struct message_t message_t;

typedef struct {
    uint8_t idx;
    uint8_t len;
    message_t* mes;
}signal_t;

typedef struct{
    uint8_t id;
    uint8_t data[8];
    uint8_t data_len;
    uint8_t pid;
    uint8_t type;
    signal_t* s[64];
    uint8_t signal_len;
}message_t;

/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/
void LIN_initSlave(void);
void LIN_SlaveTask(void);
#endif // COMSTACK_LIN_LIN_HAL_INCLUDE_LINSLAVE_H_