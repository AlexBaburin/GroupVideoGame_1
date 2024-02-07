#include <iostream>
#include "Module.h"
using namespace sf;
int main()
{
    RenderWindow window(VideoMode(800, 800), "text");
    Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }
    return 0;
}