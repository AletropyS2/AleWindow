#include <AleWindow.h>

int main()
{
	Ale::Window::WindowProps props = {
		"Test", 400, 400
	};
	Ale::Window* window = Ale::createWindow(&props);

	while (!window->ShouldClose())
	{
		window->PollEvents();
	}
}