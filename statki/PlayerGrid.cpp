#include "Grid.cpp"
class PlayerGrid : public Grid
{
	using Grid::Grid;

public:
	void mark(int row, int col) {
		tiles[row][col].setFillColor(sf::Color::Blue);
	}
};