#include "scheduler.h"
#include "LED.h"
#include "SWITCH.h"

int main()
{
    LED_init();
    SWITCH_init();
    SCH_init();
    SCH_Start();
}