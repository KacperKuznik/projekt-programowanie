#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "SoundManager.cpp"

class Button : public sf::Drawable
{
private:
	sf::RectangleShape box;
    sf::Text text;
    sf::Event event;
    sf::Font font;
    SoundManager soundmanager;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(box, states);
        target.draw(text, states);
    }
    float x, y;

public:
    Button(std::string txt) {
        x = 500;
        y = 800;
        sf::RectangleShape _box(sf::Vector2f(150, 50));
        if (!font.loadFromFile("fonts/arial.ttf"))
        {
        }
        text.setFont(font);
        _box.setFillColor(sf::Color::Blue);
        _box.setOutlineThickness(2.f);
        _box.setOutlineColor(sf::Color(0, 0, 0));
        _box.setPosition(x, y);
        box = _box;

        text.setFont(font);
        text.setCharacterSize(50*0.75);
        text.setPosition(x, y);
        //sf::FloatRect textRect = text.getLocalBounds();
        //text.setOrigin(textRect.left + textRect.width / 2.0f,
        //    textRect.top + textRect.height / 2.0f);
        //text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
        text.setString(txt);
        text.setFillColor(sf::Color::White);
    }
    const bool isClicked(const sf::Vector2f mouse)
    {
        if (!event.type == sf::Event::MouseButtonPressed) {
            return false;
        }
        if (box.getGlobalBounds().contains(mouse)) {
            soundmanager.click();
            return true;
        }
        return false;
    }
    void changeButton(std::string txt = "", sf::Color color = sf::Color::Blue) {
        text.setString(txt);
        box.setFillColor(color);
    }

    void chPos(float x, float y) {
        box.setPosition(x, y);
        text.setPosition(x, y);
    }
};