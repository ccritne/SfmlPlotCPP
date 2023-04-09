#include "../include/Textbox.hpp"

Textbox::Textbox(float x, float y, float width, float height, sf::Font& font) {
    h = height;
    w = width;

    box.setPosition(sf::Vector2f(x, y));
    box.setSize(sf::Vector2f(width, height));
    box.setOutlineThickness(1);
    box.setFillColor(sf::Color::Black);
    box.setOutlineColor(sf::Color::White);

    text.setFont(font);
    text.setPosition(sf::Vector2f(x + 0.05, y + 0.05));

    text.setString("");
}

void Textbox::setText(std::string txt) {
    text.setString(txt);

}

sf::Vector2f Textbox::getCoord() {
    return box.getPosition();
}

dim Textbox::getDim() {
    return { w, h };
}

bool Textbox::contains(sf::Vector2i coord) {
    if (coord.x > box.getPosition().x && coord.x < box.getPosition().x + w &&
        coord.y > box.getPosition().y && coord.y < box.getPosition().y + h)
        return true;
    else
        return false;
}
