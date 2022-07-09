#ifndef _WATCHDOGTIMER_F100XB_H_
#define _WATCHDOGTIMER_F100XB_H_

namespace Hardware
{
    const unsigned int WatchDogTimer::_LsiSpeed = 40000;
    void WatchDogTimer::Init(unsigned int period_ms)
    {
        unsigned short divider = 4;
        unsigned int period_us = period_ms * 1000;
        unsigned int iwdgClockPeriod_us = 1000000 / (_LsiSpeed / divider);
        while (period_us / iwdgClockPeriod_us > 0xfff)
        {
            divider *= 2;
            iwdgClockPeriod_us = divider * (1000000 / _LsiSpeed);
            if (divider > 256)
            {
                return;
            }
        }
        IWDG->KR = 0x5555;
        switch (divider)
        {
        case 4:
        {
            IWDG->PR = 0;
        }
        break;
        case 8:
        {
            IWDG->PR = 1;
        }
        break;
        case 16:
        {
            IWDG->PR = 2;
        }
        break;
        case 32:
        {
            IWDG->PR = 3;
        }
        break;
        case 64:
        {
            IWDG->PR = 4;
        }
        break;
        case 128:
        {
            IWDG->PR = 5;
        }
        break;
        case 256:
        {
            IWDG->PR = 6;
        }
        break;
        }
        IWDG->RLR = period_us / iwdgClockPeriod_us;
        ResetCounter();
    }
    void WatchDogTimer::ResetCounter()
    {
        IWDG->KR = 0xAAAA;
    }

    void WatchDogTimer::StartCounter()
    {
        IWDG->KR = 0xCCCC;
    }

}

#endif //_WATCHDOGTIMER_F100XB_H_