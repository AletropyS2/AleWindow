#pragma once

#ifdef _WIN64
#include "Platform/Windows/WindowsWindow.h"
#define WindowPtr(x) new WindowsWindow(x)
#else
#error "AleWindow just support windows for now!"
#endif

namespace Ale
{

	Window* createWindow(Window::WindowProps* props = nullptr)
	{
		if (props == nullptr)
		{
			props = new Window::WindowProps{ "Default Window", 1280, 720 };
		}

		return WindowPtr(props);
	}
#ifdef _WIN64
	DxProps* getDxPropsFromWindow(Window* windowsWindow)
	{
		return ((WindowsWindow*)windowsWindow)->GetDxProps();
	}
#endif

}