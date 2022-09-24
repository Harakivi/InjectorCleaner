#ifndef _INTERRUPTS_F100XB_H
#define _INTERRUPTS_F100XB_H

#include "NVIC_Classes.h"

SystemTick::CallBackType SystemTick::CallBack;

void SystemTick::Handler()
{
    CallBack();
}

TIM1_UP_TIM16_IRQ::CallBackType TIM1_UP_TIM16_IRQ::CallBack;

void TIM1_UP_TIM16_IRQ::Handler()
{
    if (TIM1->SR & TIM_SR_UIF_Msk)
    {
        CallBack();
        TIM1->SR &= ~TIM_SR_UIF_Msk;
    }
}

TIM2_IRQ::CallBackType TIM2_IRQ::CallBack;

#endif //_INTERRUPTS_F100XB_H