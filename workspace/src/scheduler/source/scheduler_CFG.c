#include "scheduler.h"

// extern Runnable Runnable_first;
// extern Runnable Runnable_second;
// extern Runnable Runnable_third;
// extern Runnable SW_runnable;
// extern Runnable Runnable_app;
// extern Runnable Runnable_app;
// extern Runnable Dummy_runnable;
extern Runnable LCD_TASK;
extern Runnable DateTime;
extern Runnable displayControl;
extern Runnable EditTimeModeSM;
extern Runnable readSwitches;
extern Runnable stopWatch;

const Runnable_USER_t Runnable_User [_RUNNABLE_NO] =
{   [Runnable_0] = {
        .Name = "readSwitches",
        .Priority = 0,
        .Periodicity = 60,
        .CB = (Runnable)&readSwitches,
        .First_Delay = 0
    },
    [Runnable_1] = {
        .Name = "LCD_TASK",
        .Priority = 0,
        .Periodicity = 1,
        .CB = (Runnable)&LCD_TASK,
        .First_Delay = 0
    },
    [Runnable_2] = {
        .Name = "DateTime",
        .Priority = 0,
        .Periodicity = 100,
        .CB = (Runnable)&DateTime,
        .First_Delay = 200
    },
    [Runnable_3] = {
        .Name = "EditTimeModeSM",
        .Priority = 0,
        .Periodicity = 100,
        .CB = (Runnable)&EditTimeModeSM,
        .First_Delay = 200
    },
    [Runnable_4] = {
        .Name = "StopWatch",
        .Priority = 0,
        .Periodicity = 100,
        .CB = (Runnable)&stopWatch,
        .First_Delay = 200
    },
    [Runnable_5] = {
        .Name = "displayControl",
        .Priority = 0,
        .Periodicity = 100,
        .CB = (Runnable)&displayControl,
        .First_Delay = 200
    },

};