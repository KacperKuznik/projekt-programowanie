#include "Grid.cpp"
class EnemyGrid : public Grid
{
	using Grid::Grid;
public:
	void shoot(sf::Vector2f mouse, Network& network) {
		auto pos = getClickedPosition(mouse);
		if (pos.row >= 0 && pos.col >= 0){
			tiles[pos.row][pos.col].setFillColor(sf::Color::Green);
			network.send(pos.row, pos.col);
		}
		return;
	}

};
