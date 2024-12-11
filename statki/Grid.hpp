#pragma once

#include "SFML/Graphics.hpp"
#include "Tile.hpp"
#include "Network.hpp"
#include "Player.hpp"
#include "SoundManager.hpp"
#include <iostream>

class Grid
{
private:
	int rows = 10;
	int cols = 10;
	struct Position {
		int row = -1;
		int col = -1;
	};
protected:
	Tile** tiles;
	sf::Color tile_color = sf::Color(240, 240, 240);
	sf::Color missed_shot_color = sf::Color(200, 200, 200);
	SoundManager soundmanager;
public:
	Grid(int width, int x, int y);
	Tile** getTiles();
	void drawGrid(sf::RenderWindow& window);
	Grid::Position getClickedPosition(sf::Vector2f mouse);
	void checkShipContent();
	int getRows();
	int getCols();
};
