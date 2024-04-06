#ifndef COMSTACK_LIN_LIN_HAL_INCLUDE_LINTYPES_H_
#define COMSTACK_LIN_LIN_HAL_INCLUDE_LINTYPES_H_

#include <stdint.h>

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

typedef struct {
    message_t* m;
    uint16_t slotMS;
}schedTableEntry;

#endif // COMSTACK_LIN_LIN_HAL_INCLUDE_LINTYPES_H_