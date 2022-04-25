#include <SFML/Graphics.hpp>
#include "tile.cpp"
class Grid
{
private:
	int rows = 10;
	int cols = 10;
public:
	Grid(sf::RenderWindow& window) {


		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				sf::RectangleShape tile(sf::Vector2f(50.f, 50.f));
				tile.setPosition(50.f*row, 50.f*col);
				tile.setFillColor(sf::Color(240, 240, 240));
				tile.setOutlineThickness(2.f);
				tile.setOutlineColor(sf::Color(0, 0, 0));
				window.draw(tile);
			}
		}
	}
};