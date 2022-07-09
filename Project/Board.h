#ifndef _BOARD_H_
#define _BOARD_H_

#include "..\Sources\Board\STM32F100C4T6\stm32f100xb.h"
#include "..\Sources\Board\WatchDogTimer.h"
#include "..\Sources\Board\Interrupts.h"
#include "..\Sources\Board\GPIO.h"
#include "..\Sources\Board\Clock.h"
#include "..\Sources\Board\Time.h"
#include "..\Sources\Board\Timer.h"

namespace Hardware
{
    namespace InjectorCleaner
    {
        class Board
        {
        public:
            static const unsigned int HSE_Oscillator = 8000000;
            static const unsigned int Core_Clock = 24000000;

            typedef Hardware::WatchDogTimer WDG_Timer;

            typedef Hardware::GPIO<Hardware::C, 13> LED;
            typedef Hardware::Clock<HSE_Oscillator> CoreClock;

            typedef Hardware::Timer<Hardware::Timer1, CoreClock> ThreadsTimer;
            typedef Hardware::Timer<Hardware::Timer3, CoreClock> PWMTimer;
            // typedef Hardware::Timer<Hardware::Timer4, CoreClock> PWMTimer2;

            typedef Hardware::GPIO<Hardware::B, 12> LcdD4Pin;
            typedef Hardware::GPIO<Hardware::B, 13> LcdD5Pin;
            typedef Hardware::GPIO<Hardware::B, 14> LcdD6Pin;
            typedef Hardware::GPIO<Hardware::B, 15> LcdD7Pin;
            typedef Hardware::GPIO<Hardware::B, 11> LcdEnablePin;
            typedef Hardware::GPIO<Hardware::B, 10> LcdRegSelectPin;

            static void Init()
            {
                CoreClock::SetSysCLKFrequency(Core_Clock);
                WDG_Timer::Init(10000);

                ThreadsTimer::InitCounter(1000, true);
                PWMTimer::PWMCnanStruct PWNChan1;
                PWMTimer::PWMCnanStruct PWNChan2;
                PWMTimer::PWMCnanStruct PWNChan3;
                PWMTimer::PWMCnanStruct PWNChan4;
                PWNChan1.dutyCycle = 1;
                PWNChan1.invert = false;
                PWNChan2.dutyCycle = 2.5;
                PWNChan2.invert = false;
                PWNChan3.dutyCycle = 3.4;
                PWNChan3.invert = true;
                PWNChan4.dutyCycle = 7.8;
                PWNChan4.invert = true;
                //                PWMTimer2::PWMCnanStruct PWN2Chan1;
                //                PWMTimer2::PWMCnanStruct PWN2Chan2;
                //                PWMTimer2::PWMCnanStruct PWN2Chan3;
                //                PWMTimer2::PWMCnanStruct PWN2Chan4;
                //                PWN2Chan1.dutyCycle = 1;
                //                PWN2Chan1.invert = false;
                //                PWN2Chan2.dutyCycle = 2.5;
                //                PWN2Chan2.invert = false;
                //                PWN2Chan3.dutyCycle = 3.4;
                //                PWN2Chan3.invert = true;
                //                PWN2Chan4.dutyCycle = 7.8;
                // PWN2Chan4.invert = true;
                PWMTimer::InitPWM(25, false, PWNChan1, PWNChan2, PWNChan3, PWNChan4);
                // PWMTimer2::InitPWM(25, false, PWN2Chan1, PWN2Chan2, PWN2Chan3, PWN2Chan4);

                PWMTimer::Start();
                // PWMTimer2::Start();
                
                WDG_Timer::StartCounter();
            }
        };
    } // namespace InjectorCleaner

} // namespace Hardware

#endif //_BOARD_H_