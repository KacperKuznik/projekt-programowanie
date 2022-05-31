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
#include "Button.cpp"
#include <string>
#include <cmath>
#include <sstream>

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
    bool selfFound = false;

    unsigned short port;
    Network network;
    sf::Text text;
    sf::Text playerTurnText;
    sf::Font font;

    sf::Texture bgMenu;
    sf::Sprite bg;

    sf::String ipInput;
    sf::String portInput;

    std::vector< Ship > ships;
    Player player;

    bool started = false;

public:

    void startMenu() {


        Button hostButton("HOST");
        hostButton.chPos(525, 200);

        Button joinButton("JOIN");
        joinButton.chPos(525, 350);

        sf::RenderWindow window(sf::VideoMode(width, height), "menu");

        bgMenu.loadFromFile("img/mainbg.jpg");
        bg.setTexture(bgMenu);
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
                        sf::Vector2f mouse(sf::Mouse::getPosition(window));
                        
                        if (joinButton.isClicked(mouse)) {
                            window.close();
                            joinMenu();
                        }
                        else if (hostButton.isClicked(mouse)) {
                            window.close();
                            hostMenu();
                        }


                    }
                }
            }
            window.clear(sf::Color::White);
            window.draw(bg);
            window.draw(hostButton);
            window.draw(joinButton);
            window.display();
        }
    }

    void joinMenu() {
        sf::RenderWindow window(sf::VideoMode(width, height), "Dolaczanie");
        sf::Text ipText;
        sf::Text portText;
        if (!font.loadFromFile("fonts/arial.ttf"))
        {
        }
        ipText.setFont(font);
        ipText.setCharacterSize(50);
        ipText.setFillColor(sf::Color::Black);
        ipText.setPosition(400, 50);

        portText.setFont(font);
        portText.setCharacterSize(50);
        portText.setFillColor(sf::Color::Black);
        portText.setPosition(400, 150);

        Button joinConfButton("Join");
        joinConfButton.chPos(525, 300);

        bgMenu.loadFromFile("img/mainbg.jpg");
        bg.setTexture(bgMenu);

        sf::RectangleShape ipInputBox(sf::Vector2f(400,60));

        ipInputBox.setFillColor(sf::Color::White);
        ipInputBox.setOutlineThickness(5);
        ipInputBox.setOutlineColor(sf::Color::Black);
        ipInputBox.setPosition(395, 50);

        sf::RectangleShape portInputBox(sf::Vector2f(400, 60));

        portInputBox.setFillColor(sf::Color::White);
        portInputBox.setOutlineThickness(5);
        portInputBox.setOutlineColor(sf::Color::Black);
        portInputBox.setPosition(395, 150);

        unsigned int boxSelected = 0;
        sf::IpAddress joinIp;
        while (window.isOpen())
        {
            auto result = network.listen();
            if (result.status == 0) {
                window.close();
                run();
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

                        if (ipInputBox.getGlobalBounds().contains(mouse)) {
                            boxSelected = 1;
                            portInputBox.setFillColor(sf::Color::White);
                            ipInputBox.setFillColor(sf::Color(120,120,120,255));
                            std::cout << "\n IP box selected!";
                        }
                        else if (portInputBox.getGlobalBounds().contains(mouse)) {
                            boxSelected = 2;
                            ipInputBox.setFillColor(sf::Color::White);
                            portInputBox.setFillColor(sf::Color(120, 120, 120, 255));
                            std::cout << "\n Port box selected!";
                        }
                        else {
                            boxSelected = 0;
                            ipInputBox.setFillColor(sf::Color::White);
                            portInputBox.setFillColor(sf::Color::White);
                            std::cout << "\n Box selection cleared!";
                        }

                        if (joinConfButton.isClicked(mouse)) {
                            string portstr = portText.getString();
                            int portnumber = std::stoi(portstr);
                            network.set_reciever_port(portnumber);
                            network.set_reciever_ip(ipText.getString());
                            bool starting = chooseStartingPlayer();
                            player.setTurn(starting);
                            network.connect(!starting);
                        }

                    }
                }

                else if (event.type == sf::Event::TextEntered)
                {
                    switch (boxSelected) {
                    case 0:
                        std::cout << "\n None box selected!";
                        break;

                    case 1:
                        if (ipInput.getSize() >= 15 && event.text.unicode != 8) {
                            std::cout << "\n IP: Input box is full!";
                        }
                        else {
                            std::cout << "\n IP: Entered: " << event.text.unicode;

                            if (event.text.unicode == 8) {
                                if (!ipInput.isEmpty()) {
                                    ipInput.erase(ipInput.getSize() - 1, 1);
                                    ipText.setString(ipInput);
                                }
                                else
                                {
                                    std::cout << "\n IP: Text field value is empty!";
                                }
                            }
                            else {
                                if ((event.text.unicode < 48 || event.text.unicode > 57) && event.text.unicode != 46) {
                                    std::cout << "\n IP: Input not a number or dot!";
                                    break;
                                }
                                ipInput += event.text.unicode;

                                ipText.setString(ipInput);
                            }
                        }
                        break;
                    case 2:
                        if (portInput.getSize() >= 5 && event.text.unicode != 8) {
                            std::cout << "\n Port: Input box is full!";
                            break;
                        }
                        std::cout << "\n Port: Entered: " << event.text.unicode;

                        if (event.text.unicode == 8) {
                            if (!portInput.isEmpty()) {
                                portInput.erase(portInput.getSize() - 1, 1);
                                portText.setString(portInput);
                            }
                            else
                            {
                                std::cout << "\n Port: Text field value is empty!";
                            }
                        }
                        else {
                            if (event.text.unicode < 48 || event.text.unicode > 57) {
                                std::cout << "\n Port: Input not a number!";
                                break;
                            }
                            portInput += event.text.unicode;
                            portText.setString(portInput);
                        }
                        break;
                    }
                    

                }
            }
            window.clear(sf::Color::White);
            window.draw(bg);
            window.draw(joinConfButton);
            window.draw(ipInputBox);
            window.draw(ipText);
            window.draw(portInputBox);
            window.draw(portText);
            window.display();
        }
    }

    void hostMenu() {
        sf::RenderWindow window(sf::VideoMode(width, height), "Hostowanie");

        bgMenu.loadFromFile("img/mainbg.jpg");
        bg.setTexture(bgMenu);

        sf::IpAddress hostIP;
        std::cout << "\n Checking your IP address...";
        std::cout << "\n Hosting game at IP address: " << hostIP.getLocalAddress();

        std::cout << "\n Checking your port number...";
        std::cout << "\n Hosting game at port number: " << network.getPort();

        sf::Text ipTextH;
        sf::Text portTextH;
        if (!font.loadFromFile("fonts/arial.ttf"))
        {
        }
        ipTextH.setFont(font);
        ipTextH.setCharacterSize(50);
        ipTextH.setFillColor(sf::Color::Black);
        ipTextH.setPosition(400, 50);
        ipTextH.setString(hostIP.getLocalAddress().toString());

        portTextH.setFont(font);
        portTextH.setCharacterSize(50);
        portTextH.setFillColor(sf::Color::Black);
        portTextH.setPosition(450, 150);
        portTextH.setString(std::to_string(network.getPort()));



        while (window.isOpen())
        {
            auto result = network.listen();
            if (result.status == 0) {
                bool isStarting;
                result.packet >> isStarting;
                player.setTurn(isStarting);
                cout << "successfully connected " << isStarting << endl;
                network.reply(!isStarting);
                window.close();
                run();
            }
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color::White);
            window.draw(bg);
            window.draw(ipTextH);
            window.draw(portTextH);
            window.display();
        }
    }

    void run() {

        std::cout << "\n Game starting...";

        srand(time(NULL));
        std::cout << "\n Loading fonts...";
        if (!font.loadFromFile("fonts/arial.ttf"))
        {
        }
        text.setFont(font);
        text.setCharacterSize(150);
        playerTurnText.setFont(font);
        playerTurnText.setCharacterSize(50);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));

        std::cout << "\n Creating ships...";
        short int ship_tiles_count;
        ship_tiles_count = createShips();
        
        player.setTilesCount(ship_tiles_count);
        Player enemy(ship_tiles_count);
        std::cout << "\n Choosing side... ";


        Button startButton("START");
        std::cout << "\n Rendering game window...";

        sf::RenderWindow window(sf::VideoMode(width, height), "statki");

        std::cout << "\n Creating player grid...";
        PlayerGrid player_grid(grid_width, pos_x, pos_y);

        std::cout << "\n Creating enemy grid...";
        EnemyGrid enemy_grid(grid_width, pos_x + grid_width+3* tile_width, pos_y);

        std::cout << "\n Loading finished!";
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

                        if (startButton.isClicked(mouse) && allShipsPlaced()) {
                            startButton.changeButton("READY", sf::Color::Red);
                            started = true;
                        }
                        if (!started) {
                            if (shipIsSelected == false) {
                                selShip = shipSel(mouse);
                            }
                            else {
                                if (shipMove(mouse, selShip, player_grid) == EXIT_SUCCESS) {
                                    selShip = -1;
                                }
                            }
                            updateShips(player_grid);
                            checkShips(player_grid);
                        }
                        else {
                            if (player.isPlayerTurn())
                                enemy_grid.shoot(mouse, network, enemy, player);
                        }
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right) {
                        
                        if (shipIsSelected == true) {
                            ships[selShip].setRot(shipRotate(ships[selShip], player_grid));
                        }
                    }
                }
            }

            window.clear(sf::Color::White);
            checkWin(player, enemy, window);
            player_grid.drawGrid(window);
            enemy_grid.drawGrid(window);
            for (Ship ship : ships)
                ship.drawShip(window);
            window.draw(text);
            window.draw(startButton);
            displayTurnText(window, player.isPlayerTurn());
            window.display();
        }
    }
    void displayTurnText(sf::RenderWindow& window, bool isPlayerTurn) {
        if (isPlayerTurn) {
            playerTurnText.setFillColor(sf::Color::Green);
            playerTurnText.setString("Your turn");
        }
        else {
            playerTurnText.setFillColor(sf::Color::Red);
            playerTurnText.setString("Enemy turn");
        }
        window.draw(playerTurnText);
    }


    short int createShips() {
        short int ship_tiles_count = 0;
        int n = 4;
        for (int i = 1; i <= 4; i++) {
            for (int j = 0; j < n; j++) {
                Ship ship(i, pos_x + tile_width*(i+1)*j, pos_y + grid_width + tile_width*i +tile_width*(i-1)/2);
                ships.push_back(ship);
                ship_tiles_count += i;
            }
            n--;
        }
        return ship_tiles_count;

    }
    bool allShipsPlaced() {
        for (int i = 0; i < ships.size(); i++) {
            if (!ships[i].checkPlacedState()) {
                return false;
            }
        }
        return true;
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
        bool moveNotPossible = false;
        auto pos = player_grid.getClickedPosition(mouse);
        if (ships[selShip].getRot() == 0) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= ships[selShip].size(); j++) {
                    selfFound = false;
                    if (pos.row + j < 0 || pos.row + j >= 10 || pos.col + i >= 10 || pos.col + i < 0) {
                        continue;
                    }
                    else if (player_grid.getTiles()[pos.row+j][pos.col+i].checkShipContent() == true) {
                        for (int k = 0; k < ships[selShip].size(); k++) {
                            if (player_grid.getTiles()[pos.row + j][pos.col + i].getGlobalBounds().contains(ships[selShip].getTile(k).getPosition())) {
                                selfFound = true;
                                break;
                            }
                        }
                        if (selfFound == true) {
                            continue;
                        }
                        else {
                            moveNotPossible = true;
                        }
                        
                    }
                }
            }
        }
        else {
            for (int i = -1; i <= ships[selShip].size(); i++) {
                for (int j = -1; j <= 1; j++) {
                    selfFound = false;
                    if (pos.row + j < 0 || pos.row + j >= 10 || pos.col + i >= 10 || pos.col + i < 0) {
                        continue;
                    }
                    else if (player_grid.getTiles()[pos.row + j][pos.col + i].checkShipContent() == true) {
                        for (int k = 0; k < ships[selShip].size(); k++) {
                            if (player_grid.getTiles()[pos.row + j][pos.col + i].getGlobalBounds().contains(ships[selShip].getTile(k).getPosition())) {
                                selfFound = true;
                                break;
                            }
                        }
                        if (selfFound == true) {
                            continue;
                        }
                        else {
                            moveNotPossible = true;
                        }
                    }
                }
            }
        }

        if (moveNotPossible == true) {
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
        //DEV method. NOT FOR COMMERCIAL USE!
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
    void checkWin(Player& player, Player& enemy, sf::RenderWindow& window) {
        if (player.getTilesCount() == 0) {
            text.setString("lost");
            text.setFillColor(sf::Color::Red);

        }
        else if (enemy.getTilesCount() == 0) {
            text.setString("won");
            text.setFillColor(sf::Color::Green);

        }
    }
    bool chooseStartingPlayer() {
        return (rand() > (RAND_MAX / 2));
    }
};

