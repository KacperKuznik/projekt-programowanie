#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "SoundManager.hpp"

class Button : public sf::Drawable {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Event event;
    sf::Font font;
    SoundManager soundManager;

    float posX, posY;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Button(std::string buttonText);

    bool isClicked(const sf::Vector2f mousePosition);

    void changeButton(std::string buttonText = "", sf::Color buttonColor = sf::Color::Blue);

    void changePosition(float x, float y);
};
