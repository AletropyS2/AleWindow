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
			const char* Title;
			int Width;
			int Height;
		};

		virtual ~Window() = default;

		virtual bool MakeContextCurrent() = 0;

		virtual void PollEvents() = 0;
		virtual void SwapBuffers() = 0;

		inline const bool ShouldClose() { return m_ShouldClose; }
		inline void SleepMargin(int sleepMargin) { m_SleepMargin = sleepMargin; }

	
	protected:
		int m_SleepMargin = 10;
		bool m_ShouldClose = false;
		WindowProps* m_Props;
		RenderingAPI m_RenderingAPI;
	};
}