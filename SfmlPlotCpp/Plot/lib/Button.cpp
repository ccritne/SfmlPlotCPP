#include "../include/Button.hpp"

Button::Button(float xStart, float yStart, float width, float height, sf::Font& font) {
    h = height;
    w = width;

    x = xStart;
    y = yStart;

    box.setPosition(sf::Vector2f(x, y));
    box.setSize(sf::Vector2f(width, height));
    box.setOutlineThickness(1);
    box.setOutlineColor(sf::Color::White);

    text.setFont(font);
    text.setCharacterSize(height - 0.05);
    text.setFillColor(sf::Color::Black);
    text.setPosition(sf::Vector2f(x, y));

    text.setString("");
}

void Button::setText(std::string txt) {
    
    text.setString(txt);

}

sf::Vector2f Button::getCoord() {
    return {x, y};
}

dim Button::getDim() {
    return { w, h };
}

bool Button::contains(sf::Vector2i coord) {
    if (coord.x > x && coord.x < x + w &&
        coord.y > y && coord.y < y + h)
        return true;
    
    return false;
}

void Button::setSize(float width, float height) {

    w = width;
    h = height;

    box.setSize(sf::Vector2f(width, height));

    text.setCharacterSize(height - 0.05);
}

void Button::setPosition(float xStart, float yStart) {

    x = xStart;
    y = yStart;

    box.setPosition(sf::Vector2f(x, y));
    text.setPosition(sf::Vector2f(x, y));
}