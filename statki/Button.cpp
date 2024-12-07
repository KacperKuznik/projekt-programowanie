#include "Button.hpp"

Button::Button(std::string buttonText) {
    posX = 500;
    posY = 800;

    sf::RectangleShape tempBox(sf::Vector2f(150, 50));

    if (!font.loadFromFile("fonts/arial.ttf")) {
        // Handle font loading failure here if necessary
    }

    text.setFont(font);

    tempBox.setFillColor(sf::Color::Blue);
    tempBox.setOutlineThickness(2.f);
    tempBox.setOutlineColor(sf::Color(0, 0, 0));
    tempBox.setPosition(posX, posY);

    box = tempBox;

    text.setCharacterSize(static_cast<unsigned int>(50 * 0.75));
    text.setPosition(posX, posY);
    text.setString(buttonText);
    text.setFillColor(sf::Color::White);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(box, states);
    target.draw(text, states);
}

bool Button::isClicked(const sf::Vector2f mousePosition) {
    if (event.type != sf::Event::MouseButtonPressed) {
        return false;
    }

    if (box.getGlobalBounds().contains(mousePosition)) {
        soundManager.playClick();
        return true;
    }

    return false;
}

void Button::changeButton(std::string buttonText, sf::Color buttonColor) {
    if (!buttonText.empty()) {
        text.setString(buttonText);
    }
    box.setFillColor(buttonColor);
}

void Button::changePosition(float x, float y) {
    box.setPosition(x, y);
    text.setPosition(x, y);
}
