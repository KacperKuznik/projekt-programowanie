#include "Game.hpp"

void Game::startMenu() {
    Button hostButton("HOST");
    hostButton.chPos(INIT_HOST_BTN_X_POS, INIT_HOST_BTN_Y_POS);

    Button joinButton("JOIN");
    joinButton.chPos(INIT_JOIN_BTN_X_POS, INIT_JOIN_BTN_Y_POS);

    sf::RenderWindow window(sf::VideoMode(width, height), "menu");

    if (!bgMenu.loadFromFile("img/mainbg.jpg"))
    {
        std::cerr << "Failed to load background image" << std::endl;
    }

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

void Game::joinMenu() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Dolaczanie");
    sf::Text ipText;
    sf::Text portText;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
    }
    ipText.setFont(font);
    ipText.setCharacterSize(CHAR_SIZE);
    ipText.setFillColor(sf::Color::Black);
    ipText.setPosition(INIT_IP_TEXT_X_POS, INIT_IP_TEXT_Y_POS);

    portText.setFont(font);
    portText.setCharacterSize(CHAR_SIZE);
    portText.setFillColor(sf::Color::Black);
    portText.setPosition(INIT_PORT_TEXT_X_POS, INIT_PORT_TEXT_Y_POS);

    Button joinConfButton("Join");
    joinConfButton.chPos(INIT_JOIN_CONF_BTN_X_POS, INIT_JOIN_CONF_BTN_Y_POS);

    bgMenu.loadFromFile("img/mainbg.jpg");
    bg.setTexture(bgMenu);

    sf::RectangleShape ipInputBox(sf::Vector2f(400, 60));

    ipInputBox.setFillColor(sf::Color::White);
    ipInputBox.setOutlineThickness(INIT_IP_BOX_OUTLINE_THICKNESS);
    ipInputBox.setOutlineColor(sf::Color::Black);
    ipInputBox.setPosition(INIT_IP_BOX_X_POS, INIT_IP_BOX_Y_POS);

    sf::RectangleShape portInputBox(sf::Vector2f(400, 60));

    portInputBox.setFillColor(sf::Color::White);
    portInputBox.setOutlineThickness(INIT_PORT_BOX_OUTLINE_THICKNESS);
    portInputBox.setOutlineColor(sf::Color::Black);
    portInputBox.setPosition(INIT_PORT_BOX_X_POS, INIT_PORT_BOX_X_POS);

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
                        ipInputBox.setFillColor(sf::Color(120, 120, 120, 255));
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
                        std::string portStr = portText.getString();
                        int portNumber = std::stoi(portStr);
                        network.setReceiverPort(portNumber);
                        network.setReceiverIp(ipText.getString());
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

void Game::hostMenu() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Hostowanie");

    bgMenu.loadFromFile("img/mainbg.jpg");
    bg.setTexture(bgMenu);

    sf::IpAddress hostIp;
    std::cout << "\n Checking your IP address...";
    std::cout << "\n Hosting game at IP address: " << hostIp.getLocalAddress();

    std::cout << "\n Checking your port number...";
    std::cout << "\n Hosting game at port number: " << network.getPort();

    sf::Text ipText;
    sf::Text portText;
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
    }
    ipText.setFont(font);
    ipText.setCharacterSize(CHAR_SIZE);
    ipText.setFillColor(sf::Color::Black);
    ipText.setPosition(INIT_IP_TEXT_X_POS, INIT_IP_TEXT_Y_POS);
    ipText.setString(hostIp.getLocalAddress().toString());

    portText.setFont(font);
    portText.setCharacterSize(CHAR_SIZE);
    portText.setFillColor(sf::Color::Black);
    portText.setPosition(INIT_PORT_TEXT_X_POS, INIT_PORT_TEXT_Y_POS);
    portText.setString(std::to_string(network.getPort()));

    while (window.isOpen())
    {
        auto result = network.listen();
        if (result.status == 0) {
            bool isStarting;
            result.packet >> isStarting;
            player.setTurn(isStarting);
            std::cout << "successfully connected " << isStarting << std::endl;
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
        window.draw(ipText);
        window.draw(portText);
        window.display();
    }
}

void Game::run() {
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
    sf::FloatRect turnTextRect = text.getLocalBounds();

    playerTurnText.setPosition(450, 700);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));

    std::cout << "\n Creating ships...";
    short int shipTilesCount;
    shipTilesCount = createShips();

    player.setTilesCount(shipTilesCount);
    Player enemy(shipTilesCount);
    std::cout << "\n Choosing side... ";

    Button startButton("START");
    std::cout << "\n Rendering game window...";

    sf::RenderWindow window(sf::VideoMode(width, height), "statki");

    std::cout << "\n Creating player grid...";
    GridPlayer playerGrid(gridWidth, posX, posY);

    std::cout << "\n Creating enemy grid...";
    GridEnemy enemyGrid(gridWidth, posX + gridWidth + 3 * tileWidth, posY);

    std::cout << "\n Loading finished!";
    while (window.isOpen())
    {
        auto result = network.listen();
        if (result.status == 0) {
            result.packet >> row >> col;
            playerGrid.mark(row, col, ships, network, player);
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
                            if (shipMove(mouse, selShip, playerGrid) == EXIT_SUCCESS) {
                                selShip = -1;
                            }
                        }
                        updateShips(playerGrid);
                        checkShips(playerGrid);
                    }
                    else {
                        if (player)
                            enemyGrid.shoot(mouse, network, enemy, player);
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {

                    if (shipIsSelected == true) {
                        ships[selShip].setRot(shipRotate(ships[selShip], playerGrid));
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        checkWin(player, enemy, window);
        playerGrid.drawGrid(window);
        enemyGrid.drawGrid(window);
        for (Ship<Tile> ship : ships)
            ship.drawShip(window);
        window.draw(text);
        window.draw(startButton);
        displayTurnText(window, player);
        window.display();
    }
}

void Game::displayTurnText(sf::RenderWindow& window, bool isPlayerTurn) {
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

short int Game::createShips() {
    short int shipTilesCount = 0;
    int n = 4;
    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j < n; j++) {
            Ship<Tile> ship(i, posX + tileWidth * (i + 1) * j, posY + gridWidth + tileWidth * i + tileWidth * (i - 1) / 2);
            ships.push_back(ship);
            shipTilesCount += i;
        }
        n--;
    }
    return shipTilesCount;
}

bool Game::allShipsPlaced() {
    for (int i = 0; i < ships.size(); i++) {
        if (!ships[i].checkPlacedState()) {
            return false;
        }
    }
    return true;
}

int Game::shipSel(sf::Vector2f mouse) {
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

bool Game::shipMove(sf::Vector2f mouse, int selShip, GridPlayer playerGrid) {
    ships[selShip].setShipToPlaced();
    bool moveNotPossible = false;
    auto pos = playerGrid.getClickedPosition(mouse);
    if (ships[selShip].getRot() == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= ships[selShip].size(); j++) {
                selfFound = false;
                if (pos.row + j < 0 || pos.row + j >= 10 || pos.col + i >= 10 || pos.col + i < 0) {
                    continue;
                }
                else if (playerGrid.getTiles()[pos.row + j][pos.col + i].checkShipContent() == true) {
                    for (int k = 0; k < ships[selShip].size(); k++) {
                        if (playerGrid.getTiles()[pos.row + j][pos.col + i].getGlobalBounds().contains(ships[selShip].getTile(k).getPosition())) {
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
                else if (playerGrid.getTiles()[pos.row + j][pos.col + i].checkShipContent() == true) {
                    for (int k = 0; k < ships[selShip].size(); k++) {
                        if (playerGrid.getTiles()[pos.row + j][pos.col + i].getGlobalBounds().contains(ships[selShip].getTile(k).getPosition())) {
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
        playerGrid.placeShip(ships[selShip], mouse);
        ships[selShip].chColor(sf::Color::Blue);
        return EXIT_SUCCESS;
    }
}

bool Game::shipRotate(Ship<Tile> ship, GridPlayer playerGrid) {
    if (playerGrid.canBeRotated(ship) == 0) {
        return ship.chRot();
    }
    else {
        return ship.getRot();
    }
}

void Game::updateShips(GridPlayer playerGrid) {
    for (int i = 0; i < playerGrid.getRows(); i++) {
        for (int j = 0; j < playerGrid.getCols(); j++) {
            playerGrid.getTiles()[j][i].chgShipContent(false);
        }
    }
    for (int i = 0; i < ships.size(); i++) {
        if (ships[i].checkPlacedState() == true)
        {
            for (int j = 0; j < playerGrid.getRows(); j++) {
                for (int k = 0; k < playerGrid.getCols(); k++) {
                    if (playerGrid.getTiles()[j][k].getGlobalBounds().contains(ships[i].getTile(0).getCenter())) {
                        bool rotation = ships[i].getRot();
                        int size = ships[i].size();
                        if (rotation == 0) {
                            for (int l = 0; l < size; l++) {
                                playerGrid.getTiles()[j + l][k].chgShipContent(true);
                            }
                        }
                        else
                        {
                            for (int l = 0; l < size; l++) {
                                playerGrid.getTiles()[j][k + l].chgShipContent(true);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Game::checkShips(GridPlayer playerGrid) {
    std::cout << "------------------------------------" << std::endl;
    for (int i = 0; i < playerGrid.getRows(); i++) {
        for (int j = 0; j < playerGrid.getCols(); j++) {
            if (playerGrid.getTiles()[j][i].checkShipContent() == true) {
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

void Game::checkWin(Player& player, Player& enemy, sf::RenderWindow& window) {
    if (player.getTilesCount() == 0) {
        text.setString("lost");
        text.setFillColor(sf::Color::Red);
    }
    else if (enemy.getTilesCount() == 0) {
        text.setString("won");
        text.setFillColor(sf::Color::Green);
    }
}

bool Game::chooseStartingPlayer() {
    return (rand() > (RAND_MAX / 2));
}

