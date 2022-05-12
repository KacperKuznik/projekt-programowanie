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
			if (ship.getRot() == 0) {
				if (pos.row + ship.size() > 10)
				{

				}
				else
				{
					sf::Vector2f xy = tiles[pos.row][pos.col].getPosition();
					ship.setPos(xy);
				}
			}
			else {
				if (pos.col + ship.size() > 10)
				{

				}
				else
				{
					sf::Vector2f xy = tiles[pos.row][pos.col].getPosition();
					ship.setPos(xy);
				}
			}
		}
	}
	bool isHit(int row, int col, sf::RectangleShape tile) {
		sf::FloatRect tile_bounds = tiles[row][col].getGlobalBounds();
		sf::Vector2f pos;
		pos.x = tile_bounds.left + tile_bounds.width / 2;
		pos.y = tile_bounds.top + tile_bounds.height / 2;
		bool hit = false;
		if (tile.getGlobalBounds().contains(pos)) {
					hit = true;
		}
	
	
		
		return hit;
	}

	bool canBeRotated(Ship ship) {
		auto pos = getClickedPosition(ship.getTile(0).getPosition());
		int size = ship.size();
		bool rotation = ship.getRot();

		std::cout << std::endl << "Row: " << pos.row << " Col: " << pos.col << " Size: " << size << " Rotation: " << rotation;
		
		if (rotation == 0) {
			if (pos.row + size > 10) {
				return EXIT_FAILURE;
			}
			else {
				return EXIT_SUCCESS;
			}
		}
		else
		{
			if (pos.col + size > 10) {
				return EXIT_FAILURE;
			}
			else {
				return EXIT_SUCCESS;
			}
		}
	}
};
