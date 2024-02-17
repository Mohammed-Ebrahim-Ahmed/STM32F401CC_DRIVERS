/*******************************************************************includes******************************************************************/
#include "RCC.h"

/*********************************************************************************************************************************************/

/********************************************************************defines******************************************************************/
#define RCC ((volatile RCC_Peri_t* const)0x40023800)

#define PLLQ_MASK 0xF000000
#define PLLP_MASK 0x30000
#define PLLN_MASK 0x7FC0
#define PLLM_MASK 0x1F
#define PLLSOURCE_MASK 0x400000

#define SELSYSCLK_MASK 0x3
#define RETSYSCLK_MASK 0xC

#define PLLRDY 0x2000000
#define HSERDY 0x20000
#define HSIRDY 0x2

#define Q_SHIFT 24
#define P_SHIFT 16
#define N_SHIFT 6
#define M_SHIFT 0

#define MCO2_SOURCE_MASK 0xC0000000
#define MCO2_PRE_MASK    0x38000000

#define MCO1_SOURCE_MASK 0x600000
#define MCO1_PRE_MASK    0x7000000

#define APB2_PRE_MASK 0xE000

#define APB1_PRE_MASK 0x1C00

#define AHB_PRE_MASK  0xF0
/*********************************************************************************************************************************************/

/*********************************************************************types*******************************************************************/

typedef struct{
    uint32_t RCC_CR;
    uint32_t RCC_PLLCFGR;
    uint32_t RCC_CFGR;
    uint32_t RCC_CIR;
    uint32_t RCC_AHB1RSTR;
    uint32_t RCC_AHB2RSTR;
    uint32_t RESERVED_1;
    uint32_t RESERVED_2;
    uint32_t RCC_APB1RSTR;
    uint32_t RCC_APB2RSTR;
    uint32_t RESERVED_3;
    uint32_t RESERVED_4;
    uint32_t RCC_AHB1ENR;
    uint32_t RCC_AHB2ENR;
    uint32_t RESERVED_5;
    uint32_t RESERVED_6;
    uint32_t RCC_APB1ENR;
    uint32_t RCC_APB2ENR;
    uint32_t RESERVED_7;
    uint32_t RESERVED_8;
    uint32_t RCC_AHB1LPENR;
    uint32_t RCC_AHB2LPENR;
    uint32_t RESERVED_9;
    uint32_t RESERVED_10;
    uint32_t RCC_APB1LPENR;
    uint32_t RCC_APB2LPENR;
    uint32_t RESERVED_11;
    uint32_t RESERVED_12;
    uint32_t RCC_BDCR;
    uint32_t RCC_CSR;
    uint32_t RESERVED_13;
    uint32_t RESERVED_14;
    uint32_t RCC_SSCGR;
    uint32_t RCC_PLLI2SCFGR;
    uint32_t RESERVED_15;
    uint32_t RCC_DCKCFGR;

}RCC_Peri_t;

/*********************************************************************************************************************************************/

/********************************************************************variables****************************************************************/



/*********************************************************************************************************************************************/

/**************************************************************static_function_prototyes******************************************************/


/*********************************************************************************************************************************************/

/***********************************************************************APIs******************************************************************/

RCC_WrongConfig_t RCC_enableClock(uint32_t CLKEnable)
{
    RCC_WrongConfig_t LOC_ErrorStatus = RCC_isNotOk;
    uint16_t timeout = 6000;
    if((CLKEnable != RCC_CLKENABLEPLL) && (CLKEnable != RCC_CLKENABLEHSE) && (CLKEnable != RCC_CLKENABLEHSI))
    {
        LOC_ErrorStatus = RCC_Wrong_CLK_Option;
    }
    else
    {
        LOC_ErrorStatus = RCC_isOk;
        if(CLKEnable == RCC_CLKENABLEPLL)
        {
            RCC->RCC_CR |= RCC_CLKENABLEPLL;
            while(((RCC->RCC_CR & PLLRDY) != PLLRDY) && timeout)
            {
                timeout--;
            }
        }
        else if(CLKEnable == RCC_CLKENABLEHSE)
        {
            RCC->RCC_CR |= RCC_CLKENABLEHSE;
            while(((RCC->RCC_CR & HSERDY) != HSERDY) && timeout)
            {
                timeout--;
            }           
        }
        else if(CLKEnable == RCC_CLKENABLEHSI )
        {
            RCC->RCC_CR |= RCC_CLKENABLEHSI;
            while(((RCC->RCC_CR & HSIRDY) != HSIRDY) && timeout)
            {
                timeout--;
            }              
        }
        else
        {
            LOC_ErrorStatus = RCC_isNotOk;
        }
    }
    return LOC_ErrorStatus;
}

RCC_WrongConfig_t RCC_disableClock(uint32_t CLKEnable)
{
    RCC_WrongConfig_t LOC_ErrorStatus = RCC_isNotOk;
    uint16_t timeout = 6000;
    if(CLKEnable != RCC_CLKENABLEPLL && CLKEnable != RCC_CLKENABLEHSE && CLKEnable != RCC_CLKENABLEHSI)
    {
        LOC_ErrorStatus = RCC_Wrong_CLK_Option;
    }
    else
    {
        LOC_ErrorStatus = RCC_isOk;
        if(CLKEnable == RCC_CLKENABLEPLL)
        {
            RCC->RCC_CR &= (~RCC_CLKENABLEPLL) ;
            while(((RCC->RCC_CR & (~PLLRDY)) != (~PLLRDY)) && timeout)
            {
                timeout--;
            }
        }
        else if(CLKEnable == RCC_CLKENABLEHSE)
        {
            RCC->RCC_CR &= (~RCC_CLKENABLEHSE);
            while(((RCC->RCC_CR & (~HSERDY)) != (~HSERDY)) && timeout)
            {
                timeout--;
            }           
        }
        else if(CLKEnable == RCC_CLKENABLEHSI )
        {
            RCC->RCC_CR &= (~RCC_CLKENABLEHSI);
            while(((RCC->RCC_CR | (~HSIRDY)) != (~HSIRDY)) && timeout)
            {
                timeout--;
            }              
        }
        else
        {
            LOC_ErrorStatus = RCC_isNotOk;
        }
    }
    return LOC_ErrorStatus;
}
RCC_WrongConfig_t RCC_selectSYSCLK(uint32_t SYSCLKOption)
{
    uint32_t temp = 0;
    RCC_WrongConfig_t LOC_ErrorStatus = RCC_isNotOk; 
    if(SYSCLKOption != RCC_SYSCLK_HSI && SYSCLKOption != RCC_SYSCLK_HSE && SYSCLKOption != RCC_SYSCLK_PLL)
    {
        LOC_ErrorStatus = RCC_Wrong_CLK_Option;
    }
    else
    {
        LOC_ErrorStatus = RCC_isOk; 
        temp = RCC->RCC_CFGR;
        temp &= ~ SELSYSCLK_MASK;
        temp |= SYSCLKOption;
        RCC->RCC_CFGR = temp; 
        /*
        if(SYSCLKOption == RCC_SYSCLK_HSI)
        {
            temp = RCC->RCC_CFGR;
            temp &= ~ RCC_SYSCLK_HSI;
            temp |= RCC_SYSCLK_HSI;
            RCC->RCC_CFGR = temp; 
        }
        else if (SYSCLKOption == RCC_SYSCLK_HSE)
        {
            temp = RCC->RCC_CFGR;
            temp &= ~ RCC_SYSCLK_HSE;
            temp |= RCC_SYSCLK_HSE;
            RCC->RCC_CFGR = temp;             
        }
        else if(SYSCLKOption == RCC_SYSCLK_PLL)
        {
            temp = RCC->RCC_CFGR;
            temp &= ~ RCC_SYSCLK_PLL;
            temp |= RCC_SYSCLK_PLL;
            RCC->RCC_CFGR = temp;              
        }
        else
        {
            LOC_ErrorStatus = RCC_isNotOk;
        }
        */
    }
    return LOC_ErrorStatus;
}

uint32_t RCC_getSYSCLK(void)
{   /*
    uint32_t LOC_SYSCLK = -1;
    
    if((RETSYSCLK_MASK & RCC->RCC_CFGR) == RCC_SYSCLKRETURN_HSI)
    {
        LOC_SYSCLK = RCC_SYSCLKRETURN_HSI;
    }
    else if((RETSYSCLK_MASK & RCC->RCC_CFGR) == RCC_SYSCLKRETURN_HSE)
    {
        LOC_SYSCLK = RCC_SYSCLKRETURN_HSE;
    }
    else if((RETSYSCLK_MASK & RCC->RCC_CFGR) == RCC_SYSCLKRETURN_PLL)
    {
        LOC_SYSCLK = RCC_SYSCLKRETURN_PLL;
    }
    else
    {
        LOC_SYSCLK = -1;
    }
    */
    return (RETSYSCLK_MASK & RCC->RCC_CFGR);
}

RCC_WrongConfig_t RCC_enableAHBPeriCLK(uint32_t AHBPeriOption)
{
    RCC_WrongConfig_t LOC_ErrorStatus = RCC_isNotOk;

    if((AHBPeriOption != RCC_AHB1_DMA2)  &&
       (AHBPeriOption != RCC_AHB1_DMA1)  &&
       (AHBPeriOption != RCC_AHB1_CRCEN) &&                               
       (AHBPeriOption != RCC_AHB1_GPIOH) &&
       (AHBPeriOption != RCC_AHB1_GPIOE) &&
       (AHBPeriOption != RCC_AHB1_GPIOD) &&
       (AHBPeriOption != RCC_AHB1_GPIOC) &&
       (AHBPeriOption != RCC_AHB1_GPIOB) &&
       (AHBPeriOption != RCC_AHB1_GPIOA) &&
       (AHBPeriOption != RCC_AHB2_OTGFS)  )
    {
        LOC_ErrorStatus = RCC_WrongAHBPeri;
    }
    else
    {
        LOC_ErrorStatus = RCC_isOk;
        if(AHBPeriOption == RCC_AHB2_OTGFS)
        {
            RCC->RCC_AHB2ENR |= AHBPeriOption;
        }
        else
        {
            RCC->RCC_AHB1ENR |= AHBPeriOption;
        }
    }
    return LOC_ErrorStatus;
}

RCC_WrongConfig_t RCC_enableAPBPeriCLK(uint32_t APBPeriOption)
{
    RCC_WrongConfig_t LOC_ErrorStatus = RCC_isNotOk;

    if((APBPeriOption != RCC_APB1_PWR)     &&
       (APBPeriOption != RCC_APB1_I2C3)    &&
       (APBPeriOption != RCC_APB1_I2C2)    &&
       (APBPeriOption != RCC_APB1_I2C1)    &&
       (APBPeriOption != RCC_APB1_USART2)  &&
       (APBPeriOption != RCC_APB1_SPI3)    &&
       (APBPeriOption != RCC_APB1_SPI2)    &&
       (APBPeriOption != RCC_APB1_WWDG)    &&
       (APBPeriOption != RCC_APB1_TIM5)    &&
       (APBPeriOption != RCC_APB1_TIM4)    &&
       (APBPeriOption != RCC_APB1_TIM3)    &&
       (APBPeriOption != RCC_APB1_TIM2)    &&
       (APBPeriOption != RCC_APB2_TIM11)   &&
       (APBPeriOption != RCC_APB2_TIM10)   &&
       (APBPeriOption != RCC_APB2_TIM9)    &&
       (APBPeriOption != RCC_APB2_SYSCFG)  &&
       (APBPeriOption != RCC_APB2_SPI4)    &&
       (APBPeriOption != RCC_APB2_SPI1)    &&
       (APBPeriOption != RCC_APB2_SDIO)    &&
       (APBPeriOption != RCC_APB2_ADC1)    &&
       (APBPeriOption != RCC_APB2_USART6)  &&
       (APBPeriOption != RCC_APB2_USART1)  &&
       (APBPeriOption != RCC_APB2_TIM1)     )
    {
        LOC_ErrorStatus = RCC_WrongAPBPeri;
    }
    else
    {
        LOC_ErrorStatus = RCC_isOk;

        if( (APBPeriOption == RCC_APB2_TIM11)   &&
            (APBPeriOption == RCC_APB2_TIM10)   &&
            (APBPeriOption == RCC_APB2_TIM9)    &&
            (APBPeriOption == RCC_APB2_SYSCFG)  &&
            (APBPeriOption == RCC_APB2_SPI4)    &&
            (APBPeriOption == RCC_APB2_SPI1)    &&
            (APBPeriOption == RCC_APB2_SDIO)    &&
            (APBPeriOption == RCC_APB2_ADC1)    &&
            (APBPeriOption == RCC_APB2_USART6)  &&
            (APBPeriOption == RCC_APB2_USART1)  &&
            (APBPeriOption == RCC_APB2_TIM1)     )
        {
            RCC->RCC_APB2ENR |= APBPeriOption;
        }
        else
        {
            RCC->RCC_APB1ENR |= APBPeriOption;
        }

    }
    return LOC_ErrorStatus;
}

RCC_WrongPLLConfig_t RCC_selectPLLCLK( uint32_t RCC_PLLCLKSource)
{
    RCC_WrongPLLConfig_t LOC_ErrorStatus = RCC_PLLNotOk;
    if((RCC_PLLCLKSource != RCC_PLL_CLKSOURCEHSI) && (RCC_PLLCLKSource != RCC_PLL_CLKSOURCEHSE) )
    {
        LOC_ErrorStatus = RCC_WrongPLLCLKSource;
    }
    else
    {
        LOC_ErrorStatus = RCC_PLLOk;
        if(RCC_PLLCLKSource == RCC_PLL_CLKSOURCEHSE)
        {
            RCC->RCC_PLLCFGR |= RCC_PLL_CLKSOURCEHSE;
        }
        else
        {
            RCC->RCC_PLLCFGR &= ~PLLSOURCE_MASK;
        }

    }
    return LOC_ErrorStatus;
}

RCC_WrongPLLConfig_t RCC_configurePLLCLK( uint32_t M, uint32_t N, uint32_t P, uint32_t Q)
{
    volatile uint32_t temp = 0;
    RCC_WrongPLLConfig_t LOC_ErrorStatus = RCC_PLLNotOk;
    if(M < 2 || M > 63)
    {
        LOC_ErrorStatus = RCC_WrongPLL_M_value;
    }
    else if (N < 192 || N > 432)
    {
        LOC_ErrorStatus = RCC_WrongPLL_N_value;
    }
    else if (P != 2 && P != 4 && P != 6 && P != 8)
    {
        LOC_ErrorStatus = RCC_WrongPLL_P_value;
    }
    else if( Q < 2 || Q > 15)
    {
        LOC_ErrorStatus = RCC_WrongPLL_Q_value;
    }
    else
    {
        LOC_ErrorStatus = RCC_PLLOk;
        
        temp = RCC->RCC_PLLCFGR;
        temp &= ~(PLLQ_MASK);
        temp |= (Q << Q_SHIFT);
        RCC->RCC_PLLCFGR = temp;

        temp = RCC->RCC_PLLCFGR;
        temp &= ~(PLLP_MASK);
        temp |= (P << P_SHIFT);
        RCC->RCC_PLLCFGR = temp;

        temp = RCC->RCC_PLLCFGR;
        temp &= ~(PLLN_MASK);
        temp |= (N << N_SHIFT);
        RCC->RCC_PLLCFGR = temp;

        temp = RCC->RCC_PLLCFGR;
        temp &= ~(PLLM_MASK);
        temp |= (M << M_SHIFT);
        RCC->RCC_PLLCFGR = temp;
        
    }
    return LOC_ErrorStatus;
}

RCC_WrongConfig_t RCC_configMCO2(uint32_t MCO2_SOURCE, uint32_t MCO2_PRE)
{
    uint32_t temp = 0;
    RCC_WrongConfig_t LOC_ErrorStatus = RCC_isNotOk;

    if( (MCO2_SOURCE != MCO2_SOURCE_SYSCLK) &&
        (MCO2_SOURCE != MCO2_SOURCE_PLLI2S) &&
        (MCO2_SOURCE != MCO2_SOURCE_HSE)    &&
        (MCO2_SOURCE != MCO2_SOURCE_PLL)     )
    {
        LOC_ErrorStatus = RCC_WrongMCO2Source;
    }
    else if((MCO2_PRE != MCO2_PRE_1) &&
            (MCO2_PRE != MCO2_PRE_2) &&
            (MCO2_PRE != MCO2_PRE_3) &&
            (MCO2_PRE != MCO2_PRE_4) &&
            (MCO2_PRE != MCO2_PRE_5)  )
    {
        LOC_ErrorStatus = RCC_WrongMCO2PRE;
    }
    else
    {
        LOC_ErrorStatus = RCC_isOk;
        temp = RCC->RCC_CFGR;
        temp &= (~MCO2_SOURCE_MASK);
        temp |= MCO2_SOURCE;
        temp &= (~MCO2_PRE_MASK);
        temp |= MCO2_PRE;
        RCC->RCC_CFGR = temp;
    }
    return LOC_ErrorStatus;
}

RCC_WrongConfig_t RCC_configMCO1(uint32_t MCO1_SOURCE, uint32_t MCO1_PRE)
{
    uint32_t temp = 0;
    RCC_WrongConfig_t LOC_ErrorStatus = RCC_isNotOk;

    if( (MCO1_SOURCE != MCO1_SOURCE_HSI) &&
        (MCO1_SOURCE != MCO1_SOURCE_LSE) &&
        (MCO1_SOURCE != MCO1_SOURCE_HSE) &&
        (MCO1_SOURCE != MCO1_SOURCE_PLL)  )
    {
        LOC_ErrorStatus = RCC_WrongMCO1Source;
    }
    else if((MCO1_PRE != MCO1_PRE_1) &&
            (MCO1_PRE != MCO1_PRE_2) &&
            (MCO1_PRE != MCO1_PRE_3) &&
            (MCO1_PRE != MCO1_PRE_4) &&
            (MCO1_PRE != MCO1_PRE_5)  )
    {
        LOC_ErrorStatus = RCC_WrongMCO1PRE;
    }
    else
    {
        LOC_ErrorStatus = RCC_isOk;
        temp = RCC->RCC_CFGR;
        temp &= (~MCO1_SOURCE_MASK);
        temp |= MCO1_SOURCE;
        temp &= (~MCO1_PRE_MASK);
        temp |= MCO1_PRE;
        RCC->RCC_CFGR = temp;
    }
    return LOC_ErrorStatus;
}

RCC_WrongConfig_t RCC_ConfigAPB1PRE(uint32_t APB1_PRE)
{
    uint32_t temp = 0;
    RCC_WrongConfig_t LOC_ErrorStatus = RCC_isNotOk; 
    if( (APB1_PRE != APB1_PRE_1) &&
        (APB1_PRE != APB1_PRE_2) &&
        (APB1_PRE != APB1_PRE_4) &&
        (APB1_PRE != APB1_PRE_8) &&
        (APB1_PRE != APB1_PRE_16) )
    {
        LOC_ErrorStatus = RCC_WrongAPB1_Prescaler;
    }
    else
    {
       LOC_ErrorStatus = RCC_isOk; 
       temp = RCC->RCC_CFGR;
       temp &= (~APB1_PRE_MASK);
       temp |= (APB1_PRE);
       RCC->RCC_CFGR = temp;
    }   
    return LOC_ErrorStatus;
}

RCC_WrongConfig_t RCC_ConfigAPB2PRE(uint32_t APB2_PRE)
{
    uint32_t temp = 0;
    RCC_WrongConfig_t LOC_ErrorStatus = RCC_isNotOk; 
    if( (APB2_PRE != APB2_PRE_1) &&
        (APB2_PRE != APB2_PRE_2) &&
        (APB2_PRE != APB2_PRE_4) &&
        (APB2_PRE != APB2_PRE_8) &&
        (APB2_PRE != APB2_PRE_16) )
    {
        LOC_ErrorStatus = RCC_WrongAPB2_Prescaler;
    }
    else
    {
       LOC_ErrorStatus = RCC_isOk; 
       temp = RCC->RCC_CFGR;
       temp &= (~APB2_PRE_MASK);
       temp |= (APB2_PRE);
       RCC->RCC_CFGR = temp;
    }   
    return LOC_ErrorStatus;
}

RCC_WrongConfig_t RCC_ConfigAHBPRE(uint32_t AHB_PRE)
{
    uint32_t temp = 0;
    RCC_WrongConfig_t LOC_ErrorStatus = RCC_isNotOk; 
    if( (AHB_PRE != AHB_PRE_1)  &&
        (AHB_PRE != AHB_PRE_2)  &&
        (AHB_PRE != AHB_PRE_4)  &&
        (AHB_PRE != AHB_PRE_8)  &&
        (AHB_PRE != AHB_PRE_16) &&
        (AHB_PRE != AHB_PRE_64) &&
        (AHB_PRE != AHB_PRE_128)&&
        (AHB_PRE != AHB_PRE_256)&&
        (AHB_PRE != AHB_PRE_512) )
    {
        LOC_ErrorStatus = RCC_WrongAHB_Prescaler;
    }
    else
    {
       LOC_ErrorStatus = RCC_isOk; 
       temp = RCC->RCC_CFGR;
       temp &= (~AHB_PRE_MASK);
       temp |= (AHB_PRE);
       RCC->RCC_CFGR = temp;
    }   
    return LOC_ErrorStatus;    
}

/*********************************************************************************************************************************************/