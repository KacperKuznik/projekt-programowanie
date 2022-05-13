#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.cpp"
#include "Network.cpp"
#include "tile.cpp"
#include "ship.cpp"
#include "PlayerGrid.cpp"
#include "EnemyGrid.cpp"
#include "Player.cpp"
#include <vector>
class Game
{
private:
    int width = 1200;
    int height = 900;
    int grid_width = 500;
    int tile_width = grid_width / 10;
    char column_labels[10];

    int pos_x = 25;
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
        srand(time(NULL));

        short int tiles_count;
        tiles_count = createShips();
        std::cout << tiles_count;
        Player player(tiles_count);
        Player enemy(tiles_count);
        chooseStartingPlayer(player, enemy);
        cout << player.isPlayerTurn() << enemy.isPlayerTurn() << "-------00000000000";
        cin >> port;
        network.set_reciever_port(port);


        
        sf::RenderWindow window(sf::VideoMode(width, height), "statki");
        PlayerGrid player_grid(grid_width, pos_x, pos_y);
        EnemyGrid enemy_grid(grid_width, pos_x + grid_width+3* tile_width, pos_y);
        while (window.isOpen())
        {
            auto result = network.listen();
            if (result.status == 0) {
                result.packet >> row >> col;
                player_grid.mark(row, col, ships, network, player);
                    
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    bool shipIsSelected = selShip != -1;
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2f mouse(sf::Mouse::getPosition(window));

                        if (shipIsSelected == false) {
                            selShip = shipSel(mouse);
                        }
                        else {
                            if (shipMove(mouse, selShip, player_grid) == EXIT_SUCCESS) {
                                selShip = -1;
                            }
                        }
                        enemy_grid.shoot(mouse, network, enemy);
                        updateShips(player_grid);
                        checkShips(player_grid);
                        checkWin(player, enemy);
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        if (shipIsSelected == true) {
                            //shipRotate(ships[selShip], player_grid);
                            ships[selShip].setRot(shipRotate(ships[selShip], player_grid));
                        }
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



    short int createShips() {
        short int tiles_count = 0;
        int n = 4;
        for (int i = 1; i <= 4; i++) {
            for (int j = 0; j < n; j++) {
                Ship ship(i, pos_x + tile_width*(i+1)*j, pos_y + grid_width + tile_width*i +tile_width*(i-1)/2);
                ships.push_back(ship);
                tiles_count += i;
            }
            n--;
        }
        return tiles_count;

    }

    int shipSel(sf::Vector2f mouse) {
        for (int i = 0; i < ships.size(); i++) {
            for (int j = 0; j < ships[i].size(); j++) {
                if (ships[i].getTile(j).getGlobalBounds().contains(mouse)) {
                    ships[i].chColor(sf::Color::Yellow);
                    return i;
                }
            }
        }
        return -1;
    }

    bool shipMove(sf::Vector2f mouse, int selShip, PlayerGrid player_grid) {
        ships[selShip].setShipToPlaced();
        std::cout << std::endl << "Ship: " << selShip << " placed!" << std::endl;
        bool moveNotPossible = false;
        auto pos = player_grid.getClickedPosition(mouse);
        if (ships[selShip].getRot() == 0) {
            for (int i = -1; i < 1; i++) {
                for (int j = -1; j < ships[selShip].size() + 1; j++) {
                    if (pos.row + j < 0 || pos.row + j > 10 || pos.col + i > 10 || pos.col + i < 0) {
                        continue;
                    }
                    else if (player_grid.getTiles()[pos.row+j][pos.col+i].checkShipContent() == true) {
                        moveNotPossible = true;
                    }
                }
            }
        }
        else {
            for (int i = -1; i < ships[selShip].size() + 1; i++) {
                for (int j = -1; j < 1; j++) {
                    if (pos.row + j < 0 || pos.row + j > 10 || pos.col + i > 10 || pos.col + i < 0) {
                        continue;
                    }
                    else if (player_grid.getTiles()[pos.row + j][pos.col + i].checkShipContent() == true) {
                        moveNotPossible = true;
                    }
                }
            }
        }

        if (moveNotPossible == true) {
            std::cout << std::endl << "Rusz niemozliwy";
            return EXIT_FAILURE;
        }
        else {
            player_grid.placeShip(ships[selShip], mouse);
            ships[selShip].chColor(sf::Color::Blue);
            return EXIT_SUCCESS;
        }
    }

    bool shipRotate(Ship ship, PlayerGrid player_grid) {
        if (player_grid.canBeRotated(ship) == 0) {
            return ship.chRot();
        }
        else {
            return ship.getRot();
            
        }

    }

    void updateShips(PlayerGrid player_grid) {
        for (int i = 0; i < player_grid.getRows(); i++) {
            for (int j = 0; j < player_grid.getCols(); j++) {
                player_grid.getTiles()[j][i].chgShipContent(false);
            }
        }
        for (int i = 0; i < ships.size(); i++) {
            if (ships[i].checkPlacedState() == true)
            {
                for (int j = 0; j < player_grid.getRows(); j++) {
                    for (int k = 0; k < player_grid.getCols(); k++) {
                        if (player_grid.getTiles()[j][k].getGlobalBounds().contains(ships[i].getTile(0).getCenter())) {
                            bool rotation = ships[i].getRot();
                            int size = ships[i].size();
                            if (rotation == 0) {
                                for (int l = 0; l < size; l++) {
                                    player_grid.getTiles()[j + l][k].chgShipContent(true);
                                }
                            }
                            else
                            {
                                for (int l = 0; l < size; l++) {
                                    player_grid.getTiles()[j][k+l].chgShipContent(true);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void checkShips(PlayerGrid player_grid) {
        //DEV method. NOT FOR COMMERCIAL USE!!!111
        std::cout << "------------------------------------" << std::endl;
        for (int i = 0; i < player_grid.getRows(); i++) {
            for (int j = 0; j < player_grid.getCols(); j++) {
                if (player_grid.getTiles()[j][i].checkShipContent() == true) {
                    std::cout << "X ";
                }
                else
                {
                    std::cout << "O ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "------------------------------------" << std::endl;
    }
    void checkWin(Player& player, Player& enemy) {
        if (player.getTilesCount() == 0) {
            std::cout << "przegrales";
        }
        else if (enemy.getTilesCount() == 0) {
            std::cout << "wygrales";
        }
    }
    void chooseStartingPlayer(Player& player, Player& enemy) {
        if (rand() > (RAND_MAX / 2)) {
            player.changeTurn();
            cout << "player";
        }
        else
        {
            
            cout << "enemy";

            enemy.changeTurn();
        }
    }
};

