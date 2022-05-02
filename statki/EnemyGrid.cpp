#include "Grid.cpp"
class EnemyGrid : public Grid
{
	using Grid::Grid;
public:
	void shoot(sf::Vector2f mouse, Network& network) {

		for (int row = 0; row < 10; row++)
			for (int col = 0; col < 10; col++)
				if (tiles[row][col].getGlobalBounds().contains(mouse)) {
					tiles[row][col].setFillColor(sf::Color::Green);
					network.send(row, col);
					return;
				}

	}
};