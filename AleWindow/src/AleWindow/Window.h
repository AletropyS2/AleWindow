#pragma once

#include <iostream>

namespace Ale
{
    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void PollEvents() = 0;
        virtual void SwapBuffers() = 0;

        const bool ShouldClose() { return m_ShouldClose; }
    protected:
        bool m_ShouldClose;
    };
}
