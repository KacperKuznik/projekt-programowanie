#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
private:
    sf::RectangleShape tile;
	int tile_width;

public:
	Tile(int _tile_width) {
		tile_width = _tile_width;

	}
	sf::RectangleShape createTile() {
		sf::RectangleShape tile(sf::Vector2f(tile_width, tile_width));
		tile.setFillColor(sf::Color(240, 240, 240));
		tile.setOutlineThickness(2.f);
		tile.setOutlineColor(sf::Color(0, 0, 0));
		return tile;
	}
};