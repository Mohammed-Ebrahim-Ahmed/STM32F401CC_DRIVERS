/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include "DMA_Driver.h"
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define DMA_INPUT_ASSERT_OFFSET 32
#define DMA_MAX_STRM_NUM 7

#define DMA_CRTL_STR_EN_DIS_ASSERT_MASK     0x40
#define DMA_GET_INT_STS_CLR_ASSERT_L_MASK   0x01
#define DMA_GET_INT_STS_CLR_ASSERT_H_MASK   0x02
#define DMA_INT_EN_DIS_ASSERT_L_MASK        0x20
#define DMA_INT_EN_DIS_ASSERT_H_MASK        0x30
#define DMA_CHN_SEL_ASSERT_MASK             0x03
#define DMA_MEM_B_ASSERT_MASK               0x04
#define DMA_PERI_B_ASSERT_MASK              0x05
#define DMA_CT_ASSERT_MASK                  0x06
#define DMA_DB_ASSERT_MASK                  0x07
#define DMA_PRIORITY_ASSERT_MASK            0x08
#define DMA_PINCOS_ASSERT_MASK              0x09
#define DMA_MEM_SIZE_ASSERT_MASK            0x0A
#define DMA_PERI_SIZE_ASSERT_MASK           0x0B
#define DMA_MEM_INCR_ASSERT_MASK            0x0C
#define DMA_PERI_INCR_ASSERT_MASK           0x0D
#define DMA_CIRC_ASSERT_MASK                0x0E
#define DMA_TRANS_DIR_ASSERT_MASK           0x0F
#define DMA_PERO_FLOW_ASSERT_MASK           0x10
#define DMA_DIR_MODE_ASSERT_MASK            0x50
#define DMA_FIFO_THRES_ASSERT_MASK          0x60

#define DMA_STREMSTATE_CLEAR_FLAG 0x00000001
#define DMA_INT_STATE_CLEAR_FLAG  0x00000001
#define DMA_CHN_SEL_CLEARFLAG     0x0E000000
#define DMA_MEM_B_CLEARFLAG       0x03000000
#define DMA_PERI_B_CLEARFLAG      0x00600000
#define DMA_CT_CLEAR_FLAG         0x00080000
#define DMA_DB_CLEAR_FLAG         0x00040000
#define DMA_PRIORITY_CLEAR_FLAG   0x00030000
#define DMA_PINCOS_CLEAR_FLAG     0x00008000
#define DMA_MEM_SIZE_CLEAR_FLAG   0x00006000
#define DMA_PERI_SIZE_CLEAR_FLAG  0x00001800
#define DMA_MEM_INCR_CLEAR_FLAG   0x00000400
#define DMA_PERI_INCR_CLEAR_FLAG  0x00000200
#define DMA_CIRC_CLEAR_FLAG       0x00000100
#define DMA_TRANS_DIR_CLEAR_FLAG  0x000000C0
#define DMA_PERI_FLOW_CLEAR_FLAG  0x00000020
#define DMA_DIR_MODE_CLEAR_FLAG   0x00000002
#define DMA_FIFO_THRES_CLEAR_FLAG 0x00000003

#define DMA_CT_GET_FLAG   0x00080000
#define DMA_FIFO_GET_FLAG 0x00000038

#define MAX_MEM_SIZE      0xFFFFFFFF
#define MAX_NITEMS        0x0000FFFF

#ifndef NULL
#define NULL ((void*)0)
#endif
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t NDTR;
    volatile uint32_t PAR;
    volatile uint32_t M0AR;
    volatile uint32_t M1AR;
    volatile uint32_t FCR;
} DMA_STRM_REG_t;

typedef struct
{
    volatile uint32_t LISR;
    volatile uint32_t HISR;
    volatile uint32_t LIFCR;
    volatile uint32_t HIFCR;
    DMA_STRM_REG_t DMA_STRM_REG[7];
} DMA_Peri_t;
/********************************************************************************************************/
/************************************************Variables***********************************************/
/********************************************************************************************************/

/********************************************************************************************************/
/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/

/********************************************************************************************************/
/*********************************************APIs Implementation****************************************/
/********************************************************************************************************/

DMA_errorStatus_t DMA_StreamInit(void* dma, uint8_t stream, uint64_t channel, uint64_t msize, uint64_t psize, uint64_t direction, uint64_t Memory_increment, uint64_t Peripherial_increment , uint64_t priority)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_ch = channel >> DMA_INPUT_ASSERT_OFFSET;
    uint8_t loc_assert_msize = msize >> DMA_INPUT_ASSERT_OFFSET;
    uint8_t loc_assert_psize = psize >> DMA_INPUT_ASSERT_OFFSET;
    uint8_t loc_assert_direction = direction >> DMA_INPUT_ASSERT_OFFSET;
    uint8_t loc_assert_Memory = Memory_increment >> DMA_INPUT_ASSERT_OFFSET;
    uint8_t loc_assert_Peri = Peripherial_increment >> DMA_INPUT_ASSERT_OFFSET;
    uint8_t loc_assert_Priority = priority >> DMA_INPUT_ASSERT_OFFSET;

    uint32_t loc_ch = 0;
    uint32_t loc_msize = 0;
    uint32_t loc_psize = 0;
    uint32_t loc_direction = 0;
    uint32_t loc_Memory_increment = 0;
    uint32_t loc_Peripherial_increment = 0;
    uint32_t loc_Priority = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }
    else if((uint32_t)channel < DMA_CHN_0 || (uint32_t)channel > DMA_CHN_7)
    {
        LOC_errorStatus = DMA_WrongChannel;
    }
    else if((uint32_t)msize < 0 || (uint32_t)msize > MAX_MEM_SIZE)
    {
        LOC_errorStatus = DMA_WrongMemorySize;
    }
    else if((uint32_t)psize < 0 || (uint32_t)psize > MAX_MEM_SIZE)
    {
        LOC_errorStatus = DMA_WrongPeripheralSize;
    }
    else if((uint32_t)direction < DMA_TRANS_DIR_P_TO_M  || (uint32_t)direction > DMA_TRANS_DIR_M_TO_M )
    {
        LOC_errorStatus = DMA_WrongDirection;
    }
    else if((uint32_t)Memory_increment < DMA_MEM_INCR_OFF || (uint32_t)Memory_increment > DMA_MEM_INCR_ON)
    {
        LOC_errorStatus = DMA_WrongPointerModeMemory;
    }
    else if((uint32_t)Peripherial_increment < DMA_PERI_INCR_OFF || (uint32_t)Peripherial_increment > DMA_PERI_INCR_ON )
    {
        LOC_errorStatus = DMA_WrongPointerModePeripheral;
    }
    else if((uint32_t)priority < DMA_PRIORITY_LOW || (uint32_t)priority > DMA_PRIORITY_VHIGH)
    {
        LOC_errorStatus = DMA_WrongPriority;
    }
    else if(loc_assert_ch != DMA_CHN_SEL_ASSERT_MASK           &&
            loc_assert_msize != DMA_MEM_SIZE_ASSERT_MASK       &&
            loc_assert_psize != DMA_PERI_SIZE_ASSERT_MASK      &&
            loc_assert_direction != DMA_TRANS_DIR_ASSERT_MASK  &&
            loc_assert_Memory != DMA_MEM_INCR_ASSERT_MASK      &&
            loc_assert_Peri != DMA_PERI_INCR_ASSERT_MASK       &&
            loc_assert_Priority != DMA_PRIORITY_ASSERT_MASK     )
    {
        LOC_errorStatus = DMA_WrongReq;
    }   
    else
    {
        LOC_errorStatus = DMA_IsOk;
        loc_ch = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_ch &= ~ DMA_CHN_SEL_CLEARFLAG;
        loc_ch |= (uint32_t)channel;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_ch;

        loc_msize = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_msize &= ~DMA_MEM_SIZE_CLEAR_FLAG;
        loc_msize |= (uint32_t)msize;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_msize;

        loc_psize = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_psize &= ~DMA_PERI_SIZE_CLEAR_FLAG;
        loc_psize |= (uint32_t)psize;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_psize;

        loc_direction = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_direction &= ~DMA_TRANS_DIR_CLEAR_FLAG;
        loc_direction |= (uint32_t)direction;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_direction;

        loc_Memory_increment = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_Memory_increment &= ~DMA_MEM_INCR_CLEAR_FLAG;
        loc_Memory_increment |= (uint32_t)Memory_increment;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_Memory_increment;

        loc_Peripherial_increment = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_Peripherial_increment &= ~DMA_PERI_INCR_CLEAR_FLAG;
        loc_Peripherial_increment |= (uint32_t)Peripherial_increment;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_Peripherial_increment;

        loc_Priority = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_Priority &= ~ DMA_PRIORITY_CLEAR_FLAG;
        loc_Priority |= (uint32_t)priority;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_Priority;
    }
    return LOC_errorStatus;
}

DMA_errorStatus_t DMA_CTRL_MemoryBurst(void* dma, uint8_t stream, uint64_t memory_burst)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_memory_burst = memory_burst >> DMA_INPUT_ASSERT_OFFSET;
    uint32_t loc_memory_burst = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }
    else if((uint32_t)memory_burst < DMA_MEM_B_SINGLE || (uint32_t)memory_burst > DMA_MEM_B_INCR16)
    {
        LOC_errorStatus = DMA_WrongMemoryBurst;
    }
    else if(loc_assert_memory_burst != DMA_MEM_B_ASSERT_MASK)
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        loc_memory_burst = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_memory_burst &= ~ DMA_MEM_B_CLEARFLAG;
        loc_memory_burst |= (uint32_t) memory_burst;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_memory_burst;
    }
    return LOC_errorStatus;
}

DMA_errorStatus_t DMA_CTRL_PeriBurst(void* dma, uint8_t stream, uint64_t Peri_burst)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_Peri_burst = Peri_burst >> DMA_INPUT_ASSERT_OFFSET;
    uint32_t loc_Peri_burst = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }
    else if((uint32_t)Peri_burst < DMA_PERI_B_SINGLE || (uint32_t)Peri_burst > DMA_PERI_B_INCR16)
    {
        LOC_errorStatus = DMA_WrongPeriBurst;
    }
    else if(loc_assert_Peri_burst != DMA_PERI_B_ASSERT_MASK)
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        loc_Peri_burst = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_Peri_burst &= ~ DMA_PERI_B_CLEARFLAG;
        loc_Peri_burst |= (uint32_t) Peri_burst;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_Peri_burst;
    }
    return LOC_errorStatus;
}

DMA_errorStatus_t DMA_SEL_CurrentTarget(void* dma, uint8_t stream, uint64_t CT)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_CT_burst = CT >> DMA_INPUT_ASSERT_OFFSET;
    uint32_t loc_CT_burst = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }
    else if((uint32_t)CT < DMA_CT_MEM0 || (uint32_t)CT > DMA_CT_MEM1)
    {
        LOC_errorStatus = DMA_WrongCT;
    }
    else if(loc_assert_CT_burst != DMA_CT_ASSERT_MASK)
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        loc_CT_burst = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_CT_burst &= ~ DMA_CT_CLEAR_FLAG;
        loc_CT_burst |= (uint32_t)CT;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_CT_burst;
    }
    return LOC_errorStatus;
}


DMA_errorStatus_t DMA_GET_CurrentTarget(void* dma, uint8_t stream, uint32_t* CT)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;

    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }
    else if(CT == NULL)
    {
        LOC_errorStatus = DMA_NULLptr;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        *CT = ((((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR & DMA_CT_GET_FLAG);
    }
    return LOC_errorStatus;
}

DMA_errorStatus_t DMA_CFG_DoubleBuffer(void* dma, uint8_t stream, uint64_t DB)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_DB_burst = DB >> DMA_INPUT_ASSERT_OFFSET;
    uint32_t loc_DB_burst = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }
    else if((uint32_t)DB < DMA_DB_OFF || (uint32_t)DB > DMA_DB_ON)
    {
        LOC_errorStatus = DMA_WrongCT;
    }
    else if(loc_assert_DB_burst != DMA_DB_ASSERT_MASK)
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        loc_DB_burst = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_DB_burst &= ~ DMA_DB_CLEAR_FLAG;
        loc_DB_burst |= (uint32_t)DB;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_DB_burst;
    }
    return LOC_errorStatus;    
}

DMA_errorStatus_t DMA_SelectChannel(void* dma, uint8_t stream, uint64_t channel)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_ch = channel >> DMA_INPUT_ASSERT_OFFSET;
    uint32_t loc_ch = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }
    else if((uint32_t)channel < DMA_CHN_0 || (uint32_t)channel > DMA_CHN_7)
    {
        LOC_errorStatus = DMA_WrongChannel;
    }
    else if(loc_assert_ch != DMA_CHN_SEL_ASSERT_MASK )
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        loc_ch = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_ch &= ~ DMA_CHN_SEL_CLEARFLAG;
        loc_ch |= (uint32_t)channel;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_ch;
    }
    return LOC_errorStatus;
}
DMA_errorStatus_t DMA_SetDataSize(void* dma, uint8_t stream, uint64_t msize, uint64_t psize)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_msize = msize >> DMA_INPUT_ASSERT_OFFSET;
    uint8_t loc_assert_psize = psize >> DMA_INPUT_ASSERT_OFFSET;    

    uint32_t loc_msize = 0;
    uint32_t loc_psize = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }
    else if((uint32_t)msize < 0 || (uint32_t)msize > MAX_MEM_SIZE)
    {
        LOC_errorStatus = DMA_WrongMemorySize;
    }
    else if((uint32_t)psize < 0 || (uint32_t)psize > MAX_MEM_SIZE)
    {
        LOC_errorStatus = DMA_WrongPeripheralSize;
    }
    else if(loc_assert_msize != DMA_MEM_SIZE_ASSERT_MASK       &&
            loc_assert_psize != DMA_PERI_SIZE_ASSERT_MASK       )
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        loc_msize = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_msize &= ~DMA_MEM_SIZE_CLEAR_FLAG;
        loc_msize |= (uint32_t)msize;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_msize;

        loc_psize = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_psize &= ~DMA_PERI_SIZE_CLEAR_FLAG;
        loc_psize |= (uint32_t)psize;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_psize;
    }
    return LOC_errorStatus;
}

DMA_errorStatus_t DMA_SetDirection(void* dma, uint8_t stream, uint64_t direction)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_direction = direction >> DMA_INPUT_ASSERT_OFFSET;    
    uint32_t loc_direction = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }
    else if((uint32_t)direction < DMA_TRANS_DIR_P_TO_M  || (uint32_t)direction > DMA_TRANS_DIR_M_TO_M )
    {
        LOC_errorStatus = DMA_WrongDirection;
    }
    else if(loc_assert_direction != DMA_TRANS_DIR_ASSERT_MASK)
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        loc_direction = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_direction &= ~DMA_TRANS_DIR_CLEAR_FLAG;
        loc_direction |= (uint32_t)direction;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_direction;        
    }
    return LOC_errorStatus;
}

DMA_errorStatus_t DMA_SetTransferMode(void* dma, uint8_t stream, uint64_t Memory_increment, uint64_t Peripherial_increment)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_Memory = Memory_increment >> DMA_INPUT_ASSERT_OFFSET;
    uint8_t loc_assert_Peri = Peripherial_increment >> DMA_INPUT_ASSERT_OFFSET;

    uint32_t loc_Memory_increment = 0;
    uint32_t loc_Peripherial_increment = 0;

    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }    
    else if((uint32_t)Memory_increment < DMA_MEM_INCR_OFF || (uint32_t)Memory_increment > DMA_MEM_INCR_ON)
    {
        LOC_errorStatus = DMA_WrongPointerModeMemory;
    }
    else if((uint32_t)Peripherial_increment < DMA_PERI_INCR_OFF || (uint32_t)Peripherial_increment > DMA_PERI_INCR_ON )
    {
        LOC_errorStatus = DMA_WrongPointerModePeripheral;
    }   
    else if(loc_assert_Memory != DMA_MEM_INCR_ASSERT_MASK &&
            loc_assert_Peri != DMA_PERI_INCR_ASSERT_MASK   )
    {
        LOC_errorStatus = DMA_WrongReq;
    }   
    else
    {
        LOC_errorStatus = DMA_IsOk;

        loc_Memory_increment = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_Memory_increment &= ~DMA_MEM_INCR_CLEAR_FLAG;
        loc_Memory_increment |= (uint32_t)Memory_increment;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_Memory_increment;

        loc_Peripherial_increment = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_Peripherial_increment &= ~DMA_PERI_INCR_CLEAR_FLAG;
        loc_Peripherial_increment |= (uint32_t)Peripherial_increment;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_Peripherial_increment;

    }
    return LOC_errorStatus;
}

DMA_errorStatus_t DMA_SetStreamPriority(void* dma, uint8_t stream, uint64_t priority)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_Priority = priority >> DMA_INPUT_ASSERT_OFFSET;

    uint32_t loc_Priority = 0;    

    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    else if((uint32_t)priority < DMA_PRIORITY_LOW || (uint32_t)priority > DMA_PRIORITY_VHIGH)
    {
        LOC_errorStatus = DMA_WrongPriority;
    }
    else if(loc_assert_Priority != DMA_PRIORITY_ASSERT_MASK)
    {
        LOC_errorStatus = DMA_WrongReq;
    }      
    else
    {
        LOC_errorStatus = DMA_IsOk;

        loc_Priority = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_Priority &= ~ DMA_PRIORITY_CLEAR_FLAG;
        loc_Priority |= (uint32_t)priority;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_Priority;
    }
    return LOC_errorStatus;
}

DMA_errorStatus_t DMA_SetNumberOfDataItems(void* dma, uint8_t stream, uint64_t nItems)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_nItems = nItems >> DMA_INPUT_ASSERT_OFFSET;

    uint32_t loc_nItems = 0;    

    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    if((uint32_t)nItems < 0 || (uint32_t)nItems > MAX_NITEMS)
    {
        LOC_errorStatus = DMA_WrongNItems;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).NDTR = nItems;
    }
    return LOC_errorStatus;    
}

DMA_errorStatus_t DMA_SetDataAddress(void* dma, uint8_t stream, uint32_t* MemAddr, uint32_t* PeriAddr)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;  
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    else if(MemAddr == NULL)
    {
        LOC_errorStatus = DMA_NULLptr;
    }  
    else if(PeriAddr == NULL)
    {
        LOC_errorStatus = DMA_NULLptr;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).PAR = PeriAddr;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).M0AR = MemAddr;

    }
    return LOC_errorStatus;
}

DMA_errorStatus_t DMA_SetDataAddressDB(void* dma, uint8_t stream, uint32_t* Mem0Addr, uint32_t Mem1Addr ,uint32_t* PeriAddr)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;  
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    else if(Mem0Addr == NULL)
    {
        LOC_errorStatus = DMA_NULLptr;
    }  
    else if(Mem1Addr == NULL)
    {
        LOC_errorStatus = DMA_NULLptr;
    }
    else if(PeriAddr == NULL)
    {
        LOC_errorStatus = DMA_NULLptr;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).PAR = PeriAddr;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).M0AR = Mem0Addr;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).M1AR = Mem1Addr;

    }
    return LOC_errorStatus;    
}

DMA_errorStatus_t DMA_EnableStream(void* dma, uint8_t stream)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;    
    uint32_t loc_stream = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    else
    {
        LOC_errorStatus = DMA_IsOk;
        loc_stream = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_stream &= ~ DMA_STREMSTATE_CLEAR_FLAG;
        loc_stream |= (uint32_t)DMA_STREMSTATE_ENABLE;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_stream;

    }
    return LOC_errorStatus;    
}

DMA_errorStatus_t DMA_DisableStream(void* dma, uint8_t stream)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;    
    uint32_t loc_stream = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    else
    {
        LOC_errorStatus = DMA_IsOk;
        loc_stream = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_stream &= ~ DMA_STREMSTATE_CLEAR_FLAG;
        loc_stream |= (uint32_t)DMA_STREMSTATE_DISABLE;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_stream;

    }
    return LOC_errorStatus;       
}

DMA_errorStatus_t DMA_EnableIRQ(void* dma, uint8_t stream, uint64_t IRQ)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;    
    uint8_t loc_assert_IRQ = IRQ >> DMA_INPUT_ASSERT_OFFSET;
    uint32_t loc_IRQ = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    else if((uint32_t)IRQ < DMA_TCIE_FLAG || (uint32_t)IRQ > DMA_FIFO_EI_FLAG)
    {
        LOC_errorStatus = DMA_WrongIRQ;
    }
    else if(loc_assert_IRQ != DMA_INT_EN_DIS_ASSERT_H_MASK && loc_assert_IRQ != DMA_INT_EN_DIS_ASSERT_L_MASK )
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        switch(loc_assert_IRQ)
        {
            case DMA_GET_INT_STS_CLR_ASSERT_L_MASK:
                loc_IRQ = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
                loc_IRQ &= ~ (DMA_INT_STATE_CLEAR_FLAG<<IRQ);
                loc_IRQ |= (uint32_t)(DMA_INT_STATE_ENABLE<<IRQ);
                (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_IRQ;
                break;
            
            case DMA_GET_INT_STS_CLR_ASSERT_H_MASK:
                loc_IRQ = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).FCR;
                loc_IRQ &= ~ (DMA_INT_STATE_CLEAR_FLAG<<IRQ);
                loc_IRQ |= (uint32_t)(DMA_INT_STATE_ENABLE<<IRQ);
                (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).FCR = loc_IRQ;
                break;

            default:
                break;
        }


    }
    return LOC_errorStatus;       
}

DMA_errorStatus_t DMA_DisableIRQ(void* dma, uint8_t stream, uint64_t IRQ)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;    
    uint8_t loc_assert_IRQ = IRQ >> DMA_INPUT_ASSERT_OFFSET;
    uint32_t loc_IRQ = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    else if((uint32_t)IRQ < DMA_TCIE_FLAG || (uint32_t)IRQ > DMA_FIFO_EI_FLAG)
    {
        LOC_errorStatus = DMA_WrongIRQ;
    }
    else if(loc_assert_IRQ != DMA_INT_EN_DIS_ASSERT_H_MASK && loc_assert_IRQ != DMA_INT_EN_DIS_ASSERT_L_MASK )
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        switch(loc_assert_IRQ)
        {
            case DMA_GET_INT_STS_CLR_ASSERT_L_MASK:
                loc_IRQ = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
                loc_IRQ &= ~ (DMA_INT_STATE_CLEAR_FLAG<<IRQ);
                loc_IRQ |= (uint32_t)(DMA_INT_STATE_DISABLE<<IRQ);
                (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_IRQ;
                break;
            
            case DMA_GET_INT_STS_CLR_ASSERT_H_MASK:
                loc_IRQ = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).FCR;
                loc_IRQ &= ~ (DMA_INT_STATE_CLEAR_FLAG<<IRQ);
                loc_IRQ |= (uint32_t)(DMA_INT_STATE_DISABLE<<IRQ);
                (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).FCR = loc_IRQ;
                break;

            default:
                break;
        }


    }
    return LOC_errorStatus;        
}

DMA_errorStatus_t DMA_EnableCircularMode(void* dma, uint8_t stream)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint32_t loc_circular = 0;    

    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }       
    else
    {
        LOC_errorStatus = DMA_IsOk;

        loc_circular = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_circular &= ~ DMA_CIRC_CLEAR_FLAG;
        loc_circular |= (uint32_t)DMA_CIRC_ON;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_circular;
    }
    return LOC_errorStatus;    
}

DMA_errorStatus_t DMA_DisableCircularMode(void* dma, uint8_t stream)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint32_t loc_circular = 0;    

    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }       
    else
    {
        LOC_errorStatus = DMA_IsOk;

        loc_circular = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_circular &= ~ DMA_CIRC_CLEAR_FLAG;
        loc_circular |= (uint32_t)DMA_CIRC_OFF;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_circular;
    }
    return LOC_errorStatus;    
}

DMA_errorStatus_t DMA_SelectFlowController(void* dma, uint8_t stream, uint64_t flow_controller)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_flow_controller = flow_controller >> DMA_INPUT_ASSERT_OFFSET;

    uint32_t loc_flow_controller = 0;    

    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    else if((uint32_t)flow_controller < DMA_PERI_FLOW_DMA || (uint32_t)flow_controller > DMA_PERI_FLOW_PERI)
    {
        LOC_errorStatus = DMA_WrongFlowController;
    }
    else if(loc_assert_flow_controller != DMA_PRIORITY_ASSERT_MASK)
    {
        LOC_errorStatus = DMA_WrongReq;
    }      
    else
    {
        LOC_errorStatus = DMA_IsOk;

        loc_flow_controller = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR;
        loc_flow_controller &= ~ DMA_PERI_FLOW_CLEAR_FLAG;
        loc_flow_controller |= (uint32_t)flow_controller;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).CR = loc_flow_controller;
    }
    return LOC_errorStatus;    
}

DMA_errorStatus_t DMA_ClearLIFCRFlag(void* dma, uint8_t stream, uint64_t flag)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_flag = flag >> DMA_INPUT_ASSERT_OFFSET;

    uint32_t loc_flag = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    else if(loc_assert_flag != DMA_GET_INT_STS_CLR_ASSERT_L_MASK)
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        ((DMA_Peri_t*)dma)->LIFCR &= ~(uint32_t)flag;
    }
    return LOC_errorStatus;
}

DMA_errorStatus_t DMA_ClearHIFCRFlag(void* dma, uint8_t stream, uint64_t flag)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_flag = flag >> DMA_INPUT_ASSERT_OFFSET;

    uint32_t loc_flag = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    else if(loc_assert_flag != DMA_GET_INT_STS_CLR_ASSERT_H_MASK)
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        ((DMA_Peri_t*)dma)->HIFCR &= ~(uint32_t)flag;
    }   
    return LOC_errorStatus; 
}

DMA_errorStatus_t DMA_SetFIFOThreshold(void* dma, uint8_t stream, uint64_t fifo_th)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;
    uint8_t loc_assert_fifo_th = fifo_th >> DMA_INPUT_ASSERT_OFFSET;

    uint32_t loc_fifo_th = 0;
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }   
    else if(loc_assert_fifo_th != DMA_FIFO_THRES_ASSERT_MASK)
    {
        LOC_errorStatus = DMA_WrongReq;
    }
    else
    {
        LOC_errorStatus = DMA_IsOk;
        loc_fifo_th = (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).FCR;
        loc_fifo_th &= ~ DMA_PERI_FLOW_CLEAR_FLAG;
        loc_fifo_th |= (uint32_t)fifo_th;
        (((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).FCR = loc_fifo_th;
    }   
    return LOC_errorStatus;     
}

DMA_errorStatus_t DMA_GET_FIFO_Status(void *dma, uint8_t stream, uint8_t *Status)
{
    DMA_errorStatus_t LOC_errorStatus = DMA_IsNotOk;   
    if(stream < 0 || stream > DMA_MAX_STRM_NUM)
    {
        LOC_errorStatus = DMA_WrongStream;
    }  
    else if(Status == NULL)
    {
        LOC_errorStatus = DMA_NULLptr;
    } 
    else
    {
        LOC_errorStatus = DMA_IsOk;
        *Status = ((((DMA_Peri_t*)dma)->DMA_STRM_REG[stream]).FCR & DMA_FIFO_GET_FLAG);
    }
    return LOC_errorStatus;
}