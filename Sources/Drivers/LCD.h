#ifndef _LCD_H
#define _LCD_H

namespace Hardware
{
    namespace Drivers
    {

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        class LCD : Utils::ThreadBase
        {
        public:
            enum States
            {
                StateUnknown = 0,
                StateInit = 1,
                StateIdle = 2,
                StateSendCommand,
                StateSendData,
                StateSendBuffer,
            };
            typedef ThreadBase Base;
            void Init(unsigned int threadTickFrequency);
            void OnTick();
            // void String(char const *Data);
            // static void String(void *_callbackParam, char const *Data);
            void SendBuffer();
            static void SendBuffer(void *_callbackParam);
            void BufferString(char const *Data, unsigned char X, unsigned char Y);
            static void BufferString(void *_callbackParam, char const *Data, unsigned char X, unsigned char Y);
            void ClearBuffer();
            static void ClearBuffer(void *_callbackParam);
            // void Char(char const Data);
            // static void Char(void *_callbackParam, char const Data);
            void DisplayEnable(bool dispEnable, bool cursorEnable, bool cursorBlink);
            States GetState();
            static void GetState(void *_callbackParam, Base::States &state);
            void Run();

        protected:
            bool _initied = false;
            unsigned char _commandToSend;
            unsigned char _dataToSend[CollumnCnt * LinesCnt];
            unsigned char _countDataToSend;
            unsigned char _pointerToDataSend;
            States _currentState = StateUnknown;
            States _nextState = StateUnknown;
            void LcdInit();
            void WriteCommand();
            void WriteData();
            void SetData(unsigned char Data);
            void ClearDisp();
            void SendCommand(unsigned char command);
            void SetPos(unsigned char X, unsigned char Y);
            bool _waitEnableClear = false;
        };
        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::Init(unsigned int threadTickFrequency)
        {
            Base::Init(threadTickFrequency);
            _currentState = StateInit;
            _nextState = StateIdle;
            _commandToSend = 0;
            _countDataToSend = 0;
            _pointerToDataSend = 0;
        }
        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::LcdInit()
        {
            static unsigned char inFuncPos = 0;
            switch (inFuncPos)
            {
            case 0:
            {
                D4Pin::InitOutputOpenDrain();
                D5Pin::InitOutputOpenDrain();
                D6Pin::InitOutputOpenDrain();
                D7Pin::InitOutputOpenDrain();
                EnablePin::InitOutputOpenDrain();
                RegSelectPin::InitOutputOpenDrain();
                D4Pin::Write(false);
                D5Pin::Write(false);
                D6Pin::Write(false);
                D7Pin::Write(false);
                EnablePin::Write(false);
                RegSelectPin::Write(true);
                Sleep(40);
                inFuncPos++;
                return;
            }
            break;
            case 1:
            {
                RegSelectPin::Write(false);
                SetData(0x03);
                EnablePin::Write(true);
                _waitEnableClear = true;
                Sleep(5);
                inFuncPos++;
                return;
            }
            case 2:
            {
                RegSelectPin::Write(false);
                SetData(0x03);
                EnablePin::Write(true);
                _waitEnableClear = true;
                Sleep(5);
                inFuncPos++;
                return;
            }
            case 3:
            {
                RegSelectPin::Write(false);
                SetData(0x03);
                EnablePin::Write(true);
                _waitEnableClear = true;
                Sleep(5);
                inFuncPos++;
                return;
            }
            break;
            case 4:
            {
                RegSelectPin::Write(false);
                SetData(0x02);
                EnablePin::Write(true);
                _waitEnableClear = true;
                Sleep(5);
                inFuncPos++;
                return;
            }
            break;
            case 5:
            {
                SendCommand(0x28);
                inFuncPos++;
                return;
            }
            break;
            case 6:
            {
                SendCommand(0x0C);
                inFuncPos++;
                return;
            }
            break;
            case 7:
            {
                SendCommand(0x01);
                inFuncPos++;
                return;
            }
            break;
            case 8:
            {
                SendCommand(0x06);
                inFuncPos++;
                return;
            }
            break;
            case 9:
            {
                SendCommand(0x02);
                inFuncPos++;
                return;
            }
            break;
            case 10:
            {
                ClearDisp();
                inFuncPos++;
                return;
            }
            break;
            case 11:
            {
                _currentState = _nextState;
            }
            break;
            default:
            {
                return;
            }
            break;
            }
            _initied = true;
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::OnTick()
        {
            Base::OnTick();
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::Run()
        {
            Base::Run();
            if (_sleep)
            {
                return;
            }
            if (_waitEnableClear)
            {
                EnablePin::Write(false);
                _waitEnableClear = false;
                Sleep(1);
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
                LcdInit();
            }
            break;
            case StateSendCommand:
            {
                WriteCommand();
            }
            break;
            case StateSendData:
            {
                WriteData();
            }
            break;
            case StateSendBuffer:
            {
                WriteData();
            }
            break;
            case StateIdle:
            {
            }
            break;
            }
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::WriteCommand()
        {
            static unsigned char inFuncPos = 0;
            if (_commandToSend)
            {
                RegSelectPin::Write(false);
                switch (inFuncPos)
                {
                case 0:
                {
                    SetData(_commandToSend >> 4);
                    EnablePin::Write(true);
                    _waitEnableClear = true;
                    inFuncPos++;
                    Sleep(1);
                    return;
                }
                break;
                case 1:
                {
                    SetData(_commandToSend);
                    EnablePin::Write(true);
                    _waitEnableClear = true;
                    _currentState = _nextState;
                    _nextState = StateIdle;
                    _commandToSend = 0;
                    inFuncPos = 0;
                    Sleep(1);
                    return;
                }
                break;

                default:
                    inFuncPos = 0;
                    break;
                }
            }
            else
            {
                _currentState = _nextState;
                _nextState = StateIdle;
            }
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::SendCommand(unsigned char command)
        {
            if (command)
            {
                _nextState = _currentState;
                _currentState = StateSendCommand;
                _commandToSend = command;
            }
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::BufferString(void *_callbackParam, char const *Data, unsigned char X, unsigned char Y)
        {
            LCD *me = (LCD *)_callbackParam;
            if (!me)
            {
                return;
            }

            me->BufferString(Data, X, Y);
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::BufferString(char const *Data, unsigned char X, unsigned char Y)
        {
            if (Data)
            {
                unsigned char startPos = 0;
                if (X > CollumnCnt || Y > LinesCnt)
                {
                    return;
                }
                switch (Y)
                {
                case 0:
                    break;
                case 1:
                    startPos = CollumnCnt * 2;
                    break;
                case 2:
                    startPos = CollumnCnt * 1;
                    break;
                case 3:
                    startPos = CollumnCnt * 3;
                    break;
                };
                unsigned char currentPos = startPos;
                for (int i = startPos; Data[i] && currentPos < (CollumnCnt * LinesCnt); i++)
                {
                    _dataToSend[currentPos++] = Data[i];
                    if (!(currentPos % 20))
                    {
                        switch (currentPos / 20)
                        {
                        case 1:
                            currentPos = CollumnCnt * 2;
                            break;
                        case 2:
                            currentPos = CollumnCnt * 3;
                            break;
                        case 3:
                            currentPos = CollumnCnt * 1;
                            break;
                        }
                    }
                }
            }
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::ClearBuffer()
        {
            _countDataToSend = 0;
            _pointerToDataSend = 0;
            for (int i = 0; i < (CollumnCnt * LinesCnt); i++)
            {
                _dataToSend[i] = 0;
            }
            ClearDisp();
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::ClearBuffer(void *_callbackParam)
        {
            LCD *me = (LCD *)_callbackParam;
            if (!me)
            {
                return;
            }

            me->ClearBuffer();
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::SendBuffer()
        {
            SetPos(0, 0);
            _countDataToSend = CollumnCnt * LinesCnt;
            _pointerToDataSend = 0;
            _nextState = StateSendBuffer;
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::SendBuffer(void *_callbackParam)
        {
            LCD *me = (LCD *)_callbackParam;
            if (!me)
            {
                return;
            }

            me->SendBuffer();
        }

        // template <class D4Pin,
        //           class D5Pin,
        //           class D6Pin,
        //           class D7Pin,
        //           class EnablePin,
        //           class RegSelectPin,
        //           unsigned int CollumnCnt,
        //           unsigned int LinesCnt>
        // void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::String(char const *Data)
        // {
        //     if (Data)
        //     {
        //         _nextState = _currentState;
        //         _currentState = StateSendData;
        //         for (int i = _countDataToSend + _pointerToDataSend; Data[i] && i < (CollumnCnt * LinesCnt); i++)
        //         {
        //             _dataToSend[i] = Data[i];
        //             _countDataToSend++;
        //         }
        //     }
        // }

        // template <class D4Pin,
        //           class D5Pin,
        //           class D6Pin,
        //           class D7Pin,
        //           class EnablePin,
        //           class RegSelectPin,
        //           unsigned int CollumnCnt,
        //           unsigned int LinesCnt>
        // void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::String(void *_callbackParam, char const *Data)
        // {
        //     LCD *me = (LCD *)_callbackParam;
        //     if (!me)
        //     {
        //         return;
        //     }

        //     me->String(Data);
        // }

        // template <class D4Pin,
        //           class D5Pin,
        //           class D6Pin,
        //           class D7Pin,
        //           class EnablePin,
        //           class RegSelectPin,
        //           unsigned int CollumnCnt,
        //           unsigned int LinesCnt>
        // void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::Char(char const Data)
        // {
        //     if (Data)
        //     {
        //         _nextState = _currentState;
        //         _currentState = StateSendData;
        //         _dataToSend[_countDataToSend + _pointerToDataSend] = Data;
        //         _countDataToSend++;
        //     }
        // }

        // template <class D4Pin,
        //           class D5Pin,
        //           class D6Pin,
        //           class D7Pin,
        //           class EnablePin,
        //           class RegSelectPin,
        //           unsigned int CollumnCnt,
        //           unsigned int LinesCnt>
        // void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::Char(void *_callbackParam, char const Data)
        // {
        //     LCD *me = (LCD *)_callbackParam;
        //     if (!me)
        //     {
        //         return;
        //     }

        //     me->Char(Data);
        // }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::WriteData()
        {
            static unsigned char inFuncPos = 0;
            if (_countDataToSend)
            {
                RegSelectPin::Write(true);
                switch (inFuncPos)
                {
                case 0:
                {
                    if (_dataToSend[_pointerToDataSend])
                    {
                        SetData(_dataToSend[_pointerToDataSend] >> 4);
                    }
                    else
                    {
                        SetData(0x20 >> 4);
                    }
                    EnablePin::Write(true);
                    _waitEnableClear = true;
                    inFuncPos++;
                    Sleep(1);
                    return;
                }
                break;
                case 1:
                {
                    if (_dataToSend[_pointerToDataSend])
                    {
                        SetData(_dataToSend[_pointerToDataSend]);
                    }
                    else
                    {
                        SetData(0x20);
                    }
                    EnablePin::Write(true);
                    _waitEnableClear = true;
                    _countDataToSend--;
                    _pointerToDataSend++;
                    if (!_countDataToSend)
                    {
                        _currentState = _nextState;
                        _nextState = StateIdle;
                        _pointerToDataSend = 0;
                    }

                    inFuncPos = 0;
                    Sleep(1);
                    return;
                }
                break;

                default:
                    inFuncPos = 0;
                    break;
                }
            }
            else
            {
                _currentState = _nextState;
                _nextState = StateIdle;
            }
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::ClearDisp()
        {
            SendCommand(0x01);
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::DisplayEnable(bool dispEnable, bool cursorEnable, bool cursorBlink)
        {
            unsigned char command = 0x8;
            command |= (dispEnable << 2) | (cursorEnable << 1) | (cursorBlink);
            SendCommand(command);
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::SetPos(unsigned char X, unsigned char Y)
        {
            if (X > CollumnCnt || Y > LinesCnt)
            {
                return;
            }
            unsigned char command = 0x80;
            switch (Y)
            {
            case 0:
                SendCommand(command | X);
                break;
            case 1:
                SendCommand(command | (X + 0x40));
                break;
            case 2:
                SendCommand(command | (X + 0x14));
                break;
            case 3:
                SendCommand(command | (X + 0x54));
                break;
            };
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::States
        LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::GetState()
        {
            return _currentState;
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::GetState(void *_callbackParam, Base::States &state)
        {
            LCD *me = (LCD *)_callbackParam;
            if (!me)
            {
                return;
            }

            state = (Base::States)me->GetState();
        }

        template <class D4Pin,
                  class D5Pin,
                  class D6Pin,
                  class D7Pin,
                  class EnablePin,
                  class RegSelectPin,
                  unsigned int CollumnCnt,
                  unsigned int LinesCnt>
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::SetData(unsigned char rawData)
        {
            D4Pin::Write(rawData & 0x01);
            D5Pin::Write((rawData >> 1) & 0x01);
            D6Pin::Write((rawData >> 2) & 0x01);
            D7Pin::Write((rawData >> 3) & 0x01);
        }
    } // namespace Drivers
} // namespace Hardware

#endif //_LCD_H