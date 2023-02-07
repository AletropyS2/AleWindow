#pragma once

#include "AleWindow/Window.h"

#ifdef _WIN64

#include <Windows.h>
#include <unordered_map>

namespace Ale
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(unsigned int width, unsigned int height, const char* title);
        virtual ~WindowsWindow();

        virtual void PollEvents() override;
        virtual void SwapBuffers() override;

        virtual void SetKeyCallback(std::function<void(unsigned int, unsigned int)> callback) override;
        virtual void SetMouseButtonCallback(std::function<void(unsigned int, unsigned int)> callback) override;

        virtual void MakeContextCurrent(RenderAPI api) override;

        void MakeOpenGLContext();
    private:
        static LRESULT CALLBACK WndProc(HWND hwnd, unsigned int msg, WPARAM wParam, LPARAM lParam);
    private:
        HWND m_Hwnd;
        HINSTANCE m_HInstance;

    private:
        static std::unordered_map<HWND, WindowsWindow*> m_Windows;
    };
}

#endif