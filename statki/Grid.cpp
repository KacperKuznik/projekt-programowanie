#include "Grid.hpp"

Grid::Grid(int width, int x, int y) {
    int tileWidth = width / rows;
    tiles = new Tile * [rows];

    for (int row = 0; row < rows; row++) {
        tiles[row] = new Tile[cols];

        for (int col = 0; col < cols; col++) {
            Tile tile(tileWidth, tileColor);
            tile.setPosition(x + tileWidth * row, y + tileWidth * col);
            tiles[row][col] = tile;
        }
    }
}

Grid::~Grid() {
    for (int row = 0; row < rows; row++) {
        delete[] tiles[row];
    }
    delete[] tiles;
}

Tile** Grid::getTiles() {
    return tiles;
}

void Grid::drawGrid(sf::RenderWindow& window) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            window.draw(tiles[row][col]);
        }
    }
}

Grid::Position Grid::getClickedPosition(sf::Vector2f mouse) {
    Position pos;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (tiles[row][col].getGlobalBounds().contains(mouse)) {
                pos.row = row;
                pos.col = col;
                return pos;
            }
        }
    }
    return pos; // Default position if no tile is clicked
}

void Grid::checkShipContent() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (!tiles[row][col].checkShipContent()) {
                tiles[row][col].setFillColor(sf::Color::White);
            }
            else {
                tiles[row][col].setFillColor(sf::Color::Blue);
            }
        }
    }
}

int Grid::getRows() const {
    return rows;
}

int Grid::getCols() const {
    return cols;
}
