#include "LinuxWindow.h"

#ifdef __linux__

namespace Ale
{
    LinuxWindow::LinuxWindow(unsigned int width, unsigned int height, const char* title)
    {
        m_Display = XOpenDisplay(NULL);

        if(m_Display == NULL)
            exit(1);

        m_Screen = DefaultScreen(m_Display);

        m_Window = XCreateSimpleWindow(
            m_Display, RootWindow(m_Display, m_Screen),
            10, 10, width, height, 1,
            BlackPixel(m_Display, m_Screen), WhitePixel(m_Display, m_Screen)
        );

        XStoreName(m_Display, m_Window, title);

        XSelectInput(m_Display, m_Window, ExposureMask | KeyPressMask);
        XMapWindow(m_Display, m_Window);
    }

    LinuxWindow::~LinuxWindow()
    {
        XDestroyWindow(m_Display, m_Window);
        XCloseDisplay(m_Display);
    }

    void LinuxWindow::PollEvents()
    {
        XEvent event;

        if(XPending(m_Display) > 0)
            XNextEvent(m_Display, &event);
        
        if(event.type == ClientMessage)
        {
            if(event.xclient.data.l[0] == XInternAtom(m_Display, "WM_DELETE_WINDOW", False))
                m_ShouldClose = true;
        }
    }

    void LinuxWindow::SwapBuffers()
    {
        XFlush(m_Display);
    }
}

#endif