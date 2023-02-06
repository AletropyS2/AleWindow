#pragma once

#include "AleWindow/Window.h"

#ifdef __linux__

    #include "Platform/Linux/LinuxWindow.h"

#elif

    #include "Platform/Windows/WindowsWindow.h"

#endif

namespace Ale
{

    Window* CreateWindow(unsigned int width, unsigned int height, const char* title);

#ifdef __linux__

    Window* CreateWindow(unsigned int width, unsigned int height, const char* title)
    {
        #include "Platform/Linux/LinuxWindow.h"
        return new LinuxWindow(width, height, title);
    }

#endif

}