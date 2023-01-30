#include <AleWindow.h>

int main()
{
	Ale::Window* window = CreateAleWindow();

	window->MakeContextCurrent();

	while (!window->ShouldClose())
	{
		window->SwapBuffers();
		window->PollEvents();
	}
}