#include "SWapp.h"

void Runnable_app (void)
{
    uint32_t myState = 0;
    Get_Switch_State(Switch_1, &myState);
    LED_Set_state(greenLed,LED_SET_LOW);
    if(myState == SWITCH_PRESSED)
    {
        LED_Set_state(greenLed,LED_SET_HIGH);
    }
}