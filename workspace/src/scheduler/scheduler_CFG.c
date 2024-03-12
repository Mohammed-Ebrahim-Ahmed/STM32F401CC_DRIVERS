#include "scheduler.h"

// extern Runnable Runnable_first;
// extern Runnable Runnable_second;
// extern Runnable Runnable_third;
// extern Runnable SW_runnable;
// extern Runnable Runnable_app;
extern Runnable Runnable_app;
const Runnable_USER_t Runnable_User [_RUNNABLE_NO] =
{
    [Runnable_0] = {
        .Name = "my_first",
        .Priority = 0,
        .Periodicity = 2000,
        .CB = (Runnable)&Runnable_app,
        .First_Delay = 0
    }
};