#ifndef E__ES_ITI_ARM_STM32F401CC_DRIVERS_WORKSPACE_HOST_LOG_DRIVER_LOG_H_
#define E__ES_ITI_ARM_STM32F401CC_DRIVERS_WORKSPACE_HOST_LOG_DRIVER_LOG_H_


/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include <inttypes.h>

/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define LOG_OUT_FILE    0
#define LOG_OUT_CONSOLE 1

#define LOG_CRITICAL    0
#define LOG_ERROR       1
#define LOG_WARNING     2
#define LOG_INFO        3

/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef enum{
    LOG_isOk,
    LOG_NotOk,
    LOG_WrongOut,
    LOG_NULLPTR,
    LOG_WrongSeverityLevel,
    LOG_WrongElementsNo
} LOG_errorStatus_t;



/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

LOG_errorStatus_t LOG_setOutputChnl(uint8_t LOG_OUT_DEST);

LOG_errorStatus_t LOG_logFileCFG(uint8_t* FilePath);

LOG_errorStatus_t LOG_logFileClose(void);

LOG_errorStatus_t LOG_write(uint8_t Severity_Level, uint8_t* Text);

LOG_errorStatus_t LOG_setSeverity(uint8_t Severity_Level);

LOG_errorStatus_t LOG_writeWithParameters(uint8_t Severity_Level, uint8_t ParametersNo, ...);

LOG_errorStatus_t LOG_ClearLogFile(void);

LOG_errorStatus_t LOG_ReadFile(void);


#endif // E__ES_ITI_ARM_STM32F401CC_DRIVERS_WORKSPACE_HOST_LOG_DRIVER_LOG_H_