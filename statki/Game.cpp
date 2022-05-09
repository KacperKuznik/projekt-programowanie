#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.cpp"
#include "Network.cpp"
#include "tile.cpp"
#include "ship.cpp"
#include "PlayerGrid.cpp"
#include "EnemyGrid.cpp"
#include <vector>
class Game
{
private:
    int width = 1600;
    int height = 900;
    int grid_width = 500;
    int tile_width = grid_width / 10;
    char column_labels[10];

    int pos_x = 200;
    int pos_y = 10;
    int row, col;

    int selShip = -1;
    bool shipIsSelected = false;

    unsigned short port;
    Network network;

    std::vector< Ship > ships;

public:

    void run() {
                //for (int i = 0; i < 10; i++) {
        //    column_labels[i] = (char)i + 97;
        //}
        createShips();
        cin >> port;
        network.set_reciever_port(port);
        //Tile tile(50);

        
        sf::RenderWindow window(sf::VideoMode(width, height), "statki");
        PlayerGrid player_grid(grid_width, pos_x, pos_y);
        //Grid my_grid(grid_width, pos_x, pos_y);
        EnemyGrid enemy_grid(grid_width, pos_x + grid_width+3* tile_width, pos_y);
        while (window.isOpen())
        {
            auto result = network.listen();
            if (result.status == 0) {
                result.packet >> row >> col;
                player_grid.mark(row, col);
                    
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

                        bool shipIsSelected = selShip != -1;
                        if (shipIsSelected == false) {
                            selShip = shipSel(mouse);
                        }
                        else {
                            shipMove(mouse, selShip, player_grid);
                            selShip = -1;
                        }
                        
                        //int row = (event.mouseButton.x - pos_x) / tile_width;
                        //int col = (event.mouseButton.y - pos_y) / tile_width;
                        //std::cout << "Tile: " << column_labels[row] << col + 1 << endl;
                        enemy_grid.shoot(mouse, network);
                        //network.send(row, col);

                    }
                }
            }

            window.clear(sf::Color::White);
            player_grid.drawGrid(window);
            enemy_grid.drawGrid(window);
            for (Ship ship : ships)
                ship.drawShip(window);
            //Grid enemy_grid(window, grid_width, grid_width + grid_width/10,0);

            window.display();
        }
    }
    void createShips() {
        int n = 4;
        for (int i = 1; i <= 4; i++) {
            for (int j = 0; j < n; j++) {
                Ship ship(i, pos_x + tile_width*(i+1)*j, pos_y + grid_width + tile_width*i +tile_width*(i-1)/2);
                ships.push_back(ship);
            }
            n--;
        }

        std::cout << ships.size();
    }

    int shipSel(sf::Vector2f mouse) {
        std::cout << "\n" << "Klikniecie" << "\n";
        for (int i = 0; i < ships.size(); i++) {
            for (int j = 0; j < ships[i].size(); j++) {
                if (ships[i].getTile(j).getGlobalBounds().contains(mouse)) {
                    ships[i].chColor(sf::Color::Yellow);
                    std::cout << "Zwrot" << std::endl;
                    return i;
                }
            }
        }
        return -1;
    }

    void shipMove(sf::Vector2f mouse, int selShip, PlayerGrid player_grid) {
        player_grid.placeShip(ships[selShip], mouse);
        ships[selShip].chColor(sf::Color::Blue);
    }
};
