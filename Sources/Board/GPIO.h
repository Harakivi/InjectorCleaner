#ifndef _GPIO_H_
#define _GPIO_H_

namespace Hardware
{

    enum GPIO_Ports
    {
        A = GPIOA_BASE,
        B = GPIOB_BASE,
        C = GPIOC_BASE,
        D = GPIOD_BASE,
        E = GPIOE_BASE,
    };
    template <
        GPIO_Ports Port,
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
        static void Toggle();
        static bool Read();
    };

    template <
        GPIO_Ports Port,
        unsigned char PIN>
    void GPIO<Port, PIN>::Toggle()
    {
        Write(!Read());
    }
} // Hardware

#ifdef __STM32F100xB_H
#include "STM32F100C4T6\GPIO_f100xb.h"
#endif

#endif //_GPIO_H_