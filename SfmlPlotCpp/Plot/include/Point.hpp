#pragma once

#include "NecessaryLib.hpp"

class Point: public sf::Drawable, public sf::Transformable{
    private:
        double radiusPoint = 2;
        bool visible = true;
        sf::CircleShape p;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{ 
            if(visible) 
                target.draw(p);
        }
    public:
        Point(float, float);
        Point(double, float, float);
        Point(double, float, float, sf::Color);
        void setRadius(double);
        void setPosition(float, float);
        void setColor(sf::Color);
        void setVisible(bool);
        sf::Color getColor();
};

