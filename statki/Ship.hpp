#pragma once

#include "Tile.hpp"
#include <SFML/Graphics.hpp>

class Ship {
private:
    short int length = 1;
    int tileWidth = 50;

    bool rotation = false;
    bool isPlaced = false;

    Tile* shipTiles;
    sf::Color shipColor = sf::Color(0, 255, 0);
    sf::Color shipHitColor = sf::Color(200, 0, 0);
    sf::Color shipSunkColor = sf::Color(255, 0, 0);

public:
    Ship(short int length, int x, int y);
    ~Ship();

    void drawShip(sf::RenderWindow& window);
    Tile getTile(int index) const;

    void changeColor(sf::Color color);
    void hit(int index);

    int size() const;
    bool isSunk();

    void setPosition(sf::Vector2f position);
    int changeRotation();
    bool getRotation() const;
    void setRotation(bool rotation);

    void setShipToPlaced();
    bool checkPlacedState() const;
};
