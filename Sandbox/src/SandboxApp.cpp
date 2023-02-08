#include <AleWindow.h>

#include <memory>
#include <thread>
#include <chrono>

template<typename T>
using Ref = std::shared_ptr<T>;

int main()
{
    Ref<Ale::Window> window = Ref<Ale::Window>(Ale::CreateAleWindow());

    window->MakeContextCurrent(Ale::RenderAPI::OPENGL);

    window->SetCallback(Ale::EventType::KeyEvent, [](Ale::EventSource e)
        {
            std::cout << e.keycode << std::endl;
        });

    while(!window->ShouldClose())
    {
        window->PollEvents();
        window->SwapBuffers();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}