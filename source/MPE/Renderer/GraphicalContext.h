#pragma once

namespace MPE
{
    class GraphicalContext
    {
    private:
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}