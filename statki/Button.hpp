#pragma once

#include "SFML/Graphics.hpp"
#include "SoundManager.hpp"
#include <string>

class Button : public sf::Drawable
{
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Event event;
    sf::Font font;
    SoundManager soundmanager;
    float x, y;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Button(std::string txt);
    const bool isClicked(const sf::Vector2f mouse);
    void changeButton(std::string txt = "", sf::Color color = sf::Color::Blue);
    void chPos(float x, float y);
};
