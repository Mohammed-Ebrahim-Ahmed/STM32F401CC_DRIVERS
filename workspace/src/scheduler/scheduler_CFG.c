#include "scheduler.h"

// extern Runnable Runnable_first;
// extern Runnable Runnable_second;
// extern Runnable Runnable_third;
extern Runnable SW_runnable;
extern Runnable Runnable_app;
const Runnable_USER_t Runnable_User [_RUNNABLE_NO] =
{
    [Runnable_0] = {
        .Name = "my_first",
        .Priority = 0,
        .Periodicity = 5,
        .CB = (Runnable)&SW_runnable,
        .First_Delay = 0
    },
    [Runnable_1] = {
        .Name = "my_second",
        .Priority = 1,
        .Periodicity = 50,
        .CB = (Runnable)&Runnable_app,
        .First_Delay = 0
    }
};