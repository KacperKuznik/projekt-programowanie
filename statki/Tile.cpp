#include "Tile.hpp"

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(tile, states);
}

Tile::Tile() = default;

Tile::Tile(int tileWidth, sf::Color color) {
	this->tileWidth = tileWidth;
	this->color = color;
	createTile();
}

void Tile::createTile() {
	sf::RectangleShape tile(sf::Vector2f(tileWidth, tileWidth));
	tile.setFillColor(color);
	tile.setOutlineThickness(2.f);
	tile.setOutlineColor(sf::Color(0, 0, 0));
	tile.setPosition(0, 0);
	this->tile = tile;
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
	sf::FloatRect tileBounds = tile.getGlobalBounds();
	sf::Vector2f center;
	center.x = tileBounds.left + tileBounds.width / 2;
	center.y = tileBounds.top + tileBounds.height / 2;
	return center;
}

bool Tile::checkShipContent() {
	return containsShip;
}

void Tile::chgShipContent(bool chg) {
	containsShip = chg;
}
