#ifndef _GPIO_H_
#define _GPIO_H_

namespace Hardware
{
    template <
        unsigned long Port,
        unsigned char PIN>
    class GPIO
    {
    public:
        static void InitOutputPushPull();
        static void InitOutputOpenDrain();
        static void InitOutputPushPullAlternate();
        static void InitOutputOpenDrainAlternate();
        static void InitInputAnalog();
        static void InitInputFloating();
        static void InitInputPullDown();
        static void InitInputPullUp();
        static void Write(bool value);
        static bool Read();
    };
} // Hardware

#ifdef __STM32F100xB_H
#include "STM32F100C4T6\GPIO_f100xb.h"
#endif

#endif //_GPIO_H_