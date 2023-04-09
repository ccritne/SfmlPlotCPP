#include "../include/Button.hpp"

Button::Button(float x, float y, float width, float height, sf::Font& font) {
    h = height;
    w = width;

    box.setPosition(sf::Vector2f(x, y));
    box.setSize(sf::Vector2f(width, height));
    box.setOutlineThickness(1);
    box.setOutlineColor(sf::Color::White);

    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(x + 35 / 4, y + 35 / 4));

    text.setString("");
}

void Button::setText(std::string txt) {
    text.setString(txt);

}

sf::Vector2f Button::getCoord() {
    return box.getPosition();
}

dim Button::getDim() {
    return { w, h };
}

bool Button::contains(sf::Vector2i coord) {
    if (coord.x > box.getPosition().x && coord.x < box.getPosition().x + w &&
        coord.y > box.getPosition().y && coord.y < box.getPosition().y + h)
        return true;
    else
        return false;
}