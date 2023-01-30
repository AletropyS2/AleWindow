#pragma once


#ifdef _WIN64
#include "Platform/Windows/WindowsWindow.h"
#define WindowPtr(x) new Ale::WindowsWindow(x)
#else
#error "AleWindow just support windows for now!"
#endif

Ale::Window* CreateAleWindow(Ale::Window::WindowProps* props = nullptr)
{
	if (props == nullptr)
	{
		props = new Ale::Window::WindowProps{ "Default Window", 1280, 720 };
	}

	return WindowPtr(props);
}