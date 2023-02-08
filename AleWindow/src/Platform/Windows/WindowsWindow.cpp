#include "WindowsWindow.h"
#include "AleWindow/Debug.h"

#ifdef _WIN64

#include <gl/GL.h>

namespace Ale
{
	std::unordered_map<HWND, WindowsWindow*> WindowsWindow::m_Windows;

	WindowsWindow::WindowsWindow(unsigned int width, unsigned int height, const char* title)
		: m_HInstance(GetModuleHandle(NULL))
	{
		size_t cSize = (size_t)strlen(title) + 1;
		wchar_t* wTitle = new wchar_t[cSize];
		mbstowcs_s(&cSize, wTitle, cSize, title, 256);

		WNDCLASSEX wc{};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.hInstance = m_HInstance;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wc.lpfnWndProc = WindowsWindow::WndProc;
		wc.lpszClassName = wTitle;
		wc.lpszMenuName = NULL;
		wc.style = 0;

		if (!RegisterClassEx(&wc))
		{
			exit(1);
		}

		m_Hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			wTitle, wTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			width, height, NULL, NULL, m_HInstance, NULL
		);

		m_ShouldClose = false;

		m_Windows[m_Hwnd] = this;

		ShowWindow(m_Hwnd, SW_SHOW);
		UpdateWindow(m_Hwnd);
	}

	WindowsWindow::~WindowsWindow()
	{
		DestroyWindow(m_Hwnd);
	}

	void WindowsWindow::PollEvents()
	{
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowsWindow::SwapBuffers()
	{
		::SwapBuffers(GetDC(m_Hwnd));
	}

	void WindowsWindow::MakeContextCurrent(RenderAPI api)
	{
		switch (api)
		{
		case RenderAPI::NONE: ALE_ERROR("None isn't an renderer api"); break;
		case RenderAPI::OPENGL: MakeOpenGLContext(); break;
		case RenderAPI::VULKAN: ALE_ERROR("Vulkan is not supported yet!"); break;
		case RenderAPI::DIRECTX: ALE_ERROR("DirectX is not supported yet!"); break;
		}
	}

	void WindowsWindow::MakeOpenGLContext()
	{
		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
			1,                     // version number  
			PFD_DRAW_TO_WINDOW |   // support window  
			PFD_SUPPORT_OPENGL |   // support OpenGL  
			PFD_DOUBLEBUFFER,      // double buffered  
			PFD_TYPE_RGBA,         // RGBA type  
			24,                    // 24-bit color depth  
			0, 0, 0, 0, 0, 0,      // color bits ignored  
			0,                     // no alpha buffer  
			0,                     // shift bit ignored  
			0,                     // no accumulation buffer  
			0, 0, 0, 0,            // accum bits ignored  
			32,                    // 32-bit z-buffer  
			0,                     // no stencil buffer  
			0,                     // no auxiliary buffer  
			PFD_MAIN_PLANE,        // main layer  
			0,                     // reserved  
			0, 0, 0                // layer masks ignored  
		};
		HDC hdc = GetDC(m_Hwnd);
		
		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, pixelFormat, &pfd);

		HGLRC ctx = wglCreateContext(hdc);

		if (!wglMakeCurrent(hdc, ctx))
		{
			ALE_ERROR("Cannot make opengl current context!");
		}
	}

	LRESULT WindowsWindow::WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* window = m_Windows[hwnd];

		switch (msg)
		{
		case WM_CLOSE:
		{
			window->m_ShouldClose = true;
			PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN:
		{
			EventSource e{};
			e.keycode = (int)wParam;
			e.action = ALE_PRESS;
			window->CallCallback(EventType::KeyEvent, e);
			break;
		}
		case WM_KEYUP:
		{
			EventSource e{};
			e.keycode = (int)wParam;
			e.action = ALE_RELEASE;
			window->CallCallback(EventType::KeyEvent, e);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			EventSource e{};
			e.delta = ((int)GET_WHEEL_DELTA_WPARAM(wParam)) / 120.0f;
			window->CallCallback(EventType::MouseScroll, e);
			break;
		}
		case WM_MOUSEMOVE:
		{
			EventSource e{};
			e.x = LOWORD(lParam);
			e.y = HIWORD(lParam);
			window->CallCallback(EventType::MouseMove, e);
			break;
		}
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			EventSource e{};
			e.action = ALE_PRESS;
			e.button = msg == WM_LBUTTONDOWN ? 0 : msg == WM_MBUTTONDOWN ? 1 : 2;
			window->CallCallback(EventType::MouseButton, e);
			break;
		}
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		{
			EventSource e{};
			e.action = ALE_RELEASE;
			e.button = msg == WM_LBUTTONUP ? 0 : msg == WM_MBUTTONUP ? 1 : 2;
			window->CallCallback(EventType::MouseButton, e);
			break;
		}
		case WM_SETFOCUS:
		{
			window->CallCallback(EventType::WindowSetFocus, EventSource());
			break;
		}
		case WM_KILLFOCUS:
		{
			window->CallCallback(EventType::WindowSetFocus, EventSource());
			break;
		}
		case WM_SIZING:
		case WM_MOVING:
		{
			EventSource e{};

			RECT rect = *(RECT*)lParam;

			e.x = (float)rect.left;
			e.y = (float)rect.top;
			e.width = (float)rect.right - (float)rect.left;
			e.height = (float)rect.bottom - (float)rect.top;
			window->CallCallback(EventType::WindowResize, e);
			break;
		}
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

#endif
