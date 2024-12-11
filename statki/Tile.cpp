#include "Tile.hpp"

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(tile, states);
}

Tile::Tile() = default;

Tile::Tile(int _tile_width, sf::Color _color) {
	tile_width = _tile_width;
	color = _color;
	createTile();
}

void Tile::createTile() {
	sf::RectangleShape _tile(sf::Vector2f(tile_width, tile_width));
	_tile.setFillColor(color);
	_tile.setOutlineThickness(2.f);
	_tile.setOutlineColor(sf::Color(0, 0, 0));
	_tile.setPosition(0, 0);
	tile = _tile;
}

void Tile::setPosition(float x, float y) {
	tile.setPosition(x, y);
}

sf::FloatRect Tile::getGlobalBounds() {
	return tile.getGlobalBounds();
}

void Tile::setFillColor(sf::Color color) {
	tile.setFillColor(color);
}

sf::Color Tile::getFillColor() {
	return tile.getFillColor();
}

bool Tile::isHit() {
	return hit;
}

void Tile::setHit() {
	hit = true;
}

sf::Vector2f Tile::getPosition() {
	return tile.getPosition();
}

sf::Vector2f Tile::getCenter() {
	sf::FloatRect tile_bounds = tile.getGlobalBounds();
	sf::Vector2f center;
	center.x = tile_bounds.left + tile_bounds.width / 2;
	center.y = tile_bounds.top + tile_bounds.height / 2;
	return center;
}

bool Tile::checkShipContent() {
	return containsShip;
}

void Tile::chgShipContent(bool chg) {
	containsShip = chg;
}
