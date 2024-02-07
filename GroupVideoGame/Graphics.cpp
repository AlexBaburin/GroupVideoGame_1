#include "Module.h"
#include "Graphics.h"
using namespace sf;

void Graphics()
{
	int resolution = 800;
	RenderWindow win(VideoMode(resolution, resolution), "Video game");
	while (true)
	{
		win.display();
	}
	while (win.isOpen())
	{
		Event event;

		
	}
}