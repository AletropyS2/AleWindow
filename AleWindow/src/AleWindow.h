#pragma once

#include "AleWindow/Window.h"

#ifdef __linux__
    #include "Platform/Linux/LinuxWindow.h"
#elif _WIN64
    #include "Platform/Windows/WindowsWindow.h"
#endif

namespace Ale
{

    Window* CreateAleWindow(unsigned int width, unsigned int height, const char* title);

#ifdef __linux__

    Window* CreateAleWindow(unsigned int width, unsigned int height, const char* title)
    {
        return new LinuxWindow(width, height, title);
    }

#elif _WIN64
    Window* CreateAleWindow(unsigned int width, unsigned int height, const char* title)
    {
        return new WindowsWindow(width, height, title);
    }
#endif

}