#include "Button.hpp"

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(box, states);
    target.draw(text, states);
}

Button::Button(std::string txt) {
    x = 500;
    y = 800;
    sf::RectangleShape _box(sf::Vector2f(150, 50));
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font file" << std::endl;
    }
    text.setFont(font);
    _box.setFillColor(sf::Color::Blue);
    _box.setOutlineThickness(2.f);
    _box.setOutlineColor(sf::Color(0, 0, 0));
    _box.setPosition(x, y);
    box = _box;

    text.setFont(font);
    text.setCharacterSize(50 * 0.75);
    text.setPosition(x, y);
    text.setString(txt);
    text.setFillColor(sf::Color::White);
}

const bool Button::isClicked(const sf::Vector2f mouse) {
    if (!event.type == sf::Event::MouseButtonPressed) {
        return false;
    }
    if (box.getGlobalBounds().contains(mouse)) {
        soundManager.click();
        return true;
    }
    return false;
}

void Button::changeButton(std::string txt, sf::Color color) {
    text.setString(txt);
    box.setFillColor(color);
}

void Button::chPos(float x, float y) {
    box.setPosition(x, y);
    text.setPosition(x, y);
}
