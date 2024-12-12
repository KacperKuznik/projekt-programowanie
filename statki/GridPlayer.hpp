#pragma once

#include "Grid.hpp"
#include "Ship.hpp"

class GridPlayer : public Grid
{
	using Grid::Grid;
public:
	void mark(int row, int col, std::vector<Ship> ships, Network& network, Player& player);
	void placeShip(Ship& ship, sf::Vector2f mouse);
	bool isHit(int row, int col, Tile tile);
	bool canBeRotated(Ship ship);
};
