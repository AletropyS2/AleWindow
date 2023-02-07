#include <AleWindow.h>

#include <memory>

template<typename T>
using Ref = std::shared_ptr<T>;

int main()
{
    Ref<Ale::Window> window = Ref<Ale::Window>(Ale::CreateAleWindow());

    window->MakeContextCurrent(Ale::RenderAPI::OPENGL);

    while(!window->ShouldClose())
    {
        window->PollEvents();
        window->SwapBuffers();
    }

    return 0;
}