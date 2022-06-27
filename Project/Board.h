#ifndef _BOARD_H_
#define _BOARD_H_

#include "..\Sources\Board\STM32F100C4T6\stm32f100xb.h"
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

            typedef Hardware::GPIO<Hardware::C, 13> LED;
            typedef Hardware::Clock<HSE_Oscillator> CoreClock;
            
            typedef Hardware::Timer<Hardware::Timer1, CoreClock> ThreadsTimer;

            typedef Hardware::GPIO<Hardware::B, 12> LcdD4Pin;
            typedef Hardware::GPIO<Hardware::B, 13> LcdD5Pin;
            typedef Hardware::GPIO<Hardware::B, 14> LcdD6Pin;
            typedef Hardware::GPIO<Hardware::B, 15> LcdD7Pin;
            typedef Hardware::GPIO<Hardware::B, 11> LcdEnablePin;
            typedef Hardware::GPIO<Hardware::B, 10> LcdRegSelectPin;

            static void Init()
            {
                CoreClock::SetSysCLKFrequency(Core_Clock);

                ThreadsTimer::InitCounter(1000, true);
                
                ThreadsTimer::Start();
            }
        };
    } // namespace InjectorCleaner

} // namespace Hardware

#endif //_BOARD_H_