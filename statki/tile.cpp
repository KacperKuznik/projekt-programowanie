#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
private:
    sf::RectangleShape tile;
	int tile_width;
	sf::Color color;

public:
	Tile(int _tile_width, sf::Color _color) {
		tile_width = _tile_width;
		color = _color;

	}
	sf::RectangleShape createTile() {
		sf::RectangleShape tile(sf::Vector2f(tile_width, tile_width));
		tile.setFillColor(color);
		tile.setOutlineThickness(2.f);
		tile.setOutlineColor(sf::Color(0, 0, 0));
		return tile;
	}
};