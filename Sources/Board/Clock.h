#ifndef _CLOCK_H_
#define _CLOCK_H_

namespace Hardware
{
    template <unsigned int HSE = 0,
              unsigned int HSI = 8000000>
    class Clock
    {
    public:
        static unsigned long GetSysCLKFrequency();
        static bool SetSysCLKFrequency(unsigned long SysCLKFreq);
        static unsigned long GetAHBFrequency();
        static bool SetAHBFrequency(unsigned long AHBFreq);
        static unsigned long GetAPB1Frequency();
        static bool SetAPB1Frequency(unsigned long AHBFreq);
        static unsigned long GetAPB2Frequency();
        static bool SetAPB2Frequency(unsigned long AHBFreq);
    };

} // namespace Hardware

#ifdef __STM32F100xB_H
#include "STM32F100C4T6/Clock_f100xb.h"
#endif

#endif // _CLOCK_H_