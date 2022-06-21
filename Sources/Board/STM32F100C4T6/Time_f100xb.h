#ifndef _TIME_F100XB_H_
#define _TIME_F100XB_H_

namespace Time
{
    void SystemTimeClass::Init(unsigned long coreFreq, Utils::CallbackWrapper<> &callBack)
    {
        callBack = Handler;
        SysTick->LOAD = coreFreq / 1000;
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
        SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
        NVIC_EnableIRQ(SysTick_IRQn);
    }
} // namespace Time

#endif //_TIME_F100XB_H_