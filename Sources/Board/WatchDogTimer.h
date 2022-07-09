#ifndef _WATCHDOGTIMER_H_
#define _WATCHDOGTIMER_H_

namespace Hardware
{
    class WatchDogTimer
    {
    public:
        static void Init(unsigned int period_ms);
        static void ResetCounter();
        static void StartCounter();
        static const unsigned int _LsiSpeed;
    };

}

#ifdef __STM32F100xB_H
#include "STM32F100C4T6/WatchDogTimer_f100xb.h"
#endif

#endif //_WATCHDOGTIMER_H_