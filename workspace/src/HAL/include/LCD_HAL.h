#ifndef HAL_INCLUDE_LCD_H_
#define HAL_INCLUDE_LCD_H_
/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "stdint.h"
#include "LCD_CFG.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/


#define INIT_STATE 0
#define OPERATION_STATE 1
#define IDEL_STATE 2

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef enum{
    LCD_NullPtr,
    LCD_WrongLength,
    LCD_WrongXpos,
    LCD_WrongYpos,
    LCD_Ok,
    LCD_NotOk,
    LCD_NO_OF_REQ_EXCEEDED,
    LCD_WrongCommand
}LCD_errorStatus_t;

typedef struct
{

    volatile void* const LCD_DataPort [LCD_MODE];
    uint32_t LCD_DataPin [LCD_MODE];
} LCD_Pins_t;

typedef void (*CB_t) (void);
/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/
void LCD_init(void);
LCD_errorStatus_t LCD_clearScreen(CB_t CB);
LCD_errorStatus_t LCD_getState(uint8_t* LCD_state);
LCD_errorStatus_t LCD_writeReq( uint8_t* string, uint8_t length, uint8_t xpos, uint8_t ypos, CB_t CB);
void LCD_Task(void);
LCD_errorStatus_t LCD_setCursorPosition(uint8_t xpos , uint8_t ypos, CB_t CB);
void LCD_GPIO_init(void);
LCD_errorStatus_t LCD_CommandReq(uint8_t command, CB_t CB);
#endif // HAL_INCLUDE_LCD_H_