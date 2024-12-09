#include "Tile.hpp"

Tile::Tile(int tileWidth, sf::Color color) {
    this->tileWidth = tileWidth;
    this->color = color;
    createTile();
}

void Tile::createTile() {
    sf::RectangleShape tempTile(sf::Vector2f(tileWidth, tileWidth));
    tempTile.setFillColor(color);
    tempTile.setOutlineThickness(2.f);
    tempTile.setOutlineColor(sf::Color(0, 0, 0));
    tempTile.setPosition(0, 0);
    tile = tempTile;
}

void Tile::setPosition(float x, float y) {
    tile.setPosition(x, y);
}

sf::FloatRect Tile::getGlobalBounds() const {
    return tile.getGlobalBounds();
}

void Tile::setFillColor(sf::Color color) {
    tile.setFillColor(color);
}

sf::Color Tile::getFillColor() const {
    return tile.getFillColor();
}

bool Tile::isHit() const {
    return hit;
}

void Tile::setHit() {
    hit = true;
}

sf::Vector2f Tile::getPosition() const {
    return tile.getPosition();
}

sf::Vector2f Tile::getCenter() const {
    sf::FloatRect tileBounds = tile.getGlobalBounds();
    return { tileBounds.left + tileBounds.width / 2, tileBounds.top + tileBounds.height / 2 };
}

bool Tile::checkShipContent() const {
    return containsShip;
}

void Tile::changeShipContent(bool containsShip) {
    this->containsShip = containsShip;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(tile, states);
}
