#include "WindowsWindow.h"

#include <thread>
#include <chrono>
#include <gl/GL.h>

namespace Ale
{
	std::array<std::pair<HWND, WindowsWindow*>, 32> WindowsWindow::m_Windows;

	#define Sleep(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))

	WindowsWindow::WindowsWindow(Window::WindowProps* props)
		: m_HInstance(GetModuleHandle(NULL)), m_Props(props)
	{
		LPCWSTR windowClass = L"WindowCustomClass";

		const size_t cSize = strlen(props->Title) + 1;
		wchar_t* wTitle = new wchar_t[cSize];
		mbstowcs(wTitle, props->Title, cSize);

		WNDCLASSEX wc{};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.hInstance = m_HInstance;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wc.lpszClassName = windowClass;
		wc.lpszMenuName = NULL;
		wc.lpfnWndProc = WindowsWindow::WndProc;
		wc.style = 0;

		if (!RegisterClassEx(&wc))
		{
			std::cout << "[ AleWindow ] -> Cannot create window" << std::endl;
		}

		m_Hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			windowClass,
			wTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			props->Width, props->Height,
			NULL, NULL, m_HInstance, NULL
		);

		m_Windows[0] = std::make_pair(m_Hwnd, this);

		ShowWindow(m_Hwnd, SW_SHOW);
		UpdateWindow(m_Hwnd);
	}

	void WindowsWindow::MakeContextCurrent()
	{
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		HDC hdc = GetDC(m_Hwnd);

		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, pixelFormat, &pfd);

		HGLRC ctx = wglCreateContext(hdc);

		wglMakeCurrent(hdc, ctx);
	}

	void WindowsWindow::PollEvents()
	{
		MSG msg;

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Sleep(m_SleepMargin);
	}

	void WindowsWindow::SwpBuffers()
	{
		SwapBuffers(GetDC(m_Hwnd));
	}

	void WindowsWindow::SetKeyCallback(const std::function<void(int, int)>& callback)
	{
		m_KeyCallback = new std::function<void(int, int)>(callback);
	}

	void WindowsWindow::SetMouseMoveCallback(const std::function<void(int, int)>& callback)
	{
		m_MouseMoveCallback = new std::function<void(int, int)>(callback);
	}

	void WindowsWindow::SetMouseScrollCallback(const std::function<void(int)>& callback)
	{
		m_MouseScrollCallback = new std::function<void(int)>(callback);
	}

	void WindowsWindow::SetWindowSizeCallback(const std::function<void(int, int, int, int)>& callback)
	{
		m_WindowSizeCallback = new std::function<void(int, int, int, int)>(callback);
	}

	WindowsWindow* WindowsWindow::GetWindow(HWND hwnd)
	{
		for (auto& pair : m_Windows)
		{
			if (pair.first == hwnd)
			{
				return pair.second;
			}
		}
		return nullptr;
	}

	void WindowsWindow::KeyEvent(int keycode, int action)
	{
		if (m_KeyCallback)
			(*m_KeyCallback)(keycode, action);
	}

	void WindowsWindow::MouseMoveEvent(int x, int y)
	{
		if (m_MouseMoveCallback)
			(*m_MouseMoveCallback)(x, y);
	}

	void WindowsWindow::MouseScrollEvent(int delta)
	{
		if (m_MouseScrollCallback)
			(*m_MouseScrollCallback)(delta);
	}

	void WindowsWindow::WindowSizeEvent(int x, int y, int width, int height)
	{
		if (m_WindowSizeCallback)
			(*m_WindowSizeCallback)(x, y, width, height);
	}

	LRESULT WindowsWindow::WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* window = GetWindow(hwnd);

		switch (msg)
		{
		case WM_CLOSE:
			window->m_ShouldClose = true;
			PostQuitMessage(0);
		case WM_KEYDOWN:
			window->KeyEvent((int)wParam, 0);
			break;
		case WM_KEYUP:
			window->KeyEvent((int)wParam, 1);
			break;
		case WM_MOUSEMOVE:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			window->MouseMoveEvent(x, y);
			break;
		}
		case WM_MOVING:
		case WM_SIZING:
		{
			RECT* rect = reinterpret_cast<RECT*>(lParam);

			int x = rect->left;
			int y = rect->top;

			int width = rect->right - x;
			int height = rect->bottom - y;

			window->WindowSizeEvent(x, y, width, height);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			int delta = GET_WHEEL_DELTA_WPARAM(wParam);
			window->MouseScrollEvent(delta);
			break;
		}
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}