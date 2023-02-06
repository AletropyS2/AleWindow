#pragma once

#include "AleWindow/Window.h"

#ifdef __linux__
#include <X11/Xlib.h>
#include <X11/Xatom.h>

namespace Ale
{

    class LinuxWindow : public Window
    {
    public:
        LinuxWindow(unsigned int width, unsigned int height, const char* title);
        virtual ~LinuxWindow();

        virtual void PollEvents() override;
        virtual void SwapBuffers() override;
    private:
        Display* m_Display;
        ::Window m_Window;
        int m_Screen;
    };

}

#endif