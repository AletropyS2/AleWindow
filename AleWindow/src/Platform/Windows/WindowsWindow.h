#pragma once

#include <Windows.h>
#include "Core/Window.h"

struct DXGI_SWAP_CHAIN_DESC;
struct IDXGISwapChain;
struct ID3D10Device;
struct D3D10_VIEWPORT;
struct ID3D10RenderTargetView;

namespace Ale
{

	struct DxProps
	{
		DXGI_SWAP_CHAIN_DESC* SwapChainDesc = nullptr;
		IDXGISwapChain* SwapChain = nullptr;
		ID3D10Device* D3dDevice = nullptr;
		D3D10_VIEWPORT* Viewport = nullptr;
		ID3D10RenderTargetView* RenderTargetView = nullptr;
	};

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(Window::WindowProps* props);
		~WindowsWindow() { };

		virtual bool MakeContextCurrent(RenderingAPI api) override;

		virtual void PollEvents() override;
		virtual void SwpBuffers() override;

		virtual void SetKeyCallback(const std::function<void(int, int)>& callback) override;
		virtual void SetMouseMoveCallback(const std::function<void(int, int)>& callback) override;
		virtual void SetMouseScrollCallback(const std::function<void(int)>& callback) override;
		virtual void SetWindowSizeCallback(const std::function<void(int, int, int, int)>& callback) override;

		inline DxProps* GetDxProps() { return m_DxProps; }

	private:
		virtual void KeyEvent(int keycode, int action) override;
		virtual void MouseMoveEvent(int x, int y) override;
		virtual void MouseScrollEvent(int delta) override;
		virtual void WindowSizeEvent(int x, int y, int width, int height) override;

		void UpdateViewport();

		bool MakeOpenGLContext();
		bool MakeDirectXContext();
		void SwapOpenGLBuffers();
		void SwapDirectXBuffers();
			
		static WindowsWindow* GetWindow(HWND hwnd);

	private:
		static LRESULT CALLBACK WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam);
	private:
		HWND m_Hwnd;
		HINSTANCE m_HInstance;
		Window::WindowProps* m_Props;
		DxProps* m_DxProps = nullptr;

		static int m_WindowCount;
		static std::array<std::pair<HWND, WindowsWindow*>, 32> m_Windows;
	};
}