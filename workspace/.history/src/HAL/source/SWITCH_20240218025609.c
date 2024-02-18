#include "SWITCH.h"
#include "GPIO.h"

extern SWITCH_t SWITCHS [_SWITCH_NO];

void SWITCH_init(void)
{
    GPIO_Pin_t* Pin;
    uint8_t LOC_Counter = 0;

    for(LOC_Counter = 0; LOC_Counter < _SWITCH_NO; LOC_Counter++)
    {
        Pin->Port = SWITCHS[LOC_Counter].Port;
        Pin->Pin  = SWITCHS[LOC_Counter].Pin;
        Pin->Mode = SWITCHS[LOC_Counter]
    }
}