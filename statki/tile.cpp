#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h> 
#include <stdlib.h> 
#include <stdio.h>
class Tile : public sf::Drawable
{
private:
    sf::RectangleShape tile;
	int tile_width;
	sf::Color color;
	bool containsShip = false;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(tile, states);
	}
public:
	Tile() = default;
	Tile(int _tile_width, sf::Color _color) {
		tile_width = _tile_width;
		color = _color;
		createTile();
	}
	void createTile() {
		sf::RectangleShape _tile(sf::Vector2f(tile_width, tile_width));
		_tile.setFillColor(color);
		_tile.setOutlineThickness(2.f);
		_tile.setOutlineColor(sf::Color(0, 0, 0));
		_tile.setPosition(0, 0);
		tile = _tile;
	}
	void setPosition(float x, float y) {
		tile.setPosition(x, y);
	}
	sf::FloatRect getGlobalBounds() {
		return tile.getGlobalBounds();
	}
	void setFillColor(sf::Color color) {
		tile.setFillColor(color);
	}
	sf::Vector2f getPosition() {
		return tile.getPosition();
	}
	sf::Vector2f getCenter() {
		sf::FloatRect tile_bounds = tile.getGlobalBounds();
		sf::Vector2f center;
		center.x = tile_bounds.left + tile_bounds.width / 2;
		center.y = tile_bounds.top + tile_bounds.height / 2;
		return center;
	}
	bool checkShipContent() {
		return containsShip;
	}
	void chgShipContent(bool chg) {
		containsShip = chg;
	}
};