#ifndef _NVIC_CASSES_H
#define _NVIC_CASSES_H

#include "..\..\Utils\CallbackWrapper.h"

class NMI
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class HardFault
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class MemManage
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class BusFault
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class UsageFault
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class SVC
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class DebugMon
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class PendSV
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class SystemTick
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

/////////////////////////////
//// External Interrupts ////
/////////////////////////////

class WWDG_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class PVD_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class TAMPER_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class RTC_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class FLASH_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class RCC_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class EXTI0_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class EXTI1_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class EXTI2_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};
class EXTI3_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class EXTI4_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class DMA1_Channel1_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class DMA1_Channel2_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class DMA1_Channel3_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class DMA1_Channel4_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class DMA1_Channel5_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class DMA1_Channel6_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class DMA1_Channel7_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class ADC1_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class EXTI9_5_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class TIM1_BRK_TIM15_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class TIM1_UP_TIM16_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class TIM1_TRG_COM_TIM17_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class TIM1_CC_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class TIM2_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    constexpr static CallBackType CallBack = 0;
};

class TIM3_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class TIM4_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class I2C1_EV_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class I2C1_ER_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class I2C2_EV_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class I2C2_ER_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class SPI1_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class SPI2_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class USART1_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class USART2_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class USART3_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class EXTI15_10_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class RTC_Alarm_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class CEC_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class TIM6_DAC_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

class TIM7_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

//------------------------------------------------
#endif /* _NVIC_CASSES_H */