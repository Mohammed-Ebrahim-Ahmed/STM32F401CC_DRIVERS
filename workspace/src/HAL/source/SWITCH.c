#include "SWITCH.h"
#include "GPIO.h"
#include "RCC.h"
#include "scheduler.h"

#define Toggle_Invert_Mode_MASK 0x03
#define Bit_extract_Mask 0x2
#define Resolution 5

extern SWITCH_t SWITCHS [_SWITCH_NO];
static volatile uint8_t GLOBAL_STATE[_SWITCH_NO] = {0};

void SWITCH_init(void)
{
    GPIO_Pin_t Pin;
    uint8_t LOC_Counter = 0;
    for(LOC_Counter = 0; LOC_Counter < _SWITCH_NO; LOC_Counter++)
    {
        Pin.Port = SWITCHS[LOC_Counter].Port;
        Pin.Pin  = SWITCHS[LOC_Counter].Pin;
        Pin.Mode = (SWITCHS[LOC_Counter].Mode ^ Toggle_Invert_Mode_MASK);
        Pin.Speed = GPIO_SPEED_MEDIUM;
        if(Pin.Port == GPIO_PORTA)
        {
            RCC_enableAHBPeriCLK(RCC_AHB1_GPIOA);
        }
        else if(Pin.Port == GPIO_PORTB)
        {
            RCC_enableAHBPeriCLK(RCC_AHB1_GPIOB);
        }
        else if(Pin.Port == GPIO_PORTC)
        {
            RCC_enableAHBPeriCLK(RCC_AHB1_GPIOC);
        }
        GPIO_init(&Pin);
    }
}

SWITCH_errorStatus_t Get_Switch_State(uint32_t SWITCH, uint32_t* state)
{
    SWITCH_errorStatus_t LOC_errorStatus = SWITCH_NotOk;
    uint8_t LOC_Counter = 0;
    uint8_t flag = 0;
    // uint32_t LOC_state = 3;
    // uint8_t shift = 1;
    // volatile uint8_t value = 0;

    for(LOC_Counter = 0; ((LOC_Counter < _SWITCH_NO) && (!flag)); LOC_Counter++)
    {
        if(LOC_Counter == SWITCH)
        {
            flag = 1;
        }
    }

    if(flag)
    {
        LOC_errorStatus = SWITCH_isOk;

        // GPIO_GetPinValue(SWITCHS[SWITCH].Port, SWITCHS[SWITCH].Pin, &LOC_state);
        // value = (((SWITCHS[SWITCH].Mode ^ Toggle_Invert_Mode_MASK) ^ Bit_extract_Mask) );
        // value = value>>shift;      
        // *state = (LOC_state ^ value);
        *state = GLOBAL_STATE[SWITCH];
    }
    else
    {
        LOC_errorStatus = SWITCH_WrongSwitch;
    }
    return LOC_errorStatus;
}

void SW_runnable (void)
{
    uint8_t LOC_Counter = 0;
    uint32_t LOC_state = 3;
    uint8_t shift = 1;
    volatile uint8_t value[_SWITCH_NO] = {0};
    volatile uint8_t currentState[_SWITCH_NO] = {0};
    static uint8_t perviousState[_SWITCH_NO] = {0};
    static uint32_t counts[_SWITCH_NO] = {0};

    for(LOC_Counter = 0;LOC_Counter < _SWITCH_NO ; LOC_Counter++)
    {

        GPIO_GetPinValue(SWITCHS[LOC_Counter].Port, SWITCHS[LOC_Counter].Pin, &LOC_state);
        value[LOC_Counter] = (((SWITCHS[LOC_Counter].Mode ^ Toggle_Invert_Mode_MASK) ^ Bit_extract_Mask) );
        value[LOC_Counter] = value[LOC_Counter]>>shift;      
        currentState[LOC_Counter] = (LOC_state ^ value[LOC_Counter]);

        if(perviousState[LOC_Counter] == currentState[LOC_Counter])
        {
            counts[LOC_Counter]++;
        }
        else
        {
            counts[LOC_Counter] = 0;
        }

        if(counts[LOC_Counter] == Resolution)
        {
            GLOBAL_STATE[LOC_Counter] = currentState[LOC_Counter];
            counts[LOC_Counter] = 0;
        }
        perviousState[LOC_Counter] = currentState[LOC_Counter];
    }    
}