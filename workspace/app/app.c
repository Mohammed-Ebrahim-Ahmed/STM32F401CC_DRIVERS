
#include "LCD_HAL.h"

void MoreDummy(void);

void Dummy_runnable (void)
{
    static uint8_t time = 0;
    if(time ==0)
    {
        LCD_writeReq((uint8_t *)"Ahmed",5,1,3,&MoreDummy);
        LCD_writeReq((uint8_t *)"Mohsen",6,0,3,&MoreDummy);
    }
    else if (time == 5)
    {
        // LCD_clearScreen(&MoreDummy);
        LCD_CommandReq(0x18,&MoreDummy);
    }
    time++;
}

void MoreDummy(void)
{
    volatile static uint16_t x = 0;
    x++;
}