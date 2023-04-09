#pragma once

#include "NecessaryLib.hpp"
#include "Line.hpp"

class Bar: public sf::Drawable, public sf::Transformable
{
    private:
        Line line;
        sf::Text labelBar;
        
        bool textVisible = true;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const { 
            target.draw(line);
            if(textVisible) 
                target.draw(labelBar);
        }

    public:
        Bar(float, float, float, float, std::string, sf::Font&, bool, int);
        Bar() {};
};