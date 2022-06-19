#ifndef _TIME_H_
#define _TIME_H_

#include "STM32F100C4T6\NVIC_Classes.h"

namespace Time
{
  class SystemTimeClass:SystemTick
    {
    public:
        void Init(unsigned long coreFreq);
        unsigned long GetTime_ms();
        static void Handler();

    private:
        unsigned long timeFromStartms;
    };

    void SystemTimeClass::Handler()
    {
        this.timeFromStartms++;
    }

    void SystemTimeClass::Init(unsigned long coreFreq)
    {
      //void (SystemTick::*_callBack)() = reinterpret_cast<void (SystemTick::*)()>(&Handler);
        SysTick->LOAD = coreFreq / 1000;
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
        SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        NVIC_EnableIRQ(SysTick_IRQn);
    }

    unsigned long SystemTimeClass::GetTime_ms()
    {
        return timeFromStartms;
    }

    SystemTimeClass GlobalTime;

}

std::function SystemTick::func;

void SystemTick::Handler()
{
    Time::GlobalTime.Handler();
}

#endif //_TIME_H_