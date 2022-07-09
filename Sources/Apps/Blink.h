#ifndef _BLINK_H_
#define _BLINK_H_

namespace Apps
{
    template <typename LED, unsigned int _period_ms>
    class Blink : Utils::ThreadBase
    {
        typedef Utils::ThreadBase Base;

    public:
        enum States
        {
            StateUnknown = 0,
            StateInit = 1,
            StateIdle = 2,
            StateToggle,
        };

        void Init(unsigned int threadTickFrequency)
        {
            Base::Init(threadTickFrequency);
            LED::InitOutputPushPull();
            LED::Write(true);
            _currentState = StateInit;
            _nextState = StateIdle;
        }
        void BlinkEnable(bool Enable)
        {
            if (Enable)
            {
                _currentState = StateToggle;
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
            case StateToggle:
            {
                LedToggle();
            }
            break;
            case StateIdle:
            {
            }
            break;
            }
        }

    protected:
        void LedToggle()
        {
            LED::Toggle();
            Sleep(_period_ms);
        }

        States _currentState = StateUnknown;
        States _nextState = StateUnknown;
    };
}

#endif //_BLINK_H_