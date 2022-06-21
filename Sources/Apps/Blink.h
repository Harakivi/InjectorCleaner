#ifndef _BLINK_H_
#define _BLINK_H_

namespace Apps
{
    template <typename LED>
    class Blink
    {
    public:
        Blink(unsigned int period_ms)
        {
            _period_ms = period_ms;
        }
        void Run(unsigned long currentTime)
        {
            static unsigned long lastTickTime = 0;
            if((currentTime - lastTickTime)>= _period_ms)
            {
                OnTick();
                lastTickTime = currentTime;
            }
        }

    private:
        unsigned short _period_ms = 0;
        void OnTick()
        {
            LED::Toggle();
        }
    };
}

#endif //_BLINK_H_