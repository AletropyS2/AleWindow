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

		virtual void MakeContextCurrent() override;

		virtual void PollEvents() override;
		virtual void SwpBuffers() override;

		virtual void SetKeyCallback(const std::function<void(int, int)>& callback) override;
		virtual void SetMouseMoveCallback(const std::function<void(int, int)>& callback) override;
		virtual void SetMouseScrollCallback(const std::function<void(int)>& callback) override;
		virtual void SetWindowSizeCallback(const std::function<void(int, int, int, int)>& callback) override;

	private:
		virtual void KeyEvent(int keycode, int action) override;
		virtual void MouseMoveEvent(int x, int y) override;
		virtual void MouseScrollEvent(int delta) override;
		virtual void WindowSizeEvent(int x, int y, int width, int height) override;

		static WindowsWindow* GetWindow(HWND hwnd);

	private:
		static LRESULT CALLBACK WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam);
	private:
		HWND m_Hwnd;
		HINSTANCE m_HInstance;
		Window::WindowProps* m_Props;

		static std::array<std::pair<HWND, WindowsWindow*>, 32> m_Windows;
	};
}