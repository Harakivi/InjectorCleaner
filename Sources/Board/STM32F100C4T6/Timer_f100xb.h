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
    void Timer<TIM, CoreClock>::InitPWM(double Freq, bool interruptEn, PWMCnanStruct chan1, PWMCnanStruct chan2, PWMCnanStruct chan3, PWMCnanStruct chan4)
    {
        InitCounter(Freq, interruptEn);
        if (chan1.dutyCycle > 0.0)
        {
            ((TIM_TypeDef *)TIM)->CCER |= TIM_CCER_CC1E_Msk;
            ((TIM_TypeDef *)TIM)->CCMR1 |= 0b110 << TIM_CCMR1_OC1M_Pos;
            PwmGPIOInit(1);
            ((TIM_TypeDef *)TIM)->BDTR |= TIM_BDTR_MOE_Msk;
            if (chan1.invert)
            {
                ((TIM_TypeDef *)TIM)->CCER |= TIM_CCER_CC1P_Msk;
            }
            SetDutyCycle_ms(chan1.dutyCycle, 1);
        }
        if (chan2.dutyCycle > 0.0)
        {
            ((TIM_TypeDef *)TIM)->CCER |= TIM_CCER_CC2E_Msk;
            ((TIM_TypeDef *)TIM)->CCMR1 |= 0b110 << TIM_CCMR1_OC2M_Pos;
            PwmGPIOInit(2);
            ((TIM_TypeDef *)TIM)->BDTR |= TIM_BDTR_MOE_Msk;
            if (chan2.invert)
            {
                ((TIM_TypeDef *)TIM)->CCER |= TIM_CCER_CC2P_Msk;
            }
            SetDutyCycle_ms(chan2.dutyCycle, 2);
        }
        if (chan3.dutyCycle > 0.0)
        {
            ((TIM_TypeDef *)TIM)->CCER |= TIM_CCER_CC3E_Msk;
            ((TIM_TypeDef *)TIM)->CCMR2 |= 0b110 << TIM_CCMR2_OC3M_Pos;
            PwmGPIOInit(3);
            ((TIM_TypeDef *)TIM)->BDTR |= TIM_BDTR_MOE_Msk;
            if (chan3.invert)
            {
                ((TIM_TypeDef *)TIM)->CCER |= TIM_CCER_CC3P_Msk;
            }
            SetDutyCycle_ms(chan3.dutyCycle, 3);
        }
        if (chan4.dutyCycle > 0.0)
        {
            ((TIM_TypeDef *)TIM)->CCER |= TIM_CCER_CC4E_Msk;
            ((TIM_TypeDef *)TIM)->CCMR2 |= 0b110 << TIM_CCMR2_OC4M_Pos;
            PwmGPIOInit(4);
            ((TIM_TypeDef *)TIM)->BDTR |= TIM_BDTR_MOE_Msk;
            if (chan4.invert)
            {
                ((TIM_TypeDef *)TIM)->CCER |= TIM_CCER_CC4P_Msk;
            }
            SetDutyCycle_ms(chan4.dutyCycle, 4);
        }
    }

    template <Timers TIM, class CoreClock>
    void Timer<TIM, CoreClock>::SetDutyCycle_ms(float dutyCycle, unsigned char channel)
    {
        float floatValue = ((TIM_TypeDef *)TIM)->ARR;
        unsigned int Value = 0;
        float ratio = (dutyCycle / ((1.0 / GetFrequency()) * 1000));
        floatValue *= ratio;
        Value = (unsigned int)floatValue;
        if ((floatValue - Value) > 0)
        {
            Value += 1;
        }
        if (Value > ((TIM_TypeDef *)TIM)->ARR)
        {
            return;
        }
        switch (channel)
        {
        case 1:
        {
            if (((TIM_TypeDef *)TIM)->CCER & TIM_CCER_CC1P_Msk)
            {
                ((TIM_TypeDef *)TIM)->CCR1 = ((TIM_TypeDef *)TIM)->ARR - Value;
            }
            else
            {
                ((TIM_TypeDef *)TIM)->CCR1 = Value;
            }
        }
        break;
        case 2:
        {
            if (((TIM_TypeDef *)TIM)->CCER & TIM_CCER_CC2P_Msk)
            {
                ((TIM_TypeDef *)TIM)->CCR2 = ((TIM_TypeDef *)TIM)->ARR - Value;
            }
            else
            {
                ((TIM_TypeDef *)TIM)->CCR2 = Value;
            }
        }
        break;
        case 3:
        {
            if (((TIM_TypeDef *)TIM)->CCER & TIM_CCER_CC3P_Msk)
            {
                ((TIM_TypeDef *)TIM)->CCR3 = ((TIM_TypeDef *)TIM)->ARR - Value;
            }
            else
            {
                ((TIM_TypeDef *)TIM)->CCR3 = Value;
            }
        }
        break;
        case 4:
        {
            if (((TIM_TypeDef *)TIM)->CCER & TIM_CCER_CC4P_Msk)
            {
                ((TIM_TypeDef *)TIM)->CCR4 = ((TIM_TypeDef *)TIM)->ARR - Value;
            }
            else
            {
                ((TIM_TypeDef *)TIM)->CCR4 = Value;
            }
        }
        break;
        }
    }
    template <Timers TIM, class CoreClock>
    float Timer<TIM, CoreClock>::GetDutyCycle_ms(unsigned char channel)
    {
        float ratio = 0;
        bool chanPolarity = false;
        switch (channel)
        {
        case 1:
        {
            ratio = ((TIM_TypeDef *)TIM)->CCR1;
            ratio /= ((TIM_TypeDef *)TIM)->ARR;
            chanPolarity = (bool)(((TIM_TypeDef *)TIM)->CCER & TIM_CCER_CC1P_Msk);
        }
        break;
        case 2:
        {
            ratio = ((TIM_TypeDef *)TIM)->CCR2;
            ratio /= ((TIM_TypeDef *)TIM)->ARR;
            chanPolarity = (bool)(((TIM_TypeDef *)TIM)->CCER & TIM_CCER_CC2P_Msk);
        }
        break;
        case 3:
        {
            ratio = ((TIM_TypeDef *)TIM)->CCR3;
            ratio /= ((TIM_TypeDef *)TIM)->ARR;
            chanPolarity = (bool)(((TIM_TypeDef *)TIM)->CCER & TIM_CCER_CC3P_Msk);
        }
        break;
        case 4:
        {
            ratio = ((TIM_TypeDef *)TIM)->CCR4;
            ratio /= ((TIM_TypeDef *)TIM)->ARR;
            chanPolarity = (bool)(((TIM_TypeDef *)TIM)->CCER & TIM_CCER_CC4P_Msk);
        }
        break;

        default:
            return 0;
            break;
        }
        if (chanPolarity)
        {
            return (1.0 / GetFrequency() * (1 - ratio)) * 1000;
        }
        return (1.0 / GetFrequency() * ratio) * 1000;
    }

    template <Timers TIM, class CoreClock>
    void Timer<TIM, CoreClock>::PwmGPIOInit(unsigned char timChannel)
    {
        if constexpr (TIM == TIM1_BASE)
        {
            RCC->APB2ENR &= ~RCC_APB2ENR_IOPAEN;
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        }
        if constexpr (TIM == TIM2_BASE)
        {
            RCC->APB2ENR &= ~RCC_APB2ENR_IOPAEN;
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        }
        if constexpr (TIM == TIM3_BASE)
        {
            RCC->APB2ENR &= ~RCC_APB2ENR_IOPAEN;
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
            RCC->APB2ENR &= ~RCC_APB2ENR_IOPBEN;
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
        }
        if constexpr (TIM == TIM4_BASE)
        {
            RCC->APB2ENR &= ~RCC_APB2ENR_IOPBEN;
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
        }
        if (TIM == TIM1_BASE && timChannel == 1)
        {
            Hardware::GPIO<Hardware::A, 8>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM1_BASE && timChannel == 2)
        {
            Hardware::GPIO<Hardware::A, 9>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM1_BASE && timChannel == 3)
        {
            Hardware::GPIO<Hardware::A, 10>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM1_BASE && timChannel == 4)
        {
            Hardware::GPIO<Hardware::A, 11>::InitOutputPushPullAlternate();
        }

        else if (TIM == TIM2_BASE && timChannel == 1)
        {
            // Hardware::GPIO<Hardware::A, 8>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM2_BASE && timChannel == 2)
        {
            Hardware::GPIO<Hardware::A, 1>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM2_BASE && timChannel == 3)
        {
            Hardware::GPIO<Hardware::A, 2>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM2_BASE && timChannel == 4)
        {
            Hardware::GPIO<Hardware::A, 3>::InitOutputPushPullAlternate();
        }

        else if (TIM == TIM3_BASE && timChannel == 1)
        {
            Hardware::GPIO<Hardware::A, 6>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM3_BASE && timChannel == 2)
        {
            Hardware::GPIO<Hardware::A, 7>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM3_BASE && timChannel == 3)
        {
            Hardware::GPIO<Hardware::B, 0>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM3_BASE && timChannel == 4)
        {
            Hardware::GPIO<Hardware::B, 1>::InitOutputPushPullAlternate();
        }

        else if (TIM == TIM4_BASE && timChannel == 1)
        {
            Hardware::GPIO<Hardware::B, 6>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM4_BASE && timChannel == 2)
        {
            Hardware::GPIO<Hardware::B, 7>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM4_BASE && timChannel == 3)
        {
            Hardware::GPIO<Hardware::B, 8>::InitOutputPushPullAlternate();
        }
        else if (TIM == TIM4_BASE && timChannel == 4)
        {
            Hardware::GPIO<Hardware::B, 9>::InitOutputPushPullAlternate();
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