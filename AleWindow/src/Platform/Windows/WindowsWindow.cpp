#include "WindowsWindow.h"
#include "AleWindow/Debug.h"

#ifdef _WIN64

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
	}

	void WindowsWindow::SetKeyCallback(std::function<void(unsigned int, unsigned int)> callback)
    {
        m_KeyCallback = callback;
        ALE_LOG("Setted KeyCallback to " << &callback);
    }

    void WindowsWindow::SetMouseButtonCallback(std::function<void(unsigned int, unsigned int)> callback)
    {
        m_MouseButtonCallback = callback;
        ALE_LOG("Setted MouseButtonCallback to " << &callback);
    }

	LRESULT WindowsWindow::WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* window = m_Windows[hwnd];

		switch (msg)
		{
		case WM_CLOSE:
			window->m_ShouldClose = true;
			PostQuitMessage(0);
			break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

#endif