#ifndef DRIVER_SOURCE_DMA_DRIVER_C_
#define DRIVER_SOURCE_DMA_DRIVER_C_

/********************************************************************************************************/
/************************************************Includes************************************************/
/********************************************************************************************************/
#include <stdint.h> 
/********************************************************************************************************/
/************************************************Defines*************************************************/
/********************************************************************************************************/
#define DMA_1 (void * )0x40026000
#define DMA_2 (void * )0x40026400

#define DMA_STRM_0 0
#define DMA_STRM_1 1
#define DMA_STRM_2 2
#define DMA_STRM_3 3
#define DMA_STRM_4 4
#define DMA_STRM_5 5
#define DMA_STRM_6 6
#define DMA_STRM_7 7

#define DMA_STREMSTATE_DISABLE 0x4000000000
#define DMA_STREMSTATE_ENABLE  0x4000000001

#define DMA_STRM_0_TRANS_COMP_FLAG 0x0100000020
#define DMA_STRM_1_TRANS_COMP_FLAG 0x0100000800
#define DMA_STRM_2_TRANS_COMP_FLAG 0x0100200000
#define DMA_STRM_3_TRANS_COMP_FLAG 0x0108000000
#define DMA_STRM_4_TRANS_COMP_FLAG 0x0200000020
#define DMA_STRM_5_TRANS_COMP_FLAG 0x0200000800
#define DMA_STRM_6_TRANS_COMP_FLAG 0x0200200000
#define DMA_STRM_7_TRANS_COMP_FLAG 0x0208000000

#define DMA_STRM_0_H_TRANS_COMP_FLAG 0x0100000010
#define DMA_STRM_1_H_TRANS_COMP_FLAG 0x0100000400
#define DMA_STRM_2_H_TRANS_COMP_FLAG 0x0100100000
#define DMA_STRM_3_H_TRANS_COMP_FLAG 0x0104000000
#define DMA_STRM_4_H_TRANS_COMP_FLAG 0x0200000010
#define DMA_STRM_5_H_TRANS_COMP_FLAG 0x0200000400
#define DMA_STRM_6_H_TRANS_COMP_FLAG 0x0200100000
#define DMA_STRM_7_H_TRANS_COMP_FLAG 0x0204000000

#define DMA_STRM_0_TRANS_ERR_FLAG 0x0100000004
#define DMA_STRM_1_TRANS_ERR_FLAG 0x0100000200
#define DMA_STRM_2_TRANS_ERR_FLAG 0x0100080000
#define DMA_STRM_3_TRANS_ERR_FLAG 0x0102000000
#define DMA_STRM_4_TRANS_ERR_FLAG 0x0200000004
#define DMA_STRM_5_TRANS_ERR_FLAG 0x0200000200
#define DMA_STRM_6_TRANS_ERR_FLAG 0x0200080000
#define DMA_STRM_7_TRANS_ERR_FLAG 0x0202000000

#define DMA_STRM_0_DIRM_ERR_FLAG 0x0100000002
#define DMA_STRM_1_DIRM_ERR_FLAG 0x0100000100
#define DMA_STRM_2_DIRM_ERR_FLAG 0x0100040000
#define DMA_STRM_3_DIRM_ERR_FLAG 0x0101000000
#define DMA_STRM_4_DIRM_ERR_FLAG 0x0200000002
#define DMA_STRM_5_DIRM_ERR_FLAG 0x0200000100
#define DMA_STRM_6_DIRM_ERR_FLAG 0x0200040000
#define DMA_STRM_7_DIRM_ERR_FLAG 0x0201000000

#define DMA_STRM_0_FIFO_ERR_FLAG 0x0100000001
#define DMA_STRM_1_FIFO_ERR_FLAG 0x0100000040
#define DMA_STRM_2_FIFO_ERR_FLAG 0x0100010000
#define DMA_STRM_3_FIFO_ERR_FLAG 0x0100400000
#define DMA_STRM_4_FIFO_ERR_FLAG 0x0200000001
#define DMA_STRM_5_FIFO_ERR_FLAG 0x0200000040
#define DMA_STRM_6_FIFO_ERR_FLAG 0x0200010000
#define DMA_STRM_7_FIFO_ERR_FLAG 0x0200400000

#define DMA_TCIE_FLAG    0x2000000008
#define DMA_HTIE_FLAG    0x2000000004
#define DMA_TEIE_FLAG    0x2000000002
#define DMA_DMEIE_FLAG   0x2000000001
#define DMA_FIFO_EI_FLAG 0x3000000008

#define DMA_INT_STATE_ENABLE 1
#define DMA_INT_STATE_DISABLE 0

#define DMA_CHN_0 0x0300000000
#define DMA_CHN_1 0x0302000000
#define DMA_CHN_2 0x0304000000
#define DMA_CHN_3 0x0306000000
#define DMA_CHN_4 0x0308000000
#define DMA_CHN_5 0x030A000000
#define DMA_CHN_6 0x030C000000
#define DMA_CHN_7 0x030E000000

#define DMA_MEM_B_SINGLE 0x0400000000
#define DMA_MEM_B_INCR4  0x0400800000
#define DMA_MEM_B_INCR8  0x0401000000
#define DMA_MEM_B_INCR16 0x0403000000

#define DMA_PERI_B_SINGLE 0x0500000000
#define DMA_PERI_B_INCR4  0x0500200000
#define DMA_PERI_B_INCR8  0x0500400000
#define DMA_PERI_B_INCR16 0x0500600000

#define DMA_CT_MEM0 0x0600000000
#define DMA_CT_MEM1 0x0600080000

#define DMA_DB_OFF 0x0700000000
#define DMA_DB_ON  0x0700040000

#define DMA_PRIORITY_LOW  0x0800000000
#define DMA_PRIORITY_MED  0x0800010000
#define DMA_PRIORITY_HIGH 0x0800020000
#define DMA_PRIORITY_VHIGH 0x0800030000

#define DMA_PINCOS_PSIZE 0x0900000000
#define DMA_PINCOS_FIXED 0x0900008000

#define DMA_MEM_SIZE_BYTE  0x0A00000000
#define DMA_MEM_SIZE_HWORD 0x0A00002000
#define DMA_MEM_SIZE_WORD  0x0A00004000

#define DMA_PERI_SIZE_BYTE  0x0B00000000
#define DMA_PERI_SIZE_HWORD 0x0B00000800
#define DMA_PERI_SIZE_WORD  0x0B00001000

#define DMA_MEM_INCR_OFF 0x0C00000000
#define DMA_MEM_INCR_ON  0x0C00000400

#define DMA_PERI_INCR_OFF 0x0D00000000
#define DMA_PERI_INCR_ON  0x0D00000200

#define DMA_CIRC_OFF 0x0E00000000
#define DMA_CIRC_ON  0x0E00000100

#define DMA_TRANS_DIR_P_TO_M 0x0F00000000
#define DMA_TRANS_DIR_M_TO_P 0x0F00000040
#define DMA_TRANS_DIR_M_TO_M 0x0F00000080

#define DMA_PERI_FLOW_DMA  0x1000000000
#define DMA_PERI_FLOW_PERI 0x1000000020

#define DMA_DIR_MODE_ENABLE  0x5000000000
#define DMA_DIR_MODE_DISABLE 0x5000000004

#define DMA_FIFO_THRES_1_4  0x6000000000
#define DMA_FIFO_THRES_1_2  0x6000000001
#define DMA_FIFO_THRES_3_4  0x6000000002
#define DMA_FIFO_THRES_FULL 0x6000000003
/********************************************************************************************************/
/************************************************Types***************************************************/
/********************************************************************************************************/

typedef enum{
    DMA_WrongStream,
    DMA_WrongChannel,
    DMA_WrongMemorySize,
    DMA_WrongDirection,
    DMA_WrongPointerModeMemory,
    DMA_WrongPointerModePeripheral,
    DMA_WrongPriority,
    DMA_WrongPeripheralSize,
    DMA_WrongNItems,
    DMA_NULLptr,
    DMA_WrongFlowController,
    DMA_WrongFlag,
    DMA_WrongFIFOThreshold,
    DMA_IsOk,
    DMA_IsNotOk,
    DMA_WrongReq,
    DMA_WrongMemoryBurst,
    DMA_WrongPeriBurst,
    DMA_WrongCT,
    DMA_WrongNItems,
    DMA_WrongIRQ,
    DMA_WrongFlag

}DMA_errorStatus_t;
/********************************************************************************************************/
/************************************************APIs****************************************************/
/********************************************************************************************************/

DMA_errorStatus_t DMA_StreamInit(void* dma, uint8_t stream, uint64_t channel, uint64_t msize, uint64_t psize, uint64_t direction, uint64_t Memory_increment, uint64_t Peripherial_increment , uint64_t priority);
DMA_errorStatus_t DMA_CTRL_MemoryBurst(void* dma, uint8_t stream, uint64_t memory_burst);
DMA_errorStatus_t DMA_CTRL_PeriBurst(void* dma, uint8_t stream, uint64_t Peri_burst);
DMA_errorStatus_t DMA_SEL_CurrentTarget(void* dma, uint8_t stream, uint64_t CT);
DMA_errorStatus_t DMA_GET_CurrentTarget(void* dma, uint8_t stream, uint32_t* CT);
DMA_errorStatus_t DMA_CFG_DoubleBuffer(void* dma, uint8_t stream, uint64_t DB);
DMA_errorStatus_t DMA_SelectChannel(void* dma, uint8_t stream, uint64_t channel);
DMA_errorStatus_t DMA_SetDataSize(void* dma, uint8_t stream, uint64_t msize, uint64_t psize);
DMA_errorStatus_t DMA_SetDirection(void* dma, uint8_t stream, uint64_t direction);
DMA_errorStatus_t DMA_SetTransferMode(void* dma, uint8_t stream, uint64_t Memory_increment, uint64_t Peripherial_increment);
DMA_errorStatus_t DMA_SetStreamPriority(void* dma, uint8_t stream, uint64_t priority);
DMA_errorStatus_t DMA_SetNumberOfDataItems(void* dma, uint8_t stream, uint64_t nItems);
DMA_errorStatus_t DMA_SetDataAddress(void* dma, uint8_t stream, uint32_t* MemAddr, uint32_t* PeriAddr);
DMA_errorStatus_t DMA_SetDataAddressDB(void* dma, uint8_t stream, uint32_t* Mem0Addr, uint32_t Mem1Addr ,uint32_t* PeriAddr);
DMA_errorStatus_t DMA_EnableStream(void* dma, uint8_t stream);
DMA_errorStatus_t DMA_DisableStream(void* dma, uint8_t stream);
DMA_errorStatus_t DMA_EnableIRQ(void* dma, uint8_t stream, uint64_t IRQ);
DMA_errorStatus_t DMA_DisableIRQ(void* dma, uint8_t stream, uint64_t IRQ);
DMA_errorStatus_t DMA_EnableCircularMode(void* dma, uint8_t stream);
DMA_errorStatus_t DMA_DisableCircularMode(void* dma, uint8_t stream);
DMA_errorStatus_t DMA_SelectFlowController(void* dma, uint8_t stream, uint64_t flow_controller);
DMA_errorStatus_t DMA_ClearLIFCRFlag(void* dma, uint8_t stream, uint64_t flag);
DMA_errorStatus_t DMA_ClearHIFCRFlag(void* dma, uint8_t stream, uint64_t flag);
DMA_errorStatus_t DMA_SetFIFOThreshold(void* dma, uint8_t stream, uint64_t fifo_th);
DMA_errorStatus_t DMA_GET_FIFO_Status(void *dma, uint8_t stream, uint8_t *Status);
#endif // DRIVER_SOURCE_DMA_DRIVER_C_