#include "../include/Point.hpp"

Point::Point(float x, float y) {
    p.setPosition(x, y);
}

Point::Point(double radiusPoint, float x, float y) {
    p.setRadius(radiusPoint);
    p.setPosition(x, y);
}

Point::Point(double radiusPoint, float x, float y, sf::Color color) {
    p.setRadius(radiusPoint);
    p.setPosition(x, y);
    p.setFillColor(color);
}

void Point::setRadius(double radiusPoint) {
    p.setRadius(radiusPoint);
}

void Point::setPosition(float x, float y) {
    p.setPosition(x, y);
}

void Point::setColor(sf::Color color) {
    p.setFillColor(color);
}

void Point::setVisible(bool condition) {
    visible = condition;
}

sf::Color Point::getColor() {
    return p.getFillColor();
}
