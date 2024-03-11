#include "log.h"

int main()
{
    LOG_setOutputChnl(LOG_OUT_FILE);
    LOG_logFileCFG("E:\\ES_ITI\\ARM\\STM32F401CC_DRIVERS\\workspace\\host_log_driver\\log.txt");
    LOG_ClearLogFile();
    LOG_setSeverity(LOG_CRITICAL);
    //LOG_write(LOG_CRITICAL,"hello from error");
    LOG_writeWithParameters(LOG_CRITICAL, 5, "hello from error","hello and shut up","HELLO!","do you hear me","shut up");
    LOG_logFileClose();
    LOG_ClearLogFile();
    LOG_setOutputChnl(LOG_OUT_FILE);
    LOG_logFileCFG("E:\\ES_ITI\\ARM\\STM32F401CC_DRIVERS\\workspace\\host_log_driver\\log.txt");
    LOG_setSeverity(LOG_CRITICAL);
    LOG_writeWithParameters(LOG_CRITICAL, 5, "hello from error","hello and shut up","HELLO!","do you hear me","shut up");
    // LOG_writeWithParameters(LOG_CRITICAL, 5, "hello from error","hello and shut up","HELLO!","do you hear me","shut up");
    // LOG_writeWithParameters(LOG_CRITICAL, 5, "hello from error","hello and shut up","HELLO!","do you hear me","shut up");
    // LOG_writeWithParameters(LOG_CRITICAL, 5, "hello from error","hello and shut up","HELLO!","do you hear me","shut up");
    // LOG_writeWithParameters(LOG_CRITICAL, 5, "hello from error","hello and shut up","HELLO!","do you hear me","shut up");
    LOG_logFileClose();
    LOG_ReadFile();
    return 0;
}