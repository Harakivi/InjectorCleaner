#ifndef _TIMER_F100XB_H_
#define _TIMER_F100XB_H_

namespace Hardware
{
    template <Timers TIM, class CoreClock>
    void Timer<TIM, CoreClock>::InitCounter(double Freq, bool interruptEn)
    {
        unsigned int divider = 0;
        if constexpr (TIM == TIM1_BASE)
        {
            divider = (unsigned int)(CoreClock::GetAPB2Frequency() / Freq * (CoreClock::GetAHBFrequency() / CoreClock::GetAPB2Frequency() == 1 ? 1 : 2));
        }
        else
        {
            divider = (unsigned int)(CoreClock::GetAPB1Frequency() / Freq * (CoreClock::GetAHBFrequency() / CoreClock::GetAPB1Frequency() == 1 ? 1 : 2));
        }

        if constexpr (TIM == TIM1_BASE)
        {
            RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN;
            RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
        }
        if constexpr (TIM == TIM2_BASE)
        {
            RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN;
            RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
        }
        if constexpr (TIM == TIM3_BASE)
        {
            RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN;
            RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
        }
        if constexpr (TIM == TIM4_BASE)
        {
            RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;
            RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
        }
        if constexpr (TIM == TIM6_BASE)
        {
            RCC->APB1ENR &= ~RCC_APB1ENR_TIM6EN;
            RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
        }
        if constexpr (TIM == TIM7_BASE)
        {
            RCC->APB1ENR &= ~RCC_APB1ENR_TIM7EN;
            RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
        }
        if (divider < 65535)
        {
            SetReloadValue(divider);
        }
        else
        {
            unsigned short prescaler = divider / 65535 + (divider % 65535 > 0 ? 1 : 0) - 1;
            SetPrescalerrValue(prescaler);
            SetReloadValue(divider / (prescaler + 1));
        }

        if (interruptEn)
        {
            ((TIM_TypeDef *)TIM)->DIER |= TIM_DIER_UIE_Msk;
            if constexpr (TIM == TIM1_BASE)
            {
                NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
            }
            if constexpr (TIM == TIM2_BASE)
            {
                NVIC_EnableIRQ(TIM2_IRQn);
            }
            if constexpr (TIM == TIM3_BASE)
            {
                NVIC_EnableIRQ(TIM3_IRQn);
            }
            if constexpr (TIM == TIM4_BASE)
            {
                NVIC_EnableIRQ(TIM4_IRQn);
            }
            if constexpr (TIM == TIM6_BASE)
            {
                NVIC_EnableIRQ(TIM6_IRQn);
            }
            if constexpr (TIM == TIM7_BASE)
            {
                NVIC_EnableIRQ(TIM7_IRQn);
            }
        }
    }
    template <Timers TIM, class CoreClock>
    void Timer<TIM, CoreClock>::Start()
    {
        ((TIM_TypeDef *)TIM)->CR1 |= TIM_CR1_CEN_Msk;
    }

    template <Timers TIM, class CoreClock>
    void Timer<TIM, CoreClock>::Stop()
    {
        ((TIM_TypeDef *)TIM)->CR1 &= ~TIM_CR1_CEN_Msk;
    }

    template <Timers TIM, class CoreClock>
    unsigned int Timer<TIM, CoreClock>::GetFrequency()
    {
        unsigned int timClock = 0;
        if constexpr (TIM == TIM1_BASE)
        {
            timClock = (unsigned int)(CoreClock::GetAPB2Frequency() * (CoreClock::GetAHBFrequency() / CoreClock::GetAPB2Frequency() == 1 ? 1 : 2));
        }
        else
        {
            timClock = (unsigned int)(CoreClock::GetAPB1Frequency() * (CoreClock::GetAHBFrequency() / CoreClock::GetAPB1Frequency() == 1 ? 1 : 2));
        }
        return (timClock / (GetPrescalerrValue() + 1)) / GetReloadValue();
    }

    template <Timers TIM, class CoreClock>
    void Timer<TIM, CoreClock>::SetReloadValue(unsigned short Value)
    {
        ((TIM_TypeDef *)TIM)->ARR = Value;
    }

    template <Timers TIM, class CoreClock>
    void Timer<TIM, CoreClock>::SetPrescalerrValue(unsigned short Value)
    {
        ((TIM_TypeDef *)TIM)->PSC = Value;
    }
    template <Timers TIM, class CoreClock>
    unsigned short Timer<TIM, CoreClock>::GetReloadValue()
    {
        return ((TIM_TypeDef *)TIM)->ARR;
    }
    template <Timers TIM, class CoreClock>
    unsigned short Timer<TIM, CoreClock>::GetPrescalerrValue()
    {
        return ((TIM_TypeDef *)TIM)->PSC;
    }

    template <Timers TIM, class CoreClock>
    unsigned short Timer<TIM, CoreClock>::GetCounterValue()
    {
        return ((TIM_TypeDef *)TIM)->CNT;
    }
} // namespace Hardware

#endif //_TIMER_F100XB_H_