#include "../include/Line.hpp"

Line::Line() {
    line[0].position = sf::Vector2f(0, 0);
    line[1].position = sf::Vector2f(0, 0);
}

Line::Line(float startX, float startY, float endX, float endY) {
    line[0].position = sf::Vector2f(startX, startY);
    line[1].position = sf::Vector2f(endX, endY);
}

void Line::setPosition(float startX, float startY, float endX, float endY) {
    line[0].position = sf::Vector2f(startX, startY);
    line[1].position = sf::Vector2f(endX, endY);
}

void Line::setLineColor(sf::Color color) {
    line[0].color = color;
    line[1].color = color;
}
