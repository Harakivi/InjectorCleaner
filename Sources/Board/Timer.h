#ifndef _TIMER_H_
#define _TIMER_H_

namespace Hardware
{

    enum Timers
    {
        Timer1 = TIM1_BASE,
        Timer2 = TIM2_BASE,
        Timer3 = TIM3_BASE,
        Timer4 = TIM4_BASE,
        Timer6 = TIM6_BASE,
        Timer7 = TIM7_BASE,
    };

    template <Timers TIM, class CoreClock>
    class Timer
    {
    public:
        struct PWMCnanStruct
        {
            float dutyCycle;
            bool invert;
        };
        static void InitCounter(double Freq, bool interruptEn);
        static void InitPWM(double Freq, bool interruptEn, PWMCnanStruct chan1DutyCycle = {0}, PWMCnanStruct chan2DutyCycle = {0}, PWMCnanStruct chan3DutyCycle = {0}, PWMCnanStruct chan4DutyCycle = {0});
        static void Start();
        static void Stop();
        static unsigned short GetCounterValue();
        static void SetReloadValue(unsigned short Value);
        static void SetDutyCycle_ms(float dutyCycle, unsigned char channel);
        static float GetDutyCycle_ms(unsigned char channel);
        static void SetPrescalerrValue(unsigned short Value);
        static unsigned short GetReloadValue();
        static unsigned short GetPrescalerrValue();
        static unsigned int GetFrequency();
        static void SetFrequency(unsigned int Freq);
        static void SetUpdateCallBack(void (*callBack)())
        {
            TIM1_UP_TIM16_IRQ::CallBack.Set(callBack);
        }
        void SetUpdateCallBack(void (*callBack)(void *), void *callBackParam)
        {
            TIM1_UP_TIM16_IRQ::CallBack.Set(callBack, callBackParam);
        }

    protected:
        static void PwmGPIOInit(unsigned char timChannel);
    };
} // namespace Hardware

#ifdef __STM32F100xB_H
#include "STM32F100C4T6\Timer_f100xb.h"
#endif

#endif //_TIMER_H_