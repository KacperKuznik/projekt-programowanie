#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <time.h> 
#include <stdlib.h> 
#include <stdio.h>

class Tile : public sf::Drawable
{
private:
	sf::RectangleShape tile;
	int tileWidth;
	sf::Color color;
	bool containsShip = false;
	bool hit = false;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	Tile();
	Tile(int tileWidth, sf::Color color);
	void createTile();
	void setPosition(float x, float y);
	sf::FloatRect getGlobalBounds();
	void setFillColor(sf::Color color);
	sf::Color getFillColor();
	bool isHit();
	void setHit();
	sf::Vector2f getPosition();
	sf::Vector2f getCenter();
	bool checkShipContent();
	void chgShipContent(bool chg);
};
