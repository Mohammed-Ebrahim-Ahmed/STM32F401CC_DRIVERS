#include "log.h"
#include <time.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/
static uint8_t channel_output = -1;
static uint8_t severity_level = -1;
static uint8_t * Severity_level_arr [4] = {"Critical","Error","Warning","Info"}; 
static FILE *fptr = NULL;
static uint8_t * filePath = NULL;
/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/


LOG_errorStatus_t LOG_setOutputChnl(uint8_t LOG_OUT_DEST)
{
    LOG_errorStatus_t LOG_errorStatus = LOG_NotOk;

    if(LOG_OUT_DEST > LOG_OUT_CONSOLE)
    {
        LOG_errorStatus = LOG_WrongOut;
    }
    else
    {
        LOG_errorStatus = LOG_isOk;
        channel_output = LOG_OUT_DEST;
    }

    return LOG_errorStatus;
}

LOG_errorStatus_t LOG_logFileCFG(uint8_t* FilePath)
{
    LOG_errorStatus_t LOG_errorStatus = LOG_NotOk;
    if(FilePath == NULL)
    {
        LOG_errorStatus = LOG_NULLPTR;
    }
    else
    {
        LOG_errorStatus = LOG_isOk;
        filePath = FilePath;
        fptr = fopen(FilePath,"a");

        if(fptr == NULL)
        {
            printf("Error!");   
            exit(1);             
        }
    }
}

LOG_errorStatus_t LOG_logFileClose(void)
{
    LOG_errorStatus_t LOG_errorStatus = LOG_NotOk;
    if(fptr == NULL)
    {
        LOG_errorStatus = LOG_NULLPTR;
    }
    else
    {
        LOG_errorStatus = LOG_isOk;
        fclose(fptr);
    }
    return LOG_errorStatus;
}
LOG_errorStatus_t LOG_write(uint8_t Severity_Level, uint8_t* Text)
{
    LOG_errorStatus_t LOG_errorStatus = LOG_NotOk;
    struct tm* tm;
    time_t t;
    t = time(NULL);
    tm = localtime(&t);
    if(Text == NULL)
    {
        LOG_errorStatus = LOG_NULLPTR;
    }
    else if(Severity_Level > LOG_INFO)
    {
        LOG_errorStatus = LOG_WrongSeverityLevel;
    }
    else
    {
        LOG_errorStatus = LOG_isOk;

        switch(channel_output)
        {
            case LOG_OUT_FILE:
                fprintf(fptr,"[%02d:%02d:%02d]:[%s]: %s\n", tm->tm_hour, tm->tm_min, tm->tm_sec,Severity_level_arr[severity_level],Text);
                break;
            case LOG_OUT_CONSOLE:
                printf("[%02d:%02d:%02d]:[%s]: %s\n",tm->tm_hour, tm->tm_min, tm->tm_sec,Severity_level_arr[severity_level],Text);
                break;
            default:
                break;
        }

    }    
    return LOG_errorStatus;
}


LOG_errorStatus_t LOG_setSeverity(uint8_t Severity_Level)
{

    LOG_errorStatus_t LOG_errorStatus = LOG_NotOk;
    if(Severity_Level > LOG_INFO)
    {
        LOG_errorStatus = LOG_WrongSeverityLevel;
    }
    else
    {
        LOG_errorStatus = LOG_isOk;
        severity_level = Severity_Level;

    }
    return LOG_errorStatus;

}

LOG_errorStatus_t LOG_writeWithParameters(uint8_t Severity_Level, uint8_t ParametersNo, ...)
{
    LOG_errorStatus_t LOG_errorStatus = LOG_NotOk;
    struct tm* tm;
    time_t t;
    t = time(NULL);
    tm = localtime(&t);

    va_list ptr = NULL;
    va_start(ptr, ParametersNo);
    int i = 0;
    if(ParametersNo < 1)
    {
        LOG_errorStatus = LOG_WrongElementsNo;
    }
    else if(Severity_Level > LOG_INFO)
    {
        LOG_errorStatus = LOG_WrongSeverityLevel;
    }
    else
    {
        LOG_errorStatus = LOG_isOk;

        switch(channel_output)
        {
            case LOG_OUT_FILE:
                for (i = 0; i < ParametersNo; i++)                  
                    fprintf(fptr,"[%02d:%02d:%02d]:[%s]: %s\n", tm->tm_hour, tm->tm_min, tm->tm_sec,Severity_level_arr[severity_level],va_arg(ptr, uint8_t*));
                va_end(ptr);
                break;
            case LOG_OUT_CONSOLE:
                for (i = 0; i < ParametersNo; i++)
                    printf("[%02d:%02d:%02d]:[%s]: %s\n",tm->tm_hour, tm->tm_min, tm->tm_sec,Severity_level_arr[severity_level],va_arg(ptr, uint8_t*));
                va_end(ptr);
                break;
            default:
                break;
        }

    }    
    return LOG_errorStatus;
}

LOG_errorStatus_t LOG_ClearLogFile(void)
{
    LOG_errorStatus_t LOG_errorStatus = LOG_NotOk;
    if(fptr == NULL)
    {
        LOG_errorStatus = LOG_NULLPTR;
    }
    else
    {
        LOG_errorStatus = LOG_isOk;
        FILE *fptr;

        // use appropriate location if you are using MacOS or Linux
        fptr = fopen(filePath,"w");

        if(fptr == NULL)
        {
            printf("Error!");   
            exit(1);             
        }
        fprintf(fptr,"%s","");
        fclose(fptr);
    }
    return LOG_errorStatus;
}