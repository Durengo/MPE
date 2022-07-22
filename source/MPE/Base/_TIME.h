#pragma once

namespace MPE
{
    class _TIME
    {
    private:
        float SYS_TIME;

    public:
        _TIME(float time = 0.0f)
            : SYS_TIME(time)
        {
        }

        float GetSeconds() const { return SYS_TIME; }
        float GetMilliSeconds() const { return SYS_TIME * 1000.0f; }

        operator float() const { return SYS_TIME; }
    };
}