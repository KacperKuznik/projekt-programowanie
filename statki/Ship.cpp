#include "Ship.hpp"

Ship::Ship(short int _length, int x, int y) {
    length = _length;
    shipTiles = new Tile[length];

    for (int i = 0; i < length; i++) {
        Tile tile(tileWidth, shipColor);
        tile.setPosition(x + tileWidth * i, y);
        shipTiles[i] = tile;
    }
}

void Ship::drawShip(sf::RenderWindow& window) {
    for (int i = 0; i < length; i++) {
        window.draw(shipTiles[i]);
    }
}

Tile Ship::getTile(int i) {
    return shipTiles[i];
}

void Ship::chColor(sf::Color color) {
    for (int i = 0; i < length; i++) {
        shipTiles[i].setFillColor(color);
    }
}

void Ship::hit(int i) {
    if (!shipTiles[i].isHit()) {
        shipTiles[i].setFillColor(shipHitColor);
        shipTiles[i].setHit();
        isSunk();
    }
}

int Ship::size() {
    return length;
}

bool Ship::isSunk() {
    for (int i = 0; i < length; i++) {
        if (!shipTiles[i].isHit()) {
            return false;
        }
    }
    chColor(shipSunkColor);
    return true;
}

void Ship::setPos(sf::Vector2f position) {
    if (rotation == 0) {
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

int Ship::chRot() {
    sf::Vector2f position = shipTiles[0].getPosition();
    if (rotation == 0) {
        for (int i = 0; i < length; i++) {
            shipTiles[i].setPosition(position.x, position.y + tileWidth * i);
        }
        return 1;
    }
    else {
        for (int i = 0; i < length; i++) {
            shipTiles[i].setPosition(position.x + tileWidth * i, position.y);
        }
        return 0;
    }
}

bool Ship::getRot() {
    return rotation;
}

void Ship::setRot(bool _rotation) {
    rotation = _rotation;
}

void Ship::setShipToPlaced() {
    isPlaced = true;
}

bool Ship::checkPlacedState() {
    return isPlaced;
}
