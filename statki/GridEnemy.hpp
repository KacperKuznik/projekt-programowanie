#pragma once

#include "Grid.hpp"

class GridEnemy : public Grid
{
	using Grid::Grid;
private:
	sf::Color shipHitColor = sf::Color(200, 0, 0);
public:
	void shoot(sf::Vector2f mouse, Network& network, Player& enemy, Player& player);
};
