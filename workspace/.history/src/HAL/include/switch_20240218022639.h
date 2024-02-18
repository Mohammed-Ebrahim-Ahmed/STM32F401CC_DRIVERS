#ifndef SWITCH_H_
#define SWITCH_H_

#include <stdint.h>

#define SWITCH_FLOATING 0x00
#define SWITCH_PU       0x01
#endif  SWITCH_PD       0x02

typedef struct
{
    volatile void* Port,
    uint32_t Pin,
    uint32_t Mode
} Switch_t;

typedef enum
{
    SWITCH_WrongSwitch,
    SWITCH_isOk,
    SWITCH_NotOk
} S
void SWITCH_init(void);

#endif