#include "Ship.hpp"

Ship::Ship(short int length, int x, int y) {
    this->length = length;
    shipTiles = new Tile[length];

    for (int i = 0; i < length; i++) {
        Tile tile(tileWidth, shipColor);
        tile.setPosition(x + tileWidth * i, y);
        shipTiles[i] = tile;
    }
}

Ship::~Ship() {
    delete[] shipTiles;
}

void Ship::drawShip(sf::RenderWindow& window) {
    for (int i = 0; i < length; i++) {
        window.draw(shipTiles[i]);
    }
}

Tile Ship::getTile(int index) const {
    return shipTiles[index];
}

void Ship::changeColor(sf::Color color) {
    for (int i = 0; i < length; i++) {
        shipTiles[i].setFillColor(color);
    }
}

void Ship::hit(int index) {
    if (!shipTiles[index].isHit()) {
        shipTiles[index].setFillColor(shipHitColor);
        shipTiles[index].setHit();
        isSunk();
    }
}

int Ship::size() const {
    return length;
}

bool Ship::isSunk() {
    for (int i = 0; i < length; i++) {
        if (!shipTiles[i].isHit()) {
            return false;
        }
    }
    changeColor(shipSunkColor);
    return true;
}

void Ship::setPosition(sf::Vector2f position) {
    if (!rotation) {
        for (int i = 0; i < length; i++) {
            shipTiles[i].setPosition(position.x + tileWidth * i, position.y);
        }
    }
    else {
        for (int i = 0; i < length; i++) {
            shipTiles[i].setPosition(position.x, position.y + tileWidth * i);
        }
    }
}

int Ship::changeRotation() {
    sf::Vector2f position = shipTiles[0].getPosition();
    if (!rotation) {
        for (int i = 0; i < length; i++) {
            shipTiles[i].setPosition(position.x, position.y + tileWidth * i);
        }
        rotation = true;
        return 1;
    }
    else {
        for (int i = 0; i < length; i++) {
            shipTiles[i].setPosition(position.x + tileWidth * i, position.y);
        }
        rotation = false;
        return 0;
    }
}

bool Ship::getRotation() const {
    return rotation;
}

void Ship::setRotation(bool rotation) {
    this->rotation = rotation;
}

void Ship::setShipToPlaced() {
    isPlaced = true;
}

bool Ship::checkPlacedState() const {
    return isPlaced;
}
