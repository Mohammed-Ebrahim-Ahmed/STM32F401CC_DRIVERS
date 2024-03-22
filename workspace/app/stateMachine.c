#include "stateMachine.h"
#include "LED.h"
void Runnable_app(void)
{
    static uint8_t timeElapsed = 0;
    static uint8_t state = green;
    static uint8_t prevState = green;
    timeElapsed +=2;
    switch(state)
    {
        case green:
            LED_Set_state(greenLed, LED_SET_HIGH);
            LED_Set_state(yellowLed, LED_SET_LOW);
            LED_Set_state(redLed, LED_SET_LOW);
            if(timeElapsed == 6)
            {
                state = yellow;
                timeElapsed = 0;
                prevState = green;
            }

            break;
        case yellow:
            LED_Set_state(greenLed, LED_SET_LOW);
            LED_Set_state(yellowLed, LED_SET_HIGH);
            LED_Set_state(redLed, LED_SET_LOW);
            if(prevState == green && timeElapsed == 2)
            {
                state = red;
                timeElapsed = 0;
                prevState = yellow;
            }
            else if(prevState == red && timeElapsed == 2)
            {
                state = green;
                timeElapsed = 0;
                prevState = yellow;                
            }
            else
            {

            }
            break;
        case red:
            LED_Set_state(greenLed, LED_SET_LOW);
            LED_Set_state(yellowLed, LED_SET_LOW);
            LED_Set_state(redLed, LED_SET_HIGH);
            if(timeElapsed == 20)
            {
                state = green;
                timeElapsed = 0;
                prevState = red;
            }
            break;
        default:
            break;
    }
    
}