#include <SFML/Graphics.hpp>
#include <iostream>
#include "grid.cpp"
#include "Game.cpp"
using namespace std;



int main()
{
    int width = 1920;
    int height = 1080;
    int grid_width = 500;
    float tile_width = grid_width/10;
    sf::RenderWindow window(sf::VideoMode(width, height), "statki");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        Grid my_grid(window, grid_width, 0, 50);
        Grid enemy_grid(window, grid_width, grid_width + grid_width/10,50);
        sf::Mouse mouse;
        mouse.getPosition();
        cout << mouse.getPosition().x << " " << mouse.getPosition().y << endl;
        window.display();
    }

    return 0;
}