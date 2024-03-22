#include "LED.h"
#include "GPIO.h"
#include "RCC.h"

extern const LED_t LEDS [_LED_COUNT];

void LED_init(void)
{
    GPIO_Pin_t Pin ;
    Pin.Mode = GPIO_OUT_PP;
    Pin.Speed = GPIO_SPEED_LOW;
    int i = 0;

    for(i = 0; i <_LED_COUNT; i++)
    {
        Pin.Port = LEDS[i].Port;
        Pin.Pin =  LEDS[i].Pin;
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
        GPIO_SetPinValue(LEDS[i].Port, LEDS[i].Pin, (LEDS[i].Connection ^ LEDS[i].Default_State));
    }


}

LED_errorStatus_t LED_Set_state(uint32_t LED, uint32_t state)
{   
    LED_errorStatus_t LOC_errorStatus = LED_NotOk;
    uint8_t LOC_counter = 0;
    uint8_t flag = 0;
    if( (state != LED_SET_LOW) &&
        (state != LED_SET_HIGH) )
    {
        LOC_errorStatus = LED_WrongState;
    }
    else
    {
        for(LOC_counter = 0; (LOC_counter <_LED_COUNT && (!flag)); LOC_counter++)
        {
            if(LED == LOC_counter)
            {
                flag = 1;
            }
        }
        if(flag)
        {
            GPIO_SetPinValue(LEDS[LED].Port, LEDS[LED].Pin, (LEDS[LED].Connection ^ state));
        }
        else
        {
            LOC_errorStatus = LED_WrongLED;
        }

    }
    return LOC_errorStatus;
}

