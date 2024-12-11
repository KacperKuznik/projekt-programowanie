#include "Grid.hpp"

Grid::Grid(int width, int x, int y) {
	int tile_width = width / rows;
	tiles = new Tile * [rows];

	for (int row = 0; row < rows; row++) {
		tiles[row] = new Tile[cols];

		for (int col = 0; col < cols; col++) {
			Tile tile(tile_width, tile_color);
			tile.setPosition(x + tile_width * row, y + tile_width * col);
			tiles[row][col] = tile;
		}
	}
}

Tile** Grid::getTiles() {
	return tiles;
};

void Grid::drawGrid(sf::RenderWindow& window) {
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			window.draw(tiles[row][col]);
		}
	}
}

Grid::Position Grid::getClickedPosition(sf::Vector2f mouse) {

	struct Position pos;
	for (int row = 0; row < 10; row++)
		for (int col = 0; col < 10; col++)
			if (tiles[row][col].getGlobalBounds().contains(mouse)) {
				pos.row = row;
				pos.col = col;
				return pos;
			}
}

void Grid::checkShipContent() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (tiles[i][j].checkShipContent() == 0) {
				tiles[i][j].setFillColor(sf::Color::White);
			}
			else
			{
				tiles[i][j].setFillColor(sf::Color::Blue);
			}
		}
	}
}

int Grid::getRows() {
	return rows;
}

int Grid::getCols() {
	return cols;
}
