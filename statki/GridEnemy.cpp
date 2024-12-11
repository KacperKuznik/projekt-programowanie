#include "GridEnemy.hpp"


void GridEnemy::shoot(sf::Vector2f mouse, Network& network, Player& enemy, Player& player) {
	auto pos = getClickedPosition(mouse);
	if (pos.row >= 0 && pos.col >= 0 && tiles[pos.row][pos.col].getFillColor() != missed_shot_color && !tiles[pos.row][pos.col].isHit()) {
		soundmanager.shoot();
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
		}
		else {
			tiles[pos.row][pos.col].setFillColor(missed_shot_color);
			player.changeTurn();
		}
	}
	return;
}
