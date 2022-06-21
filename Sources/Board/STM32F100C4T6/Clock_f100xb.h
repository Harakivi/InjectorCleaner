#ifndef _CLOCK_F100XB_H_
#define _CLOCK_F100XB_H_

namespace Hardware
{
    template <unsigned int HSI,
              unsigned int HSE>
    bool Clock<HSI, HSE>::Init(unsigned long coreFreq)
    {
        return coreFreq == GetCurrentCoreFrequency();
    }

    template <unsigned int HSI,
              unsigned int HSE>
    unsigned long Clock<HSI, HSE>::GetCurrentCoreFrequency()
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
} // namespace Hardware

#endif //_CLOCK_F100XB_H_