#ifndef _CLOCK_H_
#define _CLOCK_H_

namespace Hardware
{
    template <unsigned int HSI,
              unsigned int HSE>
    class Clock
    {
    public:
        static bool Init(unsigned long coreFreq);
        static unsigned long GetCurrentCoreFrequency();
    };

} // namespace Hardware

#ifdef __STM32F100xB_H
#include "STM32F100C4T6/Clock_f100xb.h"
#endif

#endif // _CLOCK_H_