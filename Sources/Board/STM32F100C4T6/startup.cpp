#pragma language = extended
#pragma segment = "CSTACK"

extern "C" void __program_start(void);

#include "NVIC_Classes.h"

typedef void (*intfunc)(void);
typedef union
{
    intfunc __fun;
    void *__ptr;
} intvec_elem;

#pragma location = ".intvec"
extern "C" const intvec_elem __vector_table[] =
    {
        {.__ptr = __sfe("CSTACK")},
        __program_start,

        NMI::Handler,
        HardFault::Handler,
        MemManage::Handler,
        BusFault::Handler,
        UsageFault::Handler,
        0,
        0,
        0,
        0,
        SVC::Handler,
        DebugMon::Handler,
        0,
        PendSV::Handler,
        SystemTick::Handler,

        /////////////////////////////
        //// External Interrupts ////
        /////////////////////////////
        WWDG_IRQ::Handler,
        PVD_IRQ::Handler,
        TAMPER_IRQ::Handler,
        RTC_IRQ::Handler,
        FLASH_IRQ::Handler,
        RCC_IRQ::Handler,
        EXTI0_IRQ::Handler,
        EXTI1_IRQ::Handler,
        EXTI2_IRQ::Handler,
        EXTI3_IRQ::Handler,
        EXTI4_IRQ::Handler,
        DMA1_Channel1_IRQ::Handler,
        DMA1_Channel2_IRQ::Handler,
        DMA1_Channel3_IRQ::Handler,
        DMA1_Channel4_IRQ::Handler,
        DMA1_Channel5_IRQ::Handler,
        DMA1_Channel6_IRQ::Handler,
        DMA1_Channel7_IRQ::Handler,
        ADC1_IRQ::Handler,
        0,
        0,
        0,
        0,
        EXTI9_5_IRQ::Handler,
        TIM1_BRK_TIM15_IRQ::Handler,
        TIM1_UP_TIM16_IRQ::Handler,
        TIM1_TRG_COM_TIM17_IRQ::Handler,
        TIM1_CC_IRQ::Handler,
        TIM2_IRQ::Handler,
        TIM3_IRQ::Handler,
        TIM4_IRQ::Handler,
        I2C1_EV_IRQ::Handler,
        I2C1_ER_IRQ::Handler,
        I2C2_EV_IRQ::Handler,
        I2C2_ER_IRQ::Handler,
        SPI1_IRQ::Handler,
        SPI2_IRQ::Handler,
        USART1_IRQ::Handler,
        USART2_IRQ::Handler,
        USART3_IRQ::Handler,
        EXTI15_10_IRQ::Handler,
        RTC_Alarm_IRQ::Handler,
        CEC_IRQ::Handler,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        TIM6_DAC_IRQ::Handler,
        TIM7_IRQ::Handler

};

__weak void NMI::Handler()
{
    while (1)
    {
    }
}
__weak void HardFault::Handler()
{
    while (1)
    {
    }
}
__weak void MemManage::Handler()
{
    while (1)
    {
    }
}
__weak void BusFault::Handler()
{
    while (1)
    {
    }
}
__weak void UsageFault::Handler()
{
    while (1)
    {
    }
}
__weak void SVC::Handler()
{
    while (1)
    {
    }
}
__weak void DebugMon::Handler()
{
    while (1)
    {
    }
}
__weak void PendSV::Handler()
{
    while (1)
    {
    }
}
__weak void SystemTick::Handler()
{
    while (1)
    {
    }
}
__weak void WWDG_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void PVD_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void TAMPER_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void RTC_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void FLASH_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void RCC_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void EXTI0_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void EXTI1_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void EXTI2_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void EXTI3_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void EXTI4_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void DMA1_Channel1_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void DMA1_Channel2_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void DMA1_Channel3_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void DMA1_Channel4_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void DMA1_Channel5_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void DMA1_Channel6_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void DMA1_Channel7_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void ADC1_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void EXTI9_5_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void TIM1_BRK_TIM15_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void TIM1_UP_TIM16_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void TIM1_TRG_COM_TIM17_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void TIM1_CC_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void TIM2_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void TIM3_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void TIM4_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void I2C1_EV_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void I2C1_ER_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void I2C2_EV_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void I2C2_ER_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void SPI1_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void SPI2_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void USART1_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void USART2_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void USART3_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void EXTI15_10_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void RTC_Alarm_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void CEC_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void TIM6_DAC_IRQ::Handler()
{
    while (1)
    {
    }
}
__weak void TIM7_IRQ::Handler()
{
    while (1)
    {
    }
}

extern "C" void __cmain(void);
extern "C" __weak void SystemInit();

#pragma required = __vector_table
void __program_start(void)
{
    SystemInit();
    __cmain();
}
