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
    int tile_width = grid_width/10;
    char column_labels[10];
    for (int i = 0; i < 10; i++) {
        column_labels[i] = (char) i + 97;
    }


    sf::RenderWindow window(sf::VideoMode(width, height), "statki");
    Grid my_grid(grid_width, 0, 0);
    while (window.isOpen())
    {
        


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "Tile: " << column_labels[event.mouseButton.x / tile_width] << event.mouseButton.y / tile_width + 1 << endl;
                    my_grid.getTiles()[event.mouseButton.x / tile_width][event.mouseButton.y / tile_width].setFillColor(sf::Color::Blue);
                }
            }
        }

        window.clear(sf::Color::White);
        my_grid.drawGrid(window);
        
        //Grid enemy_grid(window, grid_width, grid_width + grid_width/10,0);
       
     
        window.display();
    }

    return 0;
}