#pragma once

#include "Tile.hpp"
#include <iostream>

template <typename T>
class Ship
{
private:
	short int length = 1;
	int tileWidth = 50;

	bool rotation = 0;
	bool isPlaced = false;

	// Tile* shipTiles;
	std::vector<T> shipTiles;
	sf::Color shipColor = sf::Color(0, 255, 0);
	sf::Color shipHitColor = sf::Color(200, 0, 0);
	sf::Color shipSunkColor = sf::Color(255, 0, 0);
public:
	Ship(short int _length, int x, int y);
	void drawShip(sf::RenderWindow& window);
	T& getTile(int i);
	void chColor(sf::Color color);
	void hit(int i);
	int size() const;
	bool isSunk();
	void setPos(sf::Vector2f position);
	int chRot();
	bool getRot() const;
	void setRot(bool _rotation);
	void setShipToPlaced();
	bool checkPlacedState() const;
};


template <typename T>
Ship<T>::Ship(short int _length, int x, int y) : length(_length) {
    for (int i = 0; i < length; i++) {
        T tile(tileWidth, shipColor);
        tile.setPosition(x + tileWidth * i, y);
        shipTiles.push_back(tile);
    }
}

template <typename T>
void Ship<T>::drawShip(sf::RenderWindow& window) {
    for (auto& tile : shipTiles) {
        window.draw(tile);
    }
}

template <typename T>
T& Ship<T>::getTile(int i) {
    return shipTiles.at(i);
}

template <typename T>
void Ship<T>::chColor(sf::Color color) {
    for (auto& tile : shipTiles) {
        tile.setFillColor(color);
    }
}

template <typename T>
void Ship<T>::hit(int i) {
    if (!shipTiles[i].isHit()) {
        shipTiles[i].setFillColor(shipHitColor);
        shipTiles[i].setHit();
        isSunk();
    }
}

template <typename T>
int Ship<T>::size() const {
    return length;
}

template <typename T>
bool Ship<T>::isSunk() {
    for (auto& tile : shipTiles) {
        if (!tile.isHit()) {
            return false;
        }
    }
    chColor(shipSunkColor);
    return true;
}

template <typename T>
void Ship<T>::setPos(sf::Vector2f position) {
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

template <typename T>
int Ship<T>::chRot() {
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

template <typename T>
bool Ship<T>::getRot() const {
    return rotation;
}

template <typename T>
void Ship<T>::setRot(bool _rotation) {
    rotation = _rotation;
}

template <typename T>
void Ship<T>::setShipToPlaced() {
    isPlaced = true;
}

template <typename T>
bool Ship<T>::checkPlacedState() const {
    return isPlaced;
}
