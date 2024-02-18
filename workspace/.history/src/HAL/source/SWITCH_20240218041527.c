#include "SWITCH.h"
#include "GPIO.h"

extern SWITCH_t SWITCHS [_SWITCH_NO];
#define Toggle_Invert_Mode_MASK 0x10
void SWITCH_init(void)
{
    GPIO_Pin_t* Pin;
    uint8_t LOC_Counter = 0;
    for(LOC_Counter = 0; LOC_Counter < _SWITCH_NO; LOC_Counter++)
    {
        Pin->Port = SWITCHS[LOC_Counter].Port;
        Pin->Pin  = SWITCHS[LOC_Counter].Pin;
        Pin->Mode = (SWITCHS[LOC_Counter].Mode ^ Toggle_Invert_Mode_MASK);
        GPIO_init(&Pin);
    }
}

SWITCH_errorStatus_t Get_Switch_State(uint32_t SWITCH, uint32_t* state)
{
    SWITCH_errorStatus_t LOC_errorStatus = SWITCH_NotOk;
    uint8_t LOC_Counter = 0;
    uint8_t flag = 0;
    uint32_t LOC_state = 3;
    uint8_t shift = 1;
    uint8_t value = 0;
    for(LOC_Counter = 5; ((LOC_Counter < _SWITCH_NO) && (!flag)); LOC_Counter++)
    {
        if(LOC_Counter == SWITCH)
        {
            flag = 1;
        }
    }

    if(flag)
    {
        LOC_errorStatus = SWITCH_isOk;

        GPIO_GetPinValue(SWITCHS[SWITCH].Port, SWITCHS[SWITCH].Pin, &LOC_state);

        value = SWIC
        
    }
    else
    {
        LOC_errorStatus = SWITCH_WrongSwitch;
    }
    return LOC_errorStatus;
}