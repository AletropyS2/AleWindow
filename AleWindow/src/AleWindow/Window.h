#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <any>

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

    enum class EventType
    {
        KeyEvent, 
        MouseButton, MouseMove, MouseScroll,
        WindowResize, WindowSetFocus, WindowLostFocus
    };

    struct EventSource
    {
        int keycode = -1;
        int button = -1;
        int action = -1;
        float x = 0;
        float y = 0;
        float width = 0;
        float height = 0;
        float delta = 0;
    };

    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void PollEvents() = 0;
        virtual void SwapBuffers() = 0;

        const bool ShouldClose() { return m_ShouldClose; }

        virtual void MakeContextCurrent(RenderAPI api) = 0;

        void SetCallback(EventType type, const std::function<void(EventSource)>& callback)
        {
            m_Callbacks[type] = callback;
        }

        void CallCallback(EventType type, EventSource& source)
        {
            auto cb = m_Callbacks.find(type);
            if (cb != m_Callbacks.end())
                cb->second(source);
        }

    protected:
        bool m_ShouldClose;
        std::unordered_map<EventType, std::function<void(EventSource)>> m_Callbacks;
    };
}
