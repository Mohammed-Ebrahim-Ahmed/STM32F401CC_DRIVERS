#include "LCD_HAL.h"
#include "GPIO.h"



/*please select pins like this in FOUR_BIT MODE
    pin0 --> RS
    pin1 --> RW
    pin2 --> EN
    pin3 --> d4
    pin4 --> d5
    pin5 --> d6
    pin6 --> d7
*/
#if LCD_MODE == FOUR_BIT_MODE
const LCD_Pins_t LCD_Connection = {

    .LCD_DataPort = {GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA},
    .LCD_DataPin = { GPIO_PIN0, GPIO_PIN1, GPIO_PIN2, GPIO_PIN3, GPIO_PIN4, GPIO_PIN5, GPIO_PIN6}
};
#elif LCD_MODE == EIGHT_BIT_MODE
const LCD_Pins_t LCD_Connection = {

    .LCD_DataPort = {GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA, GPIO_PORTA},
    .LCD_DataPin =  {GPIO_PIN0, GPIO_PIN1, GPIO_PIN2, GPIO_PIN3, GPIO_PIN4, GPIO_PIN5, GPIO_PIN6, GPIO_PIN7, GPIO_PIN8, GPIO_PIN9, GPIO_PIN10}
};
#else

#endif