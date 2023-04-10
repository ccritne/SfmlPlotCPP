#pragma once

#include "NecessaryLib.hpp"
#include "Line.hpp"
#include "Bar.hpp"
#include "Point.hpp"
#include "Evaluate.hpp"

class Graph: public sf::Drawable, public sf::Transformable
{
    private:
        double widthGraph, heightGraph;
        double graphX, graphY;

        Line AxesX;
        Line AxesY;

        double maxIntervalX, minIntervalX;
        double maxIntervalY, minIntervalY;

        sf::Font font;

        std::vector<Bar> bars;

        std::vector<Point> points;

        double padding;
        double margin;

        double lengthX, lengthWMX;
        double lengthY, lengthWMY;

        int textSize = 15;

        double radiusPoint = 1;

        std::vector<coord> coords;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{ 

            target.draw(AxesX);
            target.draw(AxesY);

            for(int i = 0; i < bars.size(); i++)
                target.draw(bars[i]);

            for(int i = 0; i < points.size(); i++)
                target.draw(points[i]);    
        
        }
    public:
        Graph(double, double, double, double, double, double, sf::Font&);
        void plot(std::string, double, double, int, sf::Color);
        void setPoints(std::vector<point>, sf::Color);
        void addPoint(coord, sf::Color);
        void setRadiusPoint(double radius);
        void setFunction(std::string, double, double, int);

};