#pragma once

#include "NecessaryLib.hpp"

class Textbox: public sf::Drawable, public sf::Transformable
{
    private:
        sf::RectangleShape box;
        sf::Text text;
        float h;
        float w;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{    
            target.draw(box);
            target.draw(text);
        }
    public:
        Textbox(float, float, float, float, sf::Font&);
        void setText(std::string);
        sf::Vector2f getCoord();
        dim getDim();
        bool contains(sf::Vector2i coord);
};