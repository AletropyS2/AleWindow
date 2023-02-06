
#include <AleWindow.h>

int main()
{

    Ale::Window* window = Ale::CreateAleWindow(800, 600, "Test");

    while(!window->ShouldClose())
    {
        window->PollEvents();
    }

    return 0;
}