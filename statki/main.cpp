#include <SFML/Graphics.hpp>
#include <iostream>
#include "grid.cpp"

using namespace std;



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        Grid grid(window);

        window.display();
    }

    return 0;
}