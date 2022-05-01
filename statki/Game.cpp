#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.cpp"
#include "Network.cpp"
#include "tile.cpp"
#include "ship.cpp"
class Game
{
private:
    int width = 1920;
    int height = 1080;
    int grid_width = 500;
    int tile_width = grid_width / 10;
    char column_labels[10];

    int pos_x = 200;
    int pos_y = 10;
    int row, col;


    unsigned short port;
    Network network;

public:

    void run() {
                //for (int i = 0; i < 10; i++) {
        //    column_labels[i] = (char)i + 97;
        //}
        //createShips();
        cin >> port;
        network.set_reciever_port(port);
        //Tile tile(50);


        sf::RenderWindow window(sf::VideoMode(width, height), "statki");

        Grid my_grid(grid_width, pos_x, pos_y);
        Ship ship1(3, 0, 700);
        while (window.isOpen())
        {
            auto result = network.listen();
            if (result.status == 0) {
                result.packet >> row >> col;
                my_grid.getTiles()[row][col].setFillColor(sf::Color::Blue);
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mouse(sf::Mouse::getPosition(window));


                        //int row = (event.mouseButton.x - pos_x) / tile_width;
                        //int col = (event.mouseButton.y - pos_y) / tile_width;
                        //std::cout << "Tile: " << column_labels[row] << col + 1 << endl;
                        my_grid.click(mouse, network);
                        //network.send(row, col);

                    }
                }
            }

            window.clear(sf::Color::White);
            my_grid.drawGrid(window);
            ship1.drawShip(window);
            //Grid enemy_grid(window, grid_width, grid_width + grid_width/10,0);

            window.display();
        }
    }
    /*void createShips() {
        int n = 4;
        for (int i = 1; i <= 4; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << i;

            }
            n--;
        }
    }*/
};