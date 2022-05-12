#include "Grid.cpp"
#include "Ship.cpp"
class PlayerGrid : public Grid
{
	using Grid::Grid;

public:
	void mark(int row, int col, std::vector< Ship > ships, Network& network) {
		for (int i = 0; i < ships.size(); i++) {
			for (int j = 0; j < ships[i].size(); j++) {
				if (isHit(row, col, ships[i].getTile(j))) {
					ships[i].hit(j);
					network.reply(true);
					return;
				}
			}
		}
		network.reply(false);
		tiles[row][col].setFillColor(missed_shot_color);
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
	bool isHit(int row, int col, Tile tile) {
		if (tile.getGlobalBounds().contains(tiles[row][col].getCenter())) {
				return true;
		}
		return false;
		
		
	}
};
