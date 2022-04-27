#include <SFML/Graphics.hpp>
#include "tile.cpp"
#include <iostream>
class Grid
{
private:
	int rows = 10;
	int cols = 10;
	sf::RectangleShape **tiles;

public:
	Grid( int width, int x, int y) {
		int tile_width = width / rows;
		tiles = new sf::RectangleShape * [rows];

		for (int row = 0; row < rows; row++) {
			tiles[row] = new sf::RectangleShape[cols];

			for (int col = 0; col < cols; col++) {
				sf::RectangleShape tile(sf::Vector2f(tile_width, tile_width));
				tile.setPosition(x + tile_width *row, y + tile_width *col);
				tile.setFillColor(sf::Color(240, 240, 240));
				tile.setOutlineThickness(2.f);
				tile.setOutlineColor(sf::Color(0, 0, 0));
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