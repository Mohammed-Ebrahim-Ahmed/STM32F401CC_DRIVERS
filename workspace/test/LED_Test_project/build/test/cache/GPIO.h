









typedef struct{

    uint32_t Pin;

    volatile void* Port;

    uint32_t Speed;

    uint32_t Mode;





} GPIO_Pin_t;



typedef enum{

    GPIO_isOk,

    GPIO_isNotOk,

    GPIO_WrongPin,

    GPIO_WrongPort,

    GPIO_WrongSpeed,

    GPIO_WrongMode,

    GPIO_WrongSetValue,

    GPIO_WrongGetValue

} GPIO_ErrorStatus_t;

GPIO_ErrorStatus_t GPIO_init(GPIO_Pin_t* GPIO_Pin);

GPIO_ErrorStatus_t GPIO_SetPinValue(volatile void* GPIO_Port, uint32_t GPIO_Pin, uint32_t GPIO_Val_Set);

GPIO_ErrorStatus_t GPIO_GetPinValue(volatile void* GPIO_Port, uint32_t GPIO_Pin, uint32_t* GPIO_Status);
