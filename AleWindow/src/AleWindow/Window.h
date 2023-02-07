#pragma once

#include <iostream>
#include <functional>

#define ALE_PRESS 0
#define ALE_RELEASE 1

namespace Ale
{
    enum class RenderAPI
    {
        NONE = -1,
        OPENGL,
        VULKAN,
        DIRECTX
    };

    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void PollEvents() = 0;
        virtual void SwapBuffers() = 0;

        const bool ShouldClose() { return m_ShouldClose; }

        virtual void SetKeyCallback(std::function<void(unsigned int, unsigned int)> callback) = 0;
        virtual void SetMouseButtonCallback(std::function<void(unsigned int, unsigned int)> callback) = 0;

        virtual void MakeContextCurrent(RenderAPI api) = 0;

    protected:
        bool m_ShouldClose;

        std::function<void(unsigned int, unsigned int)> m_KeyCallback;
        std::function<void(unsigned int, unsigned int)> m_MouseButtonCallback;
    };
}
