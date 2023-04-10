#pragma once

#include "NecessaryLib.hpp"

class Button: public sf::Drawable, public sf::Transformable
{
    private:
        sf::RectangleShape box;
        sf::Text text;
        float h;
        float w;

        float x, y;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{    
            target.draw(box);
            target.draw(text);
        }
    public:
        Button(float, float, float, float, sf::Font&);
        void setText(std::string);
        void setSize(float, float);
        void setPosition(float, float);
        sf::Vector2f getCoord();        
        dim getDim();
        bool contains(sf::Vector2i);
};

