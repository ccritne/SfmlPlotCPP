#include "../include/Bar.hpp"

Bar::Bar(float xStart, float yStart, float xEnd, float yEnd, std::string label, sf::Font& font, bool _textVisible, int textSize) {
    if (!font.loadFromFile("arial.ttf")) std::cout << "Error while loading the font." << std::endl;

    textVisible = _textVisible;

    labelBar.setFont(font);
    labelBar.setCharacterSize(textSize);
    labelBar.setString(label);

    double widthText = labelBar.getLocalBounds().width;
    double heightText = labelBar.getLocalBounds().height;

    if (xStart == xEnd)
        labelBar.setPosition(xStart - widthText / 2, yEnd);
    else
        labelBar.setPosition(xStart - (widthText + 1), yEnd - heightText);

    line.setPosition(xStart, yStart, xEnd, yEnd);

};