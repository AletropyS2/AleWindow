#pragma once

#include <Windows.h>
#include "Core/Window.h"

namespace Ale
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(Window::WindowProps* props);
		~WindowsWindow() { };

		virtual bool MakeContextCurrent() override;

		virtual void PollEvents() override;
		virtual void SwapBuffers() override;

	private:
		void UpdateViewport();

		bool MakeOpenGLContext();
		void SwapOpenGLBuffers();
			
		static WindowsWindow* GetWindow(HWND hwnd);

	private:
		static LRESULT CALLBACK WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam);
	private:
		HWND m_Hwnd;
		HINSTANCE m_HInstance;
		Window::WindowProps* m_Props;

		static int m_WindowCount;
		static std::array<std::pair<HWND, WindowsWindow*>, 32> m_Windows;
	};
}