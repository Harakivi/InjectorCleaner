#include "..\Sources\Board\STM32F100C4T6\stm32f100xb.h"
#include "..\Sources\Board\GPIO.h"
#include "..\Sources\Board\Time.h"


typedef Hardware::GPIO<GPIOC_BASE, 13> LED;;

int main()
{
  Time::GlobalTime.Init(24000000);
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
