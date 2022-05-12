#pragma once
#include "tile.cpp"
#include <iostream>

class Ship
{
private:
	short int length  = 1;
	int tile_width = 50;
	Tile* ship_tiles;
public:
	Ship(short int _length, int x, int y) {
		length = _length;
		ship_tiles = new Tile[length];
		for (int i = 0; i < length; i++) {
			Tile tile(tile_width, sf::Color::Blue);
			tile.setPosition(x + tile_width * i, y);
			ship_tiles[i] = tile;

		}

	}
	void drawShip(sf::RenderWindow& window) {
		

		for (int i = 0; i < length; i++) {

		window.draw(ship_tiles[i]);
	
		}
	}

	Tile getTile(int i) {
		return ship_tiles[i];
	}

	void chColor(sf::Color color) {
		for (int i = 0; i < length; i++) {
			ship_tiles[i].setFillColor(color);
		}
	}
	void hit(int i) {
		ship_tiles[i].setFillColor(sf::Color::Red);
	}

	int size() {
		return length;
	}


	void setPos(sf::Vector2f position) {
		for (int i = 0; i < length; i++) {
			ship_tiles[i].setPosition(position.x + tile_width * i,position.y);
		}
	}

};