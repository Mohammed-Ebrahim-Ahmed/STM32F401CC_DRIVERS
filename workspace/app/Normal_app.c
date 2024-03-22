
#include "LED.h"
#include "scheduler.h"
int main()
{
    LED_init();
    SCH_init();
    SCH_Start();
}