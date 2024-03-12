#include"SYSTICK.h"

volatile int x = 0;
void Increment (void);
int main()
{
    SYSTICK_CLKSOURCE(AHBCLK);
    SYSTICK_SetCallBack(&Increment);
    SYSTICK_SetTimeMS(1000);
    SYSTICK_Start();
    while(1)
    {

    }
}

void Increment (void)
{
    x++;
}