#ifndef _INTERRUPTS_F100XB_H
#define _INTERRUPTS_F100XB_H

class SystemTick
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType CallBack;
};

SystemTick::CallBackType SystemTick::CallBack;

void SystemTick::Handler()
{
    CallBack();
}

class TIM1_UP_TIM16_IRQ
{
public:
    typedef Utils::CallbackWrapper<> CallBackType;
    static void Handler();
    static CallBackType UpdateCallBack;
};

TIM1_UP_TIM16_IRQ::CallBackType TIM1_UP_TIM16_IRQ::UpdateCallBack;

void TIM1_UP_TIM16_IRQ::Handler()
{
    if (TIM1->SR & TIM_SR_UIF_Msk)
    {
        UpdateCallBack();
        TIM1->SR &= ~TIM_SR_UIF_Msk;
    }
}

#endif //_INTERRUPTS_F100XB_H