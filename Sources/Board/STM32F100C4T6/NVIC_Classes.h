#ifndef _NVIC_CASSES_H
#define _NVIC_CASSES_H

class NMI
{
public:
    static void Handler();
};

class HardFault
{
public:
    static void Handler();
};

class MemManage
{
public:
    static void Handler();
};

class BusFault
{
public:
    static void Handler();
};

class UsageFault
{
public:
    static void Handler();
};

class SVC
{
public:
    static void Handler();
};

class DebugMon
{
public:
    static void Handler();
};

class PendSV
{
public:
    static void Handler();
};

class SystemTick
{
public:
    static void Handler();
};

/////////////////////////////
//// External Interrupts ////
/////////////////////////////

class WWDG_IRQ
{
public:
    static void Handler();
};

class PVD_IRQ
{
public:
    static void Handler();
};

class TAMPER_IRQ
{
public:
    static void Handler();
};

class RTC_IRQ
{
public:
    static void Handler();
};

class FLASH_IRQ
{
public:
    static void Handler();
};

class RCC_IRQ
{
public:
    static void Handler();
};

class EXTI0_IRQ
{
public:
    static void Handler();
};

class EXTI1_IRQ
{
public:
    static void Handler();
};

class EXTI2_IRQ
{
public:
    static void Handler();
};
class EXTI3_IRQ
{
public:
    static void Handler();
};

class EXTI4_IRQ
{
public:
    static void Handler();
};

class DMA1_Channel1_IRQ
{
public:
    static void Handler();
};

class DMA1_Channel2_IRQ
{
public:
    static void Handler();
};

class DMA1_Channel3_IRQ
{
public:
    static void Handler();
};

class DMA1_Channel4_IRQ
{
public:
    static void Handler();
};

class DMA1_Channel5_IRQ
{
public:
    static void Handler();
};

class DMA1_Channel6_IRQ
{
public:
    static void Handler();
};

class DMA1_Channel7_IRQ
{
public:
    static void Handler();
};

class ADC1_IRQ
{
public:
    static void Handler();
};

class EXTI9_5_IRQ
{
public:
    static void Handler();
};

class TIM1_BRK_TIM15_IRQ
{
public:
    static void Handler();
};

class TIM1_UP_TIM16_IRQ
{
public:
    static void Handler();
};

class TIM1_TRG_COM_TIM17_IRQ
{
public:
    static void Handler();
};

class TIM1_CC_IRQ
{
public:
    static void Handler();
};

class TIM2_IRQ
{
public:
    static void Handler();
};

class TIM3_IRQ
{
public:
    static void Handler();
};

class TIM4_IRQ
{
public:
    static void Handler();
};

class I2C1_EV_IRQ
{
public:
    static void Handler();
};

class I2C1_ER_IRQ
{
public:
    static void Handler();
};

class I2C2_EV_IRQ
{
public:
    static void Handler();
};

class I2C2_ER_IRQ
{
public:
    static void Handler();
};

class SPI1_IRQ
{
public:
    static void Handler();
};

class SPI2_IRQ
{
public:
    static void Handler();
};

class USART1_IRQ
{
public:
    static void Handler();
};

class USART2_IRQ
{
public:
    static void Handler();
};

class USART3_IRQ
{
public:
    static void Handler();
};

class EXTI15_10_IRQ
{
public:
    static void Handler();
};

class RTC_Alarm_IRQ
{
public:
    static void Handler();
};

class CEC_IRQ
{
public:
    static void Handler();
};

class TIM6_DAC_IRQ
{
public:
    static void Handler();
};

class TIM7_IRQ
{
public:
    static void Handler();
};

//------------------------------------------------
#endif /* _NVIC_CASSES_H */