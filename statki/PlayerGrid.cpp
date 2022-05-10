#include "Grid.cpp"
#include "Ship.cpp"
class PlayerGrid : public Grid
{
	using Grid::Grid;

public:
	void mark(int row, int col) {
		tiles[row][col].setFillColor(sf::Color::Blue);
	}
	void placeShip(Ship& ship, sf::Vector2f mouse) {
		auto pos = getClickedPosition(mouse);
		if (pos.row >= 0 && pos.col >= 0) {
			if (pos.row + ship.size() > 10)
			{

			}
			else
			{
				sf::Vector2f xy = tiles[pos.row][pos.col].getPosition();
				ship.setPos(xy);
			}
		}
	}
};
