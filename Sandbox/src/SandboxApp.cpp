
#include <AleWindow.h>

int main()
{

    Ale::Window* window = Ale::CreateWindow(800, 600, "Test");

    while(!window->ShouldClose())
    {
        window->PollEvents();
    }

    return 0;
}