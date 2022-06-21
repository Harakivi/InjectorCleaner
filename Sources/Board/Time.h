#ifndef _TIME_H_
#define _TIME_H_

#include "STM32F100C4T6\NVIC_Classes.h"

namespace Time
{
    class SystemTimeClass : SystemTick
    {
    public:
        static void Init(unsigned long coreFreq, Utils::CallbackWrapper<> &callBack);
        static unsigned long GetTime_ms();
        static void Handler();

    private:
        static unsigned long timeFromStartms;
    };

    void SystemTimeClass::Handler()
    {
        timeFromStartms++;
    }

    unsigned long SystemTimeClass::GetTime_ms()
    {
        return timeFromStartms;
    }

    unsigned long SystemTimeClass::timeFromStartms = 0;
} // namespace Time

#ifdef __STM32F100xB_H
#include "STM32F100C4T6\Time_f100xb.h"
#endif

SystemTick::TimeCallBackType SystemTick::TimeCallBack;

void SystemTick::Handler()
{
    TimeCallBack();
}

#endif //_TIME_H_