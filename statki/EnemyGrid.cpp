#include "Grid.cpp"
class EnemyGrid : public Grid
{
	using Grid::Grid;
public:
	void shoot(sf::Vector2f mouse, Network& network, Player& enemy) {
		auto pos = getClickedPosition(mouse);
		if (pos.row >= 0 && pos.col >= 0){
			soundmanager.shoot();
			network.send(pos.row, pos.col);
			auto result = network.listen();
			while (result.status != 0) {
				result = network.listen();
			};
			bool isHit;
			result.packet >> isHit;
			cout << result.status << "ishit: " << isHit;
			if (isHit) {
				enemy.hit();
				tiles[pos.row][pos.col].setFillColor(sf::Color::Red);
			}
			else {
				tiles[pos.row][pos.col].setFillColor(missed_shot_color);
			}
		}
		return;
	}

};
