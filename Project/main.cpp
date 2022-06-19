#include "..\Sources\Board\STM32F100C4T6\stm32f100xb.h"
#include "..\Sources\Board\GPIO.h"


typedef Hardware::GPIO<GPIOC_BASE, 13> LED;

int main()
{
  LED::InitOutputPushPull();
  while (1)
  {
    LED::Write(false);
    int delay = 3200000;
    while (delay--)
    {
    }
    LED::Write(true);
    delay = 3200000;
    while (delay--)
    {
    }
  }
}
