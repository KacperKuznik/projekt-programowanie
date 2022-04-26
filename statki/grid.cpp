#include <SFML/Graphics.hpp>
#include "tile.cpp"
class Grid
{
private:
	int rows = 10;
	int cols = 10;

public:
	Grid(sf::RenderWindow& window, int width, int x, int y) {
		int tile_width = width / rows;

		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				sf::RectangleShape tile(sf::Vector2f(tile_width, tile_width));
				tile.setPosition(x + tile_width *row, y + tile_width *col);
				tile.setFillColor(sf::Color(240, 240, 240));
				tile.setOutlineThickness(2.f);
				tile.setOutlineColor(sf::Color(0, 0, 0));
				window.draw(tile);
			}
		}
	}
};