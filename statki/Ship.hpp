#pragma once

#include "Tile.hpp"
#include <iostream>

class Ship
{
private:
	short int length = 1;
	int tile_width = 50;

	bool rotation = 0;
	bool isPlaced = false;

	Tile* ship_tiles;
	sf::Color shipColor = sf::Color(0, 255, 0);
	sf::Color shipHitColor = sf::Color(200, 0, 0);
	sf::Color shipSunkColor = sf::Color(255, 0, 0);
public:
	Ship(short int _length, int x, int y);
	void drawShip(sf::RenderWindow& window);
	Tile getTile(int i);
	void chColor(sf::Color color);
	void hit(int i);
	int size();
	bool isSunk();
	void setPos(sf::Vector2f position);
	int chRot();
	bool getRot();
	void setRot(bool _rotation);
	void setShipToPlaced();
	bool checkPlacedState();
};
