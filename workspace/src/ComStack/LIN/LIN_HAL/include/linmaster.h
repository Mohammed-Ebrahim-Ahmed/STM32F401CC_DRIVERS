#ifndef COMSTACK_LIN_LIN_HAL_INCLUDE_LINMASTER_H_
#define COMSTACK_LIN_LIN_HAL_INCLUDE_LINMASTER_H_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "linmaster_CFG.h"
#include "GPIO.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define SENDER 0
#define RECEIVER 1

#define NUM_OF_MESSAGES 2
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct message_t message_t;
typedef struct {
    GPIO_Pin_t TxUart_pin ;
    GPIO_Pin_t RxUart_pin ;
    volatile void *  UART_NO;
    uint8_t wordLength;
    uint16_t stopBits;
    uint16_t oversampling;
    uint16_t baudrate;
}LIN_UART_t;

typedef struct {
    uint8_t idx;
    uint8_t len;
    message_t* mes;
}signal_t;

typedef struct message_t{
    uint8_t id;
    uint8_t data[8];
    uint8_t data_len;
    uint8_t pid;
    uint8_t type;
    signal_t* s[64];
    uint8_t signal_len;
}message_t;

typedef struct {
    message_t* m;
    uint16_t slotMS;
}schedTableEntry;

typedef struct {

}LIN_BRIDGE_errorStatus_t;


/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

void LIN_initMaster(void);
void LIN_MasterTask(void);
#endif // COMSTACK_LIN_LIN_HAL_INCLUDE_LINMASTER_H_