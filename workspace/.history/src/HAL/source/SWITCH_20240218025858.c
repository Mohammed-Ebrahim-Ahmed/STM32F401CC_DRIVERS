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
        Pin->Mode = SWITCHS[LOC_Counter].Mode;
        GPIO_init(&Pin);
    }
}

SWITCH_errorStatus_t Get_Switch_State(uint32_t SWITCH, uint32_t* state)
{
    uint8_t LOC_Counter = 0;
    uint8_t flag = 0;

    for(LOC_Counter = 0; (LOC_Counter < _SWITCH_NO; LOC_Counter++)
    {
        if(LOC_Counter == SWITCH)
        {
            flag = 1;
        }
    }

}