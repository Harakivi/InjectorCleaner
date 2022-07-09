#ifndef _GUI_H_
#define _GUI_H_

#include <stdio.h>

namespace Apps
{
    namespace Gui
    {
        class TestGui : Utils::ThreadBase
        {
            typedef Utils::ThreadBase Base;
            typedef Utils::CallbackWrapper<char const *, unsigned char, unsigned char> WriteToBufferCallBackType;
            typedef Utils::CallbackWrapper<> SendBufferCallBackType;
            typedef Utils::CallbackWrapper<> ClearBufferCallBackType;
            typedef Utils::CallbackWrapper<Utils::ThreadBase::States &> GetDisplayStateCallBackType;

        public:
            GetDisplayStateCallBackType GetDisplayStateCallBack;
            WriteToBufferCallBackType WriteToBufferCallBack;
            SendBufferCallBackType SendBufferCallBack;
            ClearBufferCallBackType ClearBufferCallBack;
            enum States
            {
                StateUnknown = 0,
                StateInit = 1,
                StateIdle = 2,
                StateSendChar,
            };
            void Init(unsigned int threadTickFrequency) override
            {
                Base::Init(threadTickFrequency);
                _currentState = StateInit;
                _nextState = StateIdle;
            }
            void Enable(bool Enable)
            {
                if (Enable)
                {
                    _currentState = StateSendChar;
                }
                else
                {
                    _currentState = StateIdle;
                }
            }

            States GetState()
            {
                return _currentState;
            }

            void OnTick()
            {
                Base::OnTick();
            }

            void Run()
            {
                Base::Run();
                if (_sleep)
                {
                    return;
                }
                switch (_currentState)
                {
                case StateUnknown:
                {
                }
                break;
                case StateInit:
                {
                    _currentState = _nextState;
                }
                case StateSendChar:
                {
                    SendNewChar();
                }
                break;
                case StateIdle:
                {
                }
                break;
                }
            }

        protected:
            void SendNewChar()
            {
                static unsigned char inFuncPos = 0;
                static char sendBuffer[80] = {0};
                static int counter = 0;
                switch (inFuncPos)
                {
                case 0:
                {
                    Base::States displayState = (Base::States)StateUnknown;
                    GetDisplayStateCallBack(displayState);
                    if (displayState == Base::States::StateIdle)
                    {
                        ClearBufferCallBack();
                        inFuncPos++;
                    }
                }
                break;
                case 1:
                {
                    Base::States displayState = (Base::States)StateUnknown;
                    GetDisplayStateCallBack(displayState);
                    if (displayState == Base::States::StateIdle)
                    {
                        sprintf(sendBuffer, "%d", counter);
                        WriteToBufferCallBack(sendBuffer, 0, 0);
                        SendBufferCallBack();
                        counter++;
                        Sleep(1000);
                    }
                }
                break;
                }
            }

            States _currentState = StateUnknown;
            States _nextState = StateUnknown;
        };

    } // namespace Gui
} // namespace Apps
#endif //_GUI_H_