#ifndef _DRIVERS_H_
#define _DRIVERS_H_

#include "..\Sources\Drivers\LCD.h"
#include "..\Sources\Apps\Blink.h"

namespace Hardware
{
    namespace InjectorCleaner
    {
        template <class Board>
        class Drivers
        {
        public:
            typedef Hardware::Drivers::LCD<typename Board::LcdD4Pin, typename Board::LcdD5Pin, typename Board::LcdD6Pin, typename Board::LcdD7Pin, typename Board::LcdEnablePin, typename Board::LcdRegSelectPin, 20, 4> LCD2004Type;
            static LCD2004Type Display;

            typedef Time::SystemTimeClass TimeType;
            static TimeType GlobalTime;

            typedef Apps::Blink<typename Board::LED, 1000> BlinkerType;
            static BlinkerType Blinker;

            static void ThreadsHandler()
            {
                Display.OnTick();
                Blinker.OnTick();
            }

            static void Run()
            {
            }

            static void Init()
            {
                Board::ThreadsTimer::SetUpdateCallBack(ThreadsHandler);
                GlobalTime.Init(Board::CoreClock::GetSysCLKFrequency());

                Display.Init(Board::ThreadsTimer::GetFrequency());
                while (Display.GetState() != Display.StateIdle)
                {
                }

                Blinker.Init(Board::ThreadsTimer::GetFrequency());

                while (Blinker.GetState() != Blinker.StateIdle)
                {
                }

                Blinker.BlinkEnable(true);

                Display.String("InitComplete");
            }
        };
        template <class Board>
        Drivers<Board>::LCD2004Type Drivers<Board>::Display;

        template <class Board>
        Drivers<Board>::TimeType Drivers<Board>::GlobalTime;

        template <class Board>
        Drivers<Board>::BlinkerType Drivers<Board>::Blinker;

    } // namespace Drivers
} // namespace Hardware

#endif //_DRIVERS_H_