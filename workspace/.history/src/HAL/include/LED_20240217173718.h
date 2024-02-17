#ifndef LED_H_
#define LED_H_


typedef enum {
    LED_NotOk,
    LED_isOk,
    LED_WrongPort,
    LED_WrongPin,
    LED_WrongConnection,
    LED_WrongState
}LED_errorStatus_t;

typedef struct
{
    volatile void* const port,
    
}
LED_errorStatus_t LED_init()
#endif