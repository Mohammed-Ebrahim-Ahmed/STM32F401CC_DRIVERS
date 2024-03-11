
#ifdef TEST

#include "unity.h"

#include "LED.h"

#include "mock_GPIO.h"

LED_t LEDS [_LED_COUNT];

void setUp(void)
{
}

void tearDown(void)
{
}

void test_LED_init(void)
{
    GPIO_Pin_t Pin;
    Pin.Mode = GPIO_OUT_PP;
    Pin.Speed = GPIO_SPEED_LOW;
    Pin.Port = LEDS[0].Port;
    Pin.Pin = LEDS[0].Pin;
    int i = 0;
    for(i = 0; i <_LED_COUNT; i++)
    {
        GPIO_init_ExpectAndReturn(&Pin, GPIO_isOk);
        GPIO_SetPinValue_ExpectAndReturn(Pin.Port, Pin.Pin, (LEDS[0].Connection ^ LEDS[0].Default_State), GPIO_isOk);
    }
    TEST_ASSERT_EQUAL(LED_isOk, LED_init());
    mock_GPIO_Verify();
}

void test_LED_init_Wrong_Connection(void)
{
    int i = 0;
    for(i = 0; i <_LED_COUNT; i++)
    {

        LEDS[i].Connection = 3;
        GPIO_init_IgnoreAndReturn(GPIO_isOk);
        GPIO_SetPinValue_IgnoreAndReturn(GPIO_isOk);
        
    }
    //mock_GPIO_Verify();
    TEST_ASSERT_EQUAL(LED_WrongConnection, LED_init());
}
void test_LED_Set_state(void)
{
    LEDS[0].Connection = LED_FORWARD;
    GPIO_SetPinValue_ExpectAndReturn( LEDS[0].Port, LEDS[0].Pin, 1, GPIO_isOk);
    TEST_ASSERT_EQUAL(LED_isOk, LED_Set_state(0, LED_SET_HIGH));
    
    // Verify that GPIO_setPinValue was called with the expected arguments
    mock_GPIO_Verify();
}

void test_LED_Set_state_Wrong_Set(void)
{
    LEDS[0].Connection = LED_FORWARD;
    int state = 2;
    TEST_ASSERT_EQUAL(LED_WrongState, LED_Set_state(0, 2));    
    // Verify that GPIO_setPinValue was called with the expected arguments
    mock_GPIO_Verify();
}

void test_LED_Set_state_Wrong_LED(void)
{
    //LEDS[0].Connection = LED_FORWARD;
    TEST_ASSERT_EQUAL(LED_WrongLED, LED_Set_state(2, 1));    
    // Verify that GPIO_setPinValue was called with the expected arguments
    mock_GPIO_Verify();
}

#endif // TEST
