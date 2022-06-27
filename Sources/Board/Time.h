#ifndef _TIME_H_
#define _TIME_H_

namespace Time
{
    class SystemTimeClass
    {
    public:
        void Init(unsigned long coreFreq);
        unsigned long GetTime_ms();
        void Handler();
        static void Handler(void *_callbackParam)
        {
            SystemTimeClass *me = (SystemTimeClass *)_callbackParam;
            if (!me)
            {
                return;
            }

            me->Handler();
        }

    protected:
        unsigned long timeFromStartms;
    };

    void SystemTimeClass::Handler()
    {
        timeFromStartms++;
    }

    unsigned long SystemTimeClass::GetTime_ms()
    {
        return timeFromStartms;
    }
} // namespace Time


#ifdef __STM32F100xB_H
#include "STM32F100C4T6\Time_f100xb.h"
#endif

#endif //_TIME_H_