#include "..\Sources\Board\STM32F100C4T6\stm32f100xb.h"
#include "..\Sources\Board\GPIO.h"
#include "..\Sources\Board\Clock.h"
#include "..\Sources\Board\Time.h"
#include "..\Sources\Apps\Blink.h"

#define HSI_OSCILLATOR 8000000
#define HSE_OSCILLATOR 8000000
#define DESIRED_CORE_CLOCK 24000000

typedef Hardware::GPIO<C, 13> LED;
typedef Hardware::Clock<HSI_OSCILLATOR, HSE_OSCILLATOR> CoreClock;
typedef Time::SystemTimeClass GlobalTime;

Apps::Blink<LED> Blinker(1000);

int main()
{
  CoreClock::Init(DESIRED_CORE_CLOCK);
  GlobalTime::Init(CoreClock::GetCurrentCoreFrequency(), SystemTick::TimeCallBack);
  LED::InitOutputPushPull();
  while (1)
  {
    Blinker.Run(GlobalTime::GetTime_ms());
  }
}