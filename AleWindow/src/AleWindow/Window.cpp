#include "Window.h"

namespace Ale
{
    void Window::SetCallback(EventType type, const std::function<void(EventSource)>& callback)
    {
        m_Callbacks[type] = callback;
    }

    void Window::CallCallback(EventType type, EventSource& source)
    {
        auto cb = m_Callbacks.find(type);
        if (cb != m_Callbacks.end())
            cb->second(source);
    }
}

