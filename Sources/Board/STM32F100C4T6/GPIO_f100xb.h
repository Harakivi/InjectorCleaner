#include "..\GPIO.h"
namespace Hardware
{
    template <
        unsigned long Port,
        unsigned char PIN>
    void GPIO<Port, PIN>::InitOutputPushPull()
    {
        if constexpr (Port == GPIOA_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        }
        if constexpr (Port == GPIOB_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
        }
        if constexpr (Port == GPIOC_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
        }
        if constexpr (Port == GPIOD_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
        }
        if constexpr (Port == GPIOE_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
        }
        if constexpr (PIN <= 7)
        {
            ((GPIO_TypeDef *)Port)->CRL |= 0x3UL << (4 * PIN);
            ((GPIO_TypeDef *)Port)->CRL &= ~(0x3UL << (4 * PIN + 2));
        }
        else
        {
            ((GPIO_TypeDef *)Port)->CRH |= 0x3UL << (4 * (PIN - 8));
            ((GPIO_TypeDef *)Port)->CRH &= ~(0x3UL << (4 * (PIN - 8) + 2));
        }
    }

    template <
        unsigned long Port,
        unsigned char PIN>
    void GPIO<Port, PIN>::InitOutputOpenDrain()
    {
        if constexpr (Port == GPIOA_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        }
        if constexpr (Port == GPIOB_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
        }
        if constexpr (Port == GPIOC_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
        }
        if constexpr (Port == GPIOD_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
        }
        if constexpr (Port == GPIOE_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
        }
        if constexpr (PIN <= 7)
        {
            ((GPIO_TypeDef *)Port)->CRL |= 0x3UL << (4 * PIN);
            ((GPIO_TypeDef *)Port)->CRL |= 0x1UL << (4 * PIN + 2);
            ((GPIO_TypeDef *)Port)->CRL &= ~(0x1UL << (4 * PIN + 3));
        }
        else
        {
            ((GPIO_TypeDef *)Port)->CRH |= 0x3UL << (4 * (PIN - 8));
            ((GPIO_TypeDef *)Port)->CRH |= 0x1UL << (4 * (PIN - 8) + 2);
            ((GPIO_TypeDef *)Port)->CRH &= ~(0x1UL << (4 * (PIN - 8) + 3));
        }
    }
    
    template <
        unsigned long Port,
        unsigned char PIN>
    void GPIO<Port, PIN>::InitOutputPushPullAlternate()
    {
        if constexpr (Port == GPIOA_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        }
        if constexpr (Port == GPIOB_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
        }
        if constexpr (Port == GPIOC_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
        }
        if constexpr (Port == GPIOD_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
        }
        if constexpr (Port == GPIOE_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
        }
        if constexpr (PIN <= 7)
        {
            ((GPIO_TypeDef *)Port)->CRL |= 0x3UL << (4 * PIN);
            ((GPIO_TypeDef *)Port)->CRL &= ~(0x1UL << (4 * PIN + 2));
            ((GPIO_TypeDef *)Port)->CRL |= 0x1UL << (4 * PIN + 3);
        }
        else
        {
            ((GPIO_TypeDef *)Port)->CRH |= 0x3UL << (4 * (PIN - 8));
            ((GPIO_TypeDef *)Port)->CRH &= ~(0x1UL << (4 * (PIN - 8) + 2));
            ((GPIO_TypeDef *)Port)->CRH |= 0x1UL << (4 * (PIN - 8) + 3);
        }
    }

    template <
        unsigned long Port,
        unsigned char PIN>
    void GPIO<Port, PIN>::InitOutputOpenDrainAlternate()
    {
        if constexpr (Port == GPIOA_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        }
        if constexpr (Port == GPIOB_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
        }
        if constexpr (Port == GPIOC_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
        }
        if constexpr (Port == GPIOD_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
        }
        if constexpr (Port == GPIOE_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
        }
        if constexpr (PIN <= 7)
        {
            ((GPIO_TypeDef *)Port)->CRL |= 0x3UL << (4 * PIN);
            ((GPIO_TypeDef *)Port)->CRL |= 0x3UL << (4 * PIN + 2);
        }
        else
        {
            ((GPIO_TypeDef *)Port)->CRH |= 0x3UL << (4 * (PIN - 8));
            ((GPIO_TypeDef *)Port)->CRH |= 0x3UL << (4 * (PIN - 8) + 2);
        }
    }
    
    template <
        unsigned long Port,
        unsigned char PIN>
    void GPIO<Port, PIN>::InitInputAnalog()
    {
        if constexpr (Port == GPIOA_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        }
        if constexpr (Port == GPIOB_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
        }
        if constexpr (Port == GPIOC_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
        }
        if constexpr (Port == GPIOD_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
        }
        if constexpr (Port == GPIOE_BASE)
        {
            RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;
        }
        if constexpr (PIN <= 7)
        {
            ((GPIO_TypeDef *)Port)->CRL |= 0x3UL << (4 * PIN);
            ((GPIO_TypeDef *)Port)->CRL |= 0x3UL << (4 * PIN + 2);
        }
        else
        {
            ((GPIO_TypeDef *)Port)->CRH |= 0x3UL << (4 * (PIN - 8));
            ((GPIO_TypeDef *)Port)->CRH |= 0x3UL << (4 * (PIN - 8) + 2);
        }
    }


    template <
        unsigned long Port,
        unsigned char PIN>
    void GPIO<Port, PIN>::Write(bool enable)
    {
        if (enable)
        {
            ((GPIO_TypeDef *)Port)->ODR |= 0x1UL << PIN;
        }
        else
        {
            ((GPIO_TypeDef *)Port)->ODR &= ~(0x1UL << PIN);
        }
    }

    template <
        unsigned long Port,
        unsigned char PIN>
    bool GPIO<Port, PIN>::Read()
    {
        return (((GPIO_TypeDef *)Port)->IDR & (0x1UL << PIN));
    }

}// Hardware
