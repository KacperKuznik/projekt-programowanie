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

	struct Position
	{
		int row = -1;
		int col = -1;
	};
protected:
	Tile** tiles;
	sf::Color tile_color = sf::Color(240, 240, 240);
	sf::Color missed_shot_color = sf::Color(200, 200, 200);
public:

	Grid( int width, int x, int y) {
		int tile_width = width / rows;
		tiles = new Tile * [rows];

		for (int row = 0; row < rows; row++) {
			tiles[row] = new Tile[cols];

			for (int col = 0; col < cols; col++) {
				Tile tile(tile_width, tile_color);
				tile.setPosition(x + tile_width *row, y + tile_width *col);
				tiles[row][col] = tile;
				
			}
		}

	}
	Tile** getTiles() {
		return tiles;
	};
	void drawGrid(sf::RenderWindow& window) {
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				window.draw(tiles[row][col]);
			}
		}

	}
	auto getClickedPosition(sf::Vector2f mouse) {

		struct Position pos;
		for (int row = 0; row < 10; row++)
			for (int col = 0; col < 10; col++)
				if (tiles[row][col].getGlobalBounds().contains(mouse)) {
					pos.row = row;
					pos.col = col;
					return pos;
				}
	}


};