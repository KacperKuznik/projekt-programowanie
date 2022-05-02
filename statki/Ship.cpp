#pragma once
#include "tile.cpp"
#include <iostream>

class Ship
{
private:
	short int length  = 1;
	int tile_width = 50;
	sf::RectangleShape* ship_tiles;
public:
	Ship(short int _length, int x, int y) {
		length = _length;
		ship_tiles = new sf::RectangleShape[length];
		for (int i = 0; i < length; i++) {
			Tile tile_obj(tile_width, sf::Color::Blue);
			sf::RectangleShape tile = tile_obj.createTile();
			tile.setPosition(x + tile_width * i, y);
			ship_tiles[i] = tile;

		}

	}
	void drawShip(sf::RenderWindow& window) {
		

		for (int i = 0; i < length; i++) {

		window.draw(ship_tiles[i]);
	
		}
	}
};