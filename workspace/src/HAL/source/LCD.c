/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "LCD.h"
#include "GPIO.h"
#include "RCC.h"


/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#ifndef NULL
#define NULL (void *)0
#endif

#define RS 0
#define RW 1
#define EN 2

#define REQ_TYPE_WRITE   0
#define REQ_TYPE_CLEAR   1
#define REQ_TYPE_SET_POS 2
#define REQ_TYPE_NOREQ   3

#define REQ_STATE_BUSY  0
#define REQ_STATE_READY 1

#define LCD_INIT_STATE_POWER_ON       0
#define LCD_INIT_STATE_FUNCTIONAL_SET 1
#define LCD_INIT_STATE_DISPLAY        2
#define LCD_INIT_STATE_CLEAR          3
#define LCD_INIT_STATE_ENTRY          4
#define LCD_INIT_STATE_END            5

#define LCD_INPUT_COMMAND  GPIO_SET_PIN_LOW
#define LCD_INPUT_DATA     GPIO_SET_PIN_HIGH

#if LCD_MODE == EIGHT_BIT_MODE

    #define FUNCTION_SET 0x38

    /**
     * @brief choose between following configuations
     * 
     * DISPLAY_ON_OFF_CONTROL 0x0f for display on and Cursor display on and blinkin is active
     * DISPLAY_ON_OFF_CONTROL 0x0e for display on and Cursor display on and blinkin is inactive
     * DISPLAY_ON_OFF_CONTROL 0x0c for display on and Cursor display off
     * DISPLAY_ON_OFF_CONTROL 0x08 for display off
     * 
     */
    #define DISPLAY_ON_OFF_CONTROL 0x0e

    #define DISPLAY_CLEAR 0x01

    /**
     * @brief choose between following configuations 
     * 
     * ENTRY_MODE_SET 0x06 for increasing DDRAM address by 1 or decrease by 1 when code is written or read from DDRAM
     * and the display does not shift
     * 
     * ENTRY_MODE_SET 0x07 for increasing DDRAM address by 1 or decrease by 1 when code is written or read from DDRAM 
     * and the dispaly shifts to left
     * 
     * ENTRY_MODE_SET 0x05 for shifting the display to right
     * 
     */
    #define ENTRY_MODE_SET 0x06

#elif LCD_MODE == FOUR_BIT_MODE

    #define FUNCTION_SET_1 0x20
    #define FUNCTION_SET_2 0x20
    #define FUNCTION_SET_3 0x80

    #define DISPLAY_ON_OFF_CONTROL_1 0x00
    /**
     * @brief choose between following configuations
     * 
     * DISPLAY_ON_OFF_CONTROL_2 0xf0 for display on and Cursor display on and blinkin is active
     * DISPLAY_ON_OFF_CONTROL_2 0xe0 for display on and Cursor display on and blinkin is inactive
     * DISPLAY_ON_OFF_CONTROL_2 0xc0 for display on and Cursor display off
     * DISPLAY_ON_OFF_CONTROL_2 0x80 for display off
     * 
     */
    #define DISPLAY_ON_OFF_CONTROL_2 0xf0

    #define DISPLAY_CLEAR_1 0x00
    #define DISPLAY_CLEAR_2 0x10

    #define ENTRY_MODE_SET_1 0x00
    /**
     * @brief choose between the following configuations
     * 
     * ENTRY_MODE_SET_2 0x60 for increasing or decreasing the address by one when writing to or reading from the DDRAM 
     * and the display do not shift 
     * 
     * ENTRY_MODE_SET_2 0x70 for increasing or decreasing the address by one when writing to or reading from the DDRAM 
     * and display shifts to left
     * 
     * ENTRY_MODE_SET_2 0x50 for shifting the display to right 
     * 
     */
    #define ENTRY_MODE_SET_2 0x60

	#define SHIFT_LEFT 0x18
	
	#define SHIFT_RIGHT 0x1c
	
#else

    #error "Wrong LCD mode selection"

#endif
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct{
    const char* s;
    uint8_t len;
    uint8_t state;
    uint8_t type;
    uint8_t xpos;
    uint8_t ypos;
}User_Req_t;



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
volatile static uint8_t GLOBAL_LCD_STATE = INIT_STATE;
volatile static User_Req_t User_Req ={
    .s = NULL,
    .len = 0,
    .state = REQ_STATE_READY,
    .type = REQ_TYPE_NOREQ,
    .xpos = 0,
    .ypos = 0
};
extern const LCD_Pins_t LCD_Connection;

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/
static void LCD_writeProc(void);
static void LCD_clearProc(void);
static void LCD_setPosProc(void);
static void LCD_GPIO_init(void);
static void LCD_writeInitCommand (uint8_t command);
static void LCD_writeCommand(uint8_t command);
static void LCD_writeData(uint8_t data);
static void LCD_write(uint8_t type, uint8_t input);
/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


void LCD_TASK(void)
{
    if(GLOBAL_LCD_STATE == INIT_STATE)
    {
        LCD_init();
    }
    else if(GLOBAL_LCD_STATE == OPERATION_STATE)
    {
        if (User_Req.state == REQ_STATE_BUSY)
        {
            switch(User_Req.type)
            {
                case REQ_TYPE_WRITE:
                    LCD_writeProc();
                    break;
                case REQ_TYPE_CLEAR:
                    LCD_clearProc();
                    break;
                case REQ_TYPE_SET_POS:
                    LCD_setPosProc();
                    break;
                default:
                    break;
            }
        }
    }
    else if(GLOBAL_LCD_STATE == IDEL_STATE )
    {

    }
    else
    {

    }
}

LCD_errorStatus_t LCD_writeString(uint8_t* string, uint8_t length, uint8_t xpos, uint8_t ypos)
{
    LCD_errorStatus_t LCD_errorStatus = LCD_NotOk;

    if(string == NULL)
    {
        LCD_errorStatus = LCD_NullPtr;
    }
    else if(length <= 0)
    {
        LCD_errorStatus = LCD_WrongLength;
    }
    else if(xpos <= 0)
    {
        LCD_errorStatus = LCD_WrongXpos;
    }
    else if(ypos <= 0)
    {
        LCD_errorStatus = LCD_WrongYpos;
    }
    else
    {
        LCD_errorStatus = LCD_Ok;

        if(GLOBAL_LCD_STATE == OPERATION_STATE && User_Req.state == REQ_STATE_READY)
        {
            User_Req.state = REQ_STATE_BUSY;
            User_Req.s = string;
            User_Req.len = length;
            User_Req.type = REQ_TYPE_WRITE;
            User_Req.xpos = xpos;
            User_Req.ypos = ypos;
        }
    }

    return LCD_errorStatus;
}

LCD_errorStatus_t LCD_getState(uint8_t* LCD_state)
{
    LCD_errorStatus_t LCD_errorStatus = LCD_NotOk;

    if(LCD_state == NULL)
    {
        LCD_errorStatus = LCD_NullPtr;
    }
    else
    {
        LCD_errorStatus = LCD_Ok;
        *LCD_state = GLOBAL_LCD_STATE;
    }
    return LCD_errorStatus;
}

void LCD_clearScreen(void)
{
    if(GLOBAL_LCD_STATE == OPERATION_STATE && User_Req.state == REQ_STATE_READY)
    {
        User_Req.state = REQ_STATE_BUSY;
        User_Req.type = REQ_TYPE_CLEAR;
    }
}

LCD_errorStatus_t LCD_setCursorPosition(uint8_t xpos , uint8_t ypos)
{
    LCD_errorStatus_t LCD_errorStatus = LCD_NotOk;

    if(xpos <= 0)
    {
        LCD_errorStatus = LCD_WrongXpos;
    }
    else if(ypos <= 0)
    {
        LCD_errorStatus = LCD_WrongYpos;
    }
    else
    {
        LCD_errorStatus = LCD_Ok;
        if(GLOBAL_LCD_STATE == OPERATION_STATE && User_Req.state == REQ_STATE_READY)
        {
            User_Req.state = REQ_STATE_BUSY;
            User_Req.xpos = xpos;
            User_Req.ypos = ypos;
            User_Req.type = REQ_TYPE_SET_POS;
        }
    }
    return LCD_errorStatus;
}

void LCD_init(void)
{
    static uint8_t LCD_init_state = LCD_INIT_STATE_POWER_ON;
    static uint8_t time = 0;
    switch (LCD_init_state)
    {
        
    case LCD_INIT_STATE_POWER_ON:
        LCD_GPIO_init();
        LCD_init_state = LCD_INIT_STATE_FUNCTIONAL_SET;
        break;

    case LCD_INIT_STATE_FUNCTIONAL_SET:
        if(time == 50)
        {
            LCD_writeInitCommand(FUNCTION_SET_1);
        }
        else if(time == 51)
        {
            LCD_writeInitCommand(FUNCTION_SET_2);
        }
        else if(time == 52)
        {
            LCD_writeInitCommand(FUNCTION_SET_3);
            
        }
        LCD_init_state = LCD_INIT_STATE_DISPLAY;
        break;    

    case LCD_INIT_STATE_DISPLAY:
        if(time == 53)
        {
            LCD_writeInitCommand(DISPLAY_ON_OFF_CONTROL_1);
        }
        else if(time == 54)
        {
            LCD_writeInitCommand(DISPLAY_ON_OFF_CONTROL_2);
        }
        LCD_init_state = LCD_INIT_STATE_CLEAR;
        break;

    case LCD_INIT_STATE_CLEAR:
        if(time == 55)
        {
            LCD_writeInitCommand(DISPLAY_CLEAR_1);
        }
        else if(time == 57)
        {
            LCD_writeInitCommand(DISPLAY_CLEAR_2);
        }
        LCD_init_state = LCD_INIT_STATE_ENTRY;
        break;

    case LCD_INIT_STATE_ENTRY:
        if(time == 59)
        {
            LCD_writeInitCommand(ENTRY_MODE_SET_1);
        }
        else if(time == 60)
        {
            LCD_writeInitCommand(ENTRY_MODE_SET_2);
        }
        LCD_init_state = LCD_INIT_STATE_END;
        break;

    case LCD_INIT_STATE_END:
        GLOBAL_LCD_STATE = OPERATION_STATE;
        break;

    default:
        break;
    }
    time++;
}

void LCD_GPIO_init(void)
{
    GPIO_Pin_t Pin ;
    Pin.Mode = GPIO_OUT_PP;
    Pin.Speed = GPIO_SPEED_MEDIUM;
    int i = 0;

    for(i = 0; i < LCD_MODE; i++)
    {
        Pin.Port = LCD_Connection.LCD_DataPort[i];
        Pin.Pin =   LCD_Connection.LCD_DataPin[i];
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
        GPIO_SetPinValue(Pin.Port, Pin.Pin, GPIO_SET_PIN_LOW);
    }
}

void LCD_writeInitCommand(uint8_t command)
{
    static uint8_t counter = 0;
    if(LCD_MODE == FOUR_BIT_MODE)
    {
        
        if (counter == 0)
        {
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[RS], LCD_Connection.LCD_DataPin[RS], GPIO_SET_PIN_LOW);
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[RW], LCD_Connection.LCD_DataPin[RW], GPIO_SET_PIN_LOW);
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[3], LCD_Connection.LCD_DataPin[3], ( (command>>4) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[4], LCD_Connection.LCD_DataPin[4], ( (command>>5) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[5], LCD_Connection.LCD_DataPin[5], ( (command>>6) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[6], LCD_Connection.LCD_DataPin[6], ( (command>>7) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_HIGH);                   
        }
        counter++;
        if(counter > 2)
        {
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_LOW);
            counter = 0;
        }
        
    }
}

// void LCD_writeCommand(uint8_t command)
// {
//     static uint8_t counter = 0;

//     if(LCD_MODE == FOUR_BIT_MODE)
//     {
//         if(counter == 0)
//         {
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[RS], LCD_Connection.LCD_DataPin[RS], GPIO_SET_PIN_LOW);
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[RW], LCD_Connection.LCD_DataPin[RW], GPIO_SET_PIN_LOW);
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[3], LCD_Connection.LCD_DataPin[3], ( (command>>4) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[4], LCD_Connection.LCD_DataPin[4], ( (command>>5) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[5], LCD_Connection.LCD_DataPin[5], ( (command>>6) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[6], LCD_Connection.LCD_DataPin[6], ( (command>>7) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_HIGH);       
//         }
//         else if(counter == 2)
//         {
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_LOW);
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[3], LCD_Connection.LCD_DataPin[3], ( (command>>0) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[4], LCD_Connection.LCD_DataPin[4], ( (command>>1) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[5], LCD_Connection.LCD_DataPin[5], ( (command>>2) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[6], LCD_Connection.LCD_DataPin[6], ( (command>>3) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_HIGH);
//         }
//         else if(counter == 4)
//         {
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_LOW);
//         }
//         counter++;       
        
//     }    
// }

// static void LCD_writeData(uint8_t data)
// {
//     static uint8_t counter = 0;

//     if(LCD_MODE == FOUR_BIT_MODE)
//     {
//         if(counter == 0)
//         {
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[RS], LCD_Connection.LCD_DataPin[RS], GPIO_SET_PIN_HIGH);
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[RW], LCD_Connection.LCD_DataPin[RW], GPIO_SET_PIN_LOW);
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[3], LCD_Connection.LCD_DataPin[3], ( (data>>4) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[4], LCD_Connection.LCD_DataPin[4], ( (data>>5) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[5], LCD_Connection.LCD_DataPin[5], ( (data>>6) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[6], LCD_Connection.LCD_DataPin[6], ( (data>>7) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_HIGH);       
//         }
//         else if(counter == 2)
//         {
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_LOW);
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[3], LCD_Connection.LCD_DataPin[3], ( (data>>0) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[4], LCD_Connection.LCD_DataPin[4], ( (data>>1) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[5], LCD_Connection.LCD_DataPin[5], ( (data>>2) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[6], LCD_Connection.LCD_DataPin[6], ( (data>>3) & 1));
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_HIGH);
//         }
//         else if(counter == 4)
//         {
//             GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_LOW);
//         }
//         counter++;       
        
//     }        
// }

static void LCD_write(uint8_t type, uint8_t input)
{
    static uint8_t counter = 0;

    if(LCD_MODE == FOUR_BIT_MODE)
    {
        if(counter == 0)
        {
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[RS], LCD_Connection.LCD_DataPin[RS], type);
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[RW], LCD_Connection.LCD_DataPin[RW], GPIO_SET_PIN_LOW);
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[3], LCD_Connection.LCD_DataPin[3], ( (input>>4) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[4], LCD_Connection.LCD_DataPin[4], ( (input>>5) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[5], LCD_Connection.LCD_DataPin[5], ( (input>>6) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[6], LCD_Connection.LCD_DataPin[6], ( (input>>7) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_HIGH);       
        }
        else if(counter == 2)
        {
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_LOW);
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[3], LCD_Connection.LCD_DataPin[3], ( (input>>0) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[4], LCD_Connection.LCD_DataPin[4], ( (input>>1) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[5], LCD_Connection.LCD_DataPin[5], ( (input>>2) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[6], LCD_Connection.LCD_DataPin[6], ( (input>>3) & 1));
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_HIGH);
        }
        else if(counter == 4)
        {
            GPIO_SetPinValue(LCD_Connection.LCD_DataPort[EN], LCD_Connection.LCD_DataPin[EN],GPIO_SET_PIN_LOW);
        }
        counter++;       
        
    }           
}