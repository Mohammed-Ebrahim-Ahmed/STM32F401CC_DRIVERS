#include "build/test/mocks/mock_GPIO.h"
#include "src/LED.h"
#include "C:/Ruby30/lib/ruby/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"












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

    Pin.Mode = 0x8;

    Pin.Speed = 0x00;

    Pin.Port = LEDS[0].Port;

    Pin.Pin = LEDS[0].Pin;

    int i = 0;

    for(i = 0; i <_LED_COUNT; i++)

    {

        GPIO_init_CMockExpectAndReturn(30, &Pin, GPIO_isOk);

        GPIO_SetPinValue_CMockExpectAndReturn(31, Pin.Port, Pin.Pin, (LEDS[0].Connection ^ LEDS[0].Default_State), GPIO_isOk);

    }

    UnityAssertEqualNumber((UNITY_INT)((LED_isOk)), (UNITY_INT)((LED_init())), (

   ((void *)0)

   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_INT);

    mock_GPIO_Verify();

}



void test_LED_init_Wrong_Connection(void)

{

    int i = 0;

    for(i = 0; i <_LED_COUNT; i++)

    {



        LEDS[i].Connection = 3;

        GPIO_init_CMockIgnoreAndReturn(44, GPIO_isOk);

        GPIO_SetPinValue_CMockIgnoreAndReturn(45, GPIO_isOk);



    }



    UnityAssertEqualNumber((UNITY_INT)((LED_WrongConnection)), (UNITY_INT)((LED_init())), (

   ((void *)0)

   ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_INT);

}

void test_LED_Set_state(void)

{

    LEDS[0].Connection = 0;

    GPIO_SetPinValue_CMockExpectAndReturn(54, LEDS[0].Port, LEDS[0].Pin, 1, GPIO_isOk);

    UnityAssertEqualNumber((UNITY_INT)((LED_isOk)), (UNITY_INT)((LED_Set_state(0, 1))), (

   ((void *)0)

   ), (UNITY_UINT)(55), UNITY_DISPLAY_STYLE_INT);





    mock_GPIO_Verify();

}



void test_LED_Set_state_Wrong_Set(void)

{

    LEDS[0].Connection = 0;

    int state = 2;

    UnityAssertEqualNumber((UNITY_INT)((LED_WrongState)), (UNITY_INT)((LED_Set_state(0, 2))), (

   ((void *)0)

   ), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_INT);



    mock_GPIO_Verify();

}



void test_LED_Set_state_Wrong_LED(void)

{



    UnityAssertEqualNumber((UNITY_INT)((LED_WrongLED)), (UNITY_INT)((LED_Set_state(2, 1))), (

   ((void *)0)

   ), (UNITY_UINT)(73), UNITY_DISPLAY_STYLE_INT);



    mock_GPIO_Verify();

}
