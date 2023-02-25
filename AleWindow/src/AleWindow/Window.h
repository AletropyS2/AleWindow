#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <unordered_map>
#include <any>

#include "Core.h"

#define ALE_PRESS 0
#define ALE_RELEASE 1

namespace Ale
{
    enum class ALE_API RenderAPI
    {
        NONE = -1,
        OPENGL,
        VULKAN,
        DIRECTX
    };

    enum class ALE_API EventType
    {
        KeyEvent, 
        MouseButton, MouseMove, MouseScroll,
        WindowResize, WindowSetFocus, WindowLostFocus
    };

    struct ALE_API EventSource
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

    class ALE_API Window
    {
    public:
        virtual ~Window() = default;

        virtual void PollEvents() = 0;
        virtual void SwapBuffers() = 0;

        const bool ShouldClose() { return m_ShouldClose; }

        virtual void MakeContextCurrent(RenderAPI api) = 0;

        void SetCallback(EventType type, const std::function<void(EventSource)>& callback);

        void CallCallback(EventType type, EventSource& source);

    protected:
        bool m_ShouldClose;
        std::unordered_map<EventType, std::function<void(EventSource)>> m_Callbacks;
    };
}
