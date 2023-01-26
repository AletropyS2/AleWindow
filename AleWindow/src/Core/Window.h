#pragma once

#include <iostream>
#include <functional>
#include <array>
#include <vector>



namespace Ale
{
	enum KeyAction
	{
		PRESS = 0, RELEASE = 1
	};

	enum RenderingAPI
	{
		OPENGL,
		DIRECTX
	};

	class Window
	{
	public:

		struct WindowProps
		{
			const char* Title = "Default Window";
			int Width = 1280;
			int Height = 720;
		};

		virtual ~Window() = default;

		virtual bool MakeContextCurrent(RenderingAPI api) = 0;

		virtual void PollEvents() = 0;
		virtual void SwpBuffers() = 0;

		virtual void SetKeyCallback(const std::function<void(int, int)>& callback) = 0;
		virtual void SetMouseMoveCallback(const std::function<void(int, int)>& callback) = 0;
		virtual void SetMouseScrollCallback(const std::function<void(int)>& callback) = 0;
		virtual void SetWindowSizeCallback(const std::function<void(int, int, int, int)>& callback) = 0;

		inline const bool ShouldClose() { return m_ShouldClose; }
		inline void SleepMargin(int sleepMargin) { m_SleepMargin = sleepMargin; }
	protected:
		virtual void KeyEvent(int keycode, int action) = 0;
		virtual void MouseMoveEvent(int x, int y) = 0;
		virtual void MouseScrollEvent(int delta) = 0;
		virtual void WindowSizeEvent(int x, int y, int width, int height) = 0;

	
	protected:
		int m_SleepMargin = 10;
		bool m_ShouldClose = false;
		WindowProps* m_Props;
		RenderingAPI m_RenderingAPI;

		std::function<void(int, int)>* m_KeyCallback;
		std::function<void(int, int)>* m_MouseMoveCallback;
		std::function<void(int)>* m_MouseScrollCallback;
		std::function<void(int, int, int, int)>* m_WindowSizeCallback;
	};
}