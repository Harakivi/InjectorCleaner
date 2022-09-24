#ifndef _DRIVERS_H_
#define _DRIVERS_H_

#include "..\Sources\Drivers\LCD.h"
#include "..\Sources\Apps\Gui.h"
#include "..\Sources\Apps\Blink.h"

namespace Hardware
{
    namespace InjectorCleaner
    {
        template <class Board>
        class Drivers
        {
        public:
            // typedef Hardware::Drivers::LCD<typename Board::LcdD4Pin, typename Board::LcdD5Pin, typename Board::LcdD6Pin, typename Board::LcdD7Pin, typename Board::LcdEnablePin, typename Board::LcdRegSelectPin, 20, 4> LCD2004Type;
            // static LCD2004Type Display;

            typedef Time::SystemTimeClass TimeType;
            static TimeType GlobalTime;

            typedef Apps::Blink<typename Board::LED, 1000> BlinkerType;
            static BlinkerType Blinker;

            // typedef Apps::Gui::TestGui TestType;
            // static TestType TestInstance;

            static void ThreadsHandler()
            {
                //Display.OnTick();
                Blinker.OnTick();
                //TestInstance.OnTick();
            }

            static void Run()
            {
                //Display.Run();
                Blinker.Run();
                //TestInstance.Run();
            }

            static void Init()
            {
                Board::ThreadsTimer::SetUpdateCallBack(ThreadsHandler);
                GlobalTime.Init(Board::CoreClock::GetSysCLKFrequency());

                // Display.Init(Board::ThreadsTimer::GetFrequency());
                // Display.Init(Board::ThreadsTimer::GetFrequency());

                Blinker.Init(Board::ThreadsTimer::GetFrequency());

                //TestInstance.Init(Board::ThreadsTimer::GetFrequency());

                // TestInstance.GetDisplayStateCallBack.Set(LCD2004Type::GetState, &Display);
                // TestInstance.WriteToBufferCallBack.Set(LCD2004Type::BufferString, &Display);
                // TestInstance.SendBufferCallBack.Set(LCD2004Type::SendBuffer, &Display);
                // TestInstance.ClearBufferCallBack.Set(LCD2004Type::ClearBuffer, &Display);

                Blinker.BlinkEnable(true);
                //TestInstance.Enable(true);

                Board::ThreadsTimer::Start();
            }
        };
        //template <class Board>
        //Drivers<Board>::LCD2004Type Drivers<Board>::Display;

        template <class Board>
        Drivers<Board>::TimeType Drivers<Board>::GlobalTime;

        template <class Board>
        Drivers<Board>::BlinkerType Drivers<Board>::Blinker;

        //template <class Board>
        //Drivers<Board>::TestType Drivers<Board>::TestInstance;

    } // namespace Drivers
} // namespace Hardware

#endif //_DRIVERS_H_