#pragma once
#include <SFML/Graphics.hpp>
#include "tile.cpp"
#include <iostream>
#include "Network.cpp"

class Grid
{
private:
	int rows = 10;
	int cols = 10;

protected:
	sf::RectangleShape** tiles;

public:

	Grid( int width, int x, int y) {
		int tile_width = width / rows;
		tiles = new sf::RectangleShape * [rows];

		for (int row = 0; row < rows; row++) {
			tiles[row] = new sf::RectangleShape[cols];

			for (int col = 0; col < cols; col++) {
				Tile tile_obj(tile_width, sf::Color(240, 240, 240));
				sf::RectangleShape tile = tile_obj.createTile();
				tile.setPosition(x + tile_width *row, y + tile_width *col);
				tiles[row][col] = tile;
				
			}
		}

	}
	sf::RectangleShape** getTiles() {
		return tiles;
	};
	void drawGrid(sf::RenderWindow& window) {
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				window.draw(tiles[row][col]);
			}
		}

	}


};