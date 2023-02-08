#include "LinuxWindow.h"
#include "AleWindow/Debug.h"

#ifdef __linux__

#include <GL/glx.h>

namespace Ale
{
    LinuxWindow::LinuxWindow(unsigned int width, unsigned int height, const char* title)
    {
        m_Display = XOpenDisplay(NULL);

        if(m_Display == NULL)
        {
            ALE_ERROR("Cannot open XDisplay!");
        }

        m_Screen = DefaultScreen(m_Display);

        m_Window = XCreateSimpleWindow(
            m_Display, RootWindow(m_Display, m_Screen),
            10, 10, width, height, 1,
            BlackPixel(m_Display, m_Screen), WhitePixel(m_Display, m_Screen)
        );

        XStoreName(m_Display, m_Window, title);

        XSelectInput(m_Display, m_Window, 
        ExposureMask 
        | KeyPressMask | KeyReleaseMask
        | ButtonPressMask | ButtonReleaseMask
        );
        XMapWindow(m_Display, m_Window);

        ALE_LOG("Created a window (" << width << ", " << height << ") named \"" << title << "\"");
    }

    LinuxWindow::~LinuxWindow()
    {
        XDestroyWindow(m_Display, m_Window);
        XCloseDisplay(m_Display);
    }

    void LinuxWindow::PollEvents()
    {
        XEvent event;

        if(XPending(m_Display) <= 0) return;

        XNextEvent(m_Display, &event);

        switch(event.type)
        {
            case ClientMessage:
            {
                if(event.xclient.data.l[0] == XInternAtom(m_Display, "WM_DELETE_WINDOW", False))
                    m_ShouldClose = true;
                break;
            }
        }
    }

    void LinuxWindow::SwapBuffers()
    {
        #ifdef ALE_OPENGL
        glXSwapBuffers(m_Display, m_Window);
        #endif
    }

    void LinuxWindow::MakeContextCurrent(RenderAPI api)
    {
        switch(api)
        {
            case RenderAPI::NONE: ALE_ERROR("None isn't an renderer api"); break;
            case RenderAPI::OPENGL: MakeOpenGLContext(); break;
            case RenderAPI::VULKAN: ALE_ERROR("Vulkan is not supported yet!"); break;
            case RenderAPI::DIRECTX: ALE_ERROR("DirectX is not supported in Linux!"); break;
        }
    }

    void LinuxWindow::MakeOpenGLContext()
    {
        int attribList[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
        XVisualInfo* vi = glXChooseVisual(m_Display, m_Screen, attribList);

        GLXContext glc = glXCreateContext(m_Display, vi, nullptr, GL_TRUE);

        glXMakeCurrent(m_Display, m_Window, glc);
    }
}

#endif