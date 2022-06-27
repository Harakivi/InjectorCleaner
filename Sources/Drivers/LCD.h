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
            };
            typedef ThreadBase Base;
            void Init(unsigned int threadTickFrequency);
            void OnTick();
            void SendCommand(unsigned char command);
            void String(char const *Data);
            void Clear();
            void DisplayEnable(bool dispEnable, bool cursorEnable, bool cursorBlink);
            void SetPos(unsigned char X, unsigned char Y);
            States GetState();

        protected:
            bool _initied = false;
            bool _waitEnableClear = false;
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
                Clear();
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
            if (_sleep)
            {
                return;
            }
            if (_waitEnableClear)
            {
                EnablePin::Write(false);
                _waitEnableClear = false;
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
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::String(char const *Data)
        {
            if (Data)
            {
                _nextState = _currentState;
                _currentState = StateSendData;
                for (int i = _countDataToSend; Data[i] && i < (CollumnCnt * LinesCnt); i++)
                {
                    _dataToSend[i] = Data[i];
                    _countDataToSend++;
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
                    SetData(_dataToSend[_pointerToDataSend] >> 4);
                    EnablePin::Write(true);
                    _waitEnableClear = true;
                    inFuncPos++;
                    Sleep(1);
                    return;
                }
                break;
                case 1:
                {
                    SetData(_dataToSend[_pointerToDataSend]);
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
        void LCD<D4Pin, D5Pin, D6Pin, D7Pin, EnablePin, RegSelectPin, CollumnCnt, LinesCnt>::Clear()
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