#ifndef _THREADS_H_
#define _THREADS_H_

namespace Utils
{

    class ThreadBase
    {

    public:
        static const unsigned long SLEEPINFINITE = 0xFFFFFFFF;
        enum States
        {
            StateUnknown = 0,
            StateInit = 1,
            StateIdle = 2,
        };
        virtual void Init(unsigned int threadTickFrequency);
        virtual void OnTick();
        virtual void Sleep(unsigned int milliSeconds);
        virtual void Run();

    protected:
        unsigned int _threadTickFrequency = 0;
        unsigned int _sleep = 0;
        States _currentState = StateUnknown;
        States _nextState = StateUnknown;
    };

    void ThreadBase::Init(unsigned int threadTickFrequency)
    {
        _threadTickFrequency = threadTickFrequency;
        _currentState = StateInit;
        _nextState = StateIdle;
    }

    void ThreadBase::OnTick()
    {
        if (_sleep)
        {
            _sleep--;
        }
        if (_sleep)
        {
            return;
        }
    }

    void ThreadBase::Run()
    {
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
        break;
        case StateIdle:
        {
        }
        break;
        }
    }

    void ThreadBase::Sleep(unsigned int milliSeconds)
    {
        if (1.0 / (milliSeconds / 1000.0) > _threadTickFrequency)
        {
            return;
        }
        _sleep += milliSeconds * (_threadTickFrequency / 1000);
    }
} // namespace Utils

#endif //_THREADS_H_