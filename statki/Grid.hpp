#pragma once

#include "SFML/Graphics.hpp"
#include "Tile.hpp"
#include "SoundManager.hpp"

class Grid {
private:
    int rows = 10;
    int cols = 10;

    struct Position {
        int row = -1;
        int col = -1;
    };

protected:
    Tile** tiles;
    sf::Color tileColor = sf::Color(240, 240, 240);
    sf::Color missedShotColor = sf::Color(200, 200, 200);
    SoundManager soundManager;

public:
    Grid(int width, int x, int y);
    ~Grid();

    Tile** getTiles();
    void drawGrid(sf::RenderWindow& window);
    Position getClickedPosition(sf::Vector2f mouse);
    void checkShipContent();

    int getRows() const;
    int getCols() const;
};
