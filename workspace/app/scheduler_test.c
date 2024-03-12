#include "scheduler.h"

void Runnable_first(void);
void Runnable_second(void);
void Runnable_third(void);
volatile uint8_t x = 0;
volatile uint8_t y = 0;
volatile uint8_t z = 0;

int main()
{
    SCH_init();
    SCH_Start();
}

void Runnable_first(void)
{
    x++;
}

void Runnable_second(void)
{
    y++;
}

void Runnable_third(void)
{
    z++;

}