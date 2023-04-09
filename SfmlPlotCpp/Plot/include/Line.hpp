#pragma once

#include "NecessaryLib.hpp"

class Line: public sf::Drawable, public sf::Transformable
{
    private:
        sf::Vertex line[2];
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{ 
            target.draw(line, 2, sf::Lines);
        }
    public:
        Line();
        Line(float, float, float, float);
        void setPosition(float, float, float, float);
        void setLineColor(sf::Color);
};
