#pragma once

#include "AleWindow/Window.h"
#include "AleWindow/Debug.h"

#ifdef __linux__
    #include "Platform/Linux/LinuxWindow.h"
#elif _WIN64
    #include "Platform/Windows/WindowsWindow.h"
#endif

namespace Ale
{

    Window* ALE_API CreateAleWindow(unsigned int width = 1280, unsigned int height = 720, const char* title = "AleWindow")
    {
        #ifdef __linux__
        return new LinuxWindow(width, height, title);
        #elif _WIN64
        return new WindowsWindow(width, height, title);
        #else
        ALE_ERROR("Platform not supported yet!");
        return nullptr;
        #endif
    }

}
