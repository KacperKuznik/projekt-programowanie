#include "GridEnemy.hpp"

void GridEnemy::shoot(sf::Vector2f mouse, Network& network, Player& enemy, Player& player, GridPlayer& gridPLayer, std::string history_file_name) {
	auto pos = getClickedPosition(mouse);
	if (pos.row >= 0 && pos.col >= 0 && tiles[pos.row][pos.col].getFillColor() != missedShotColor && !tiles[pos.row][pos.col].isHit()) {
		soundManager.shoot();
		network.send(pos.row, pos.col);
		auto result = network.listen();
		while (result.status != 0) {
			result = network.listen();
		};
		bool isHit;
		result.packet >> isHit;
		if (isHit) {
			enemy.hit();
			tiles[pos.row][pos.col].setFillColor(shipHitColor);
			std::cout << "Ship hited" << std::endl;
			Game::printState(gridPLayer, history_file_name);
		}
		else {
			tiles[pos.row][pos.col].setFillColor(missedShotColor);
			player.changeTurn();
			std::cout << "Ship missed" << std::endl;
			Game::printState(gridPLayer, history_file_name);
		}
	}
	return;
}
