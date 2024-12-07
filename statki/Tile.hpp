#pragma once

#include "SFML/Graphics.hpp"

class Tile : public sf::Drawable {
private:
    sf::RectangleShape tile;
    int tileWidth;
    sf::Color color;
    bool containsShip = false;
    bool hit = false;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Tile() = default;
    Tile(int tileWidth, sf::Color color);

    void createTile();
    void setPosition(float x, float y);
    sf::FloatRect getGlobalBounds() const;
    void setFillColor(sf::Color color);
    sf::Color getFillColor() const;
    bool isHit() const;
    void setHit();
    sf::Vector2f getPosition() const;
    sf::Vector2f getCenter() const;
    bool checkShipContent() const;
    void changeShipContent(bool containsShip);
};
