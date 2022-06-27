#ifndef _CLOCK_F100XB_H_
#define _CLOCK_F100XB_H_

namespace Hardware
{
    template <unsigned int HSE,
              unsigned int HSI>
    bool Clock<HSE, HSI>::SetSysCLKFrequency(unsigned long SysCLKFreq)
    {
        bool HsePresent = HSE > 0;
        if (SysCLKFreq > 24000000)
        {
            return false;
        }
        if (HsePresent)
        {
            RCC->CR |= RCC_CR_HSEON_Msk;
            unsigned long delay = 10000;
            while ((--delay) && !(RCC->CR & RCC_CR_HSERDY_Msk))
            {
            }
            if (!delay)
            {
                HsePresent = false;
            }
        }
        if constexpr (HSE > 0)
        {
            if (HsePresent && (SysCLKFreq % HSE == 0))
            {
                unsigned int tmp = ((SysCLKFreq / HSE) - 2) << RCC_CFGR_PLLMULL_Pos;
                tmp |= RCC->CFGR;
                RCC->CFGR = tmp;
                RCC->CFGR |= RCC_CFGR_PLLSRC_Msk;
                RCC->CR |= RCC_CR_PLLON_Msk;
                unsigned long delay = 10000;
                while ((--delay) && !(RCC->CR & RCC_CR_PLLRDY_Msk))
                {
                }
                if (!delay)
                {
                    return false;
                }
                RCC->CFGR |= RCC_CFGR_SW_PLL;
                delay = 10000;
                while ((--delay) && !(RCC->CFGR & RCC_CFGR_SWS_PLL))
                {
                }
                if (!delay)
                {
                    return false;
                }
            }
            else if (HsePresent)
            {
                unsigned char preDivider = 0;
                for (unsigned char i = 2; i <= 16; i++)
                {
                    if ((SysCLKFreq % (HSE / i) == 0))
                    {
                        preDivider = i;
                        break;
                    }
                }
                if (preDivider)
                {
                    RCC->CFGR2 = preDivider - 1;
                    unsigned int tmp = ((SysCLKFreq / (HSE / preDivider)) - 2) << RCC_CFGR_PLLMULL_Pos;
                    tmp |= RCC->CFGR;
                    RCC->CFGR = tmp;
                    RCC->CFGR |= RCC_CFGR_PLLSRC_Msk;
                    RCC->CR |= RCC_CR_PLLON_Msk;
                    unsigned long delay = 10000;
                    while ((--delay) && !(RCC->CR & RCC_CR_PLLRDY_Msk))
                    {
                    }
                    if (!delay)
                    {
                        return false;
                    }
                    RCC->CFGR |= RCC_CFGR_SW_PLL;
                    delay = 10000;
                    while ((--delay) && !(RCC->CFGR & RCC_CFGR_SWS_PLL))
                    {
                    }
                    if (!delay)
                    {
                        return false;
                    }
                }
            }
        }
        else if (SysCLKFreq % HSI == 0)
        {
            unsigned int tmp = ((SysCLKFreq / HSI) - 2) << RCC_CFGR_PLLMULL_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
            RCC->CFGR &= ~(RCC_CFGR_PLLSRC_Msk);
            RCC->CR |= RCC_CR_PLLON_Msk;
            unsigned long delay = 10000;
            while ((--delay) && !(RCC->CR & RCC_CR_PLLRDY_Msk))
            {
            }
            if (!delay)
            {
                return false;
            }
            RCC->CFGR |= RCC_CFGR_SW_PLL;
            delay = 10000;
            while ((--delay) && !(RCC->CFGR & RCC_CFGR_SWS_PLL))
            {
            }
            if (!delay)
            {
                return false;
            }
        }
        else
        {
            if (RCC->CFGR & RCC_CFGR_SWS_HSI)
            {
                return false;
            }
            else
            {
                RCC->CFGR |= RCC_CFGR_SW_HSI;
            }
        }
        return SysCLKFreq == GetSysCLKFrequency();
    }

    template <unsigned int HSE,
              unsigned int HSI>
    unsigned long Clock<HSE, HSI>::GetSysCLKFrequency()
    {
        unsigned int tmp = 0U, pllmull = 0U, pllsource = 0U;
        unsigned int prediv1factor = 0U;

        /* Get SYSCLK source -------------------------------------------------------*/
        tmp = RCC->CFGR & RCC_CFGR_SWS;

        switch (tmp)
        {
        case 0x00U: /* HSI used as system clock */
            return HSI;
            break;
        case 0x04U: /* HSE used as system clock */
            return HSE;
            break;
        case 0x08U: /* PLL used as system clock */

            /* Get PLL clock source and multiplication factor ----------------------*/
            pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
            pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
            pllmull = (pllmull >> 18U) + 2U;

            if (pllsource == 0x00U)
            {
                /* HSI oscillator clock divided by 2 selected as PLL clock entry */
                return (HSI >> 1U) * pllmull;
            }
            else
            {
                prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1U;
                /* HSE oscillator clock selected as PREDIV1 clock entry */
                return (HSE / prediv1factor) * pllmull;
            }
            break;

        default:
            return HSI;
            break;
        }
    }

    template <unsigned int HSE,
              unsigned int HSI>
    unsigned long Clock<HSE, HSI>::GetAHBFrequency()
    {
        unsigned int AHB_Prescaler_Reg = (RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos;

        if (AHB_Prescaler_Reg < 8)
        {
            return GetSysCLKFrequency();
        }
        else
        {
            switch (AHB_Prescaler_Reg)
            {
            case 8:
            {
                return GetSysCLKFrequency() / 2;
            }
            break;
            case 9:
            {
                return GetSysCLKFrequency() / 4;
            }
            break;
            case 10:
            {
                return GetSysCLKFrequency() / 8;
            }
            break;
            case 11:
            {
                return GetSysCLKFrequency() / 16;
            }
            break;
            case 12:
            {
                return GetSysCLKFrequency() / 64;
            }
            break;
            case 13:
            {
                return GetSysCLKFrequency() / 128;
            }
            break;
            case 14:
            {
                return GetSysCLKFrequency() / 256;
            }
            break;
            case 15:
            {
                return GetSysCLKFrequency() / 512;
            }
            break;
            }
        }
        return 0;
    }

    template <unsigned int HSE,
              unsigned int HSI>
    bool Clock<HSE, HSI>::SetAHBFrequency(unsigned long AHBFreq)
    {
        if (AHBFreq > GetSysCLKFrequency())
        {
            return false;
        }
        unsigned int divider = GetSysCLKFrequency() / AHBFreq;

        switch (divider)
        {
        case 2:
        {
            unsigned int tmp = 8 << RCC_CFGR_HPRE_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 4:
        {
            unsigned int tmp = 9 << RCC_CFGR_HPRE_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 8:
        {
            unsigned int tmp = 10 << RCC_CFGR_HPRE_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 16:
        {
            unsigned int tmp = 11 << RCC_CFGR_HPRE_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 64:
        {
            unsigned int tmp = 12 << RCC_CFGR_HPRE_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 128:
        {
            unsigned int tmp = 13 << RCC_CFGR_HPRE_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 256:
        {
            unsigned int tmp = 14 << RCC_CFGR_HPRE_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 512:
        {
            unsigned int tmp = 15 << RCC_CFGR_HPRE_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        }
        return AHBFreq == GetAHBFrequency();
    }

    template <unsigned int HSE,
              unsigned int HSI>
    unsigned long Clock<HSE, HSI>::GetAPB1Frequency()
    {
        unsigned int APB1_Prescaler_Reg = (RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos;

        if (APB1_Prescaler_Reg < 4)
        {
            return GetAHBFrequency();
        }
        else
        {
            switch (APB1_Prescaler_Reg)
            {
            case 4:
            {
                return GetAHBFrequency() / 2;
            }
            break;
            case 5:
            {
                return GetAHBFrequency() / 4;
            }
            break;
            case 6:
            {
                return GetAHBFrequency() / 8;
            }
            break;
            case 7:
            {
                return GetAHBFrequency() / 16;
            }
            break;
            }
        }
        return 0;
    }

    template <unsigned int HSE,
              unsigned int HSI>
    bool Clock<HSE, HSI>::SetAPB1Frequency(unsigned long APB1Freq)
    {
        if (APB1Freq > GetAHBFrequency())
        {
            return false;
        }
        unsigned int divider = GetAHBFrequency() / APB1Freq;

        switch (divider)
        {
        case 2:
        {
            unsigned int tmp = 4 << RCC_CFGR_PPRE1_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 4:
        {
            unsigned int tmp = 5 << RCC_CFGR_PPRE1_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 8:
        {
            unsigned int tmp = 6 << RCC_CFGR_PPRE1_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 16:
        {
            unsigned int tmp = 7 << RCC_CFGR_PPRE1_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        }
        return APB1Freq == GetAPB1Frequency();
    }

    template <unsigned int HSE,
              unsigned int HSI>
    unsigned long Clock<HSE, HSI>::GetAPB2Frequency()
    {
        unsigned int APB2_Prescaler_Reg = (RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos;

        if (APB2_Prescaler_Reg < 4)
        {
            return GetAHBFrequency();
        }
        else
        {
            switch (APB2_Prescaler_Reg)
            {
            case 4:
            {
                return GetAHBFrequency() / 2;
            }
            break;

            case 5:
            {
                return GetAHBFrequency() / 4;
            }
            break;

            case 6:
            {
                return GetAHBFrequency() / 8;
            }
            break;

            case 7:
            {
                return GetAHBFrequency() / 16;
            }
            break;
            }
        }
        return 0;
    }

    template <unsigned int HSE,
              unsigned int HSI>
    bool Clock<HSE, HSI>::SetAPB2Frequency(unsigned long APB2Freq)
    {
        if (APB2Freq > GetAHBFrequency())
        {
            return false;
        }
        unsigned int divider = GetAHBFrequency() / APB2Freq;

        switch (divider)
        {
        case 2:
        {
            unsigned int tmp = 4 << RCC_CFGR_PPRE2_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 4:
        {
            unsigned int tmp = 5 << RCC_CFGR_PPRE2_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 8:
        {
            unsigned int tmp = 6 << RCC_CFGR_PPRE2_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        case 16:
        {
            unsigned int tmp = 7 << RCC_CFGR_PPRE2_Pos;
            tmp |= RCC->CFGR;
            RCC->CFGR = tmp;
        }
        break;
        }
        return APB2Freq == GetAPB2Frequency();
    }
} // namespace Hardware

#endif //_CLOCK_F100XB_H_