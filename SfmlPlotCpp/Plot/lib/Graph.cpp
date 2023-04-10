#include "../include/Graph.hpp"

Graph::Graph(double xStart, double yStart, double xEnd, double yEnd, double _padding, double _margin, sf::Font& _font) {

    widthGraph = xEnd - xStart;
    heightGraph = yEnd - yStart;

    padding = _padding;
    margin = _margin;

    graphX = xStart + padding * widthGraph;
    graphY = yStart + padding * heightGraph;

    lengthX = widthGraph - 2 * widthGraph * padding;
    lengthY = heightGraph - 2 * heightGraph * padding;

    lengthWMX = widthGraph * (1 - 2 * (padding + margin));
    lengthWMY = heightGraph * (1 - 2 * (padding + margin));

    AxesX.setPosition(graphX, graphY + lengthY, graphX + lengthX, graphY + lengthY);

    AxesY.setPosition(graphX, graphY, graphX, graphY + lengthY);

    maxIntervalX = 1;
    minIntervalX = 1;

    maxIntervalY = 1;
    minIntervalY = 1;

}

void Graph::plot(std::string function, double minRange, double maxRange, int numberPoints, sf::Color color = sf::Color::White) {

    double step = double(maxRange - minRange) / numberPoints;

    double index = minRange;

    for (int i = 0; i <= numberPoints; i++) {
        double y = evaluate(change(function, index));
        if (!isinf(y)) {
            coords.push_back({ index, y });
            minIntervalY = std::min(y, minIntervalY);
            maxIntervalY = std::max(y, maxIntervalY);
        }
        index += step;
    }


    for (int i = 0; i < coords.size(); i++) {
        double x = graphX + margin * lengthX + determineCoordInAxes(coords[i].x, minIntervalX, maxIntervalX, lengthWMX, true);
        double y = graphY + margin * lengthY + determineCoordInAxes(coords[i].y, minIntervalY, maxIntervalY, lengthWMY, false);
        Point p(radiusPoint, x - radiusPoint, y - radiusPoint);
        points.push_back(p);
    }

    int counter = std::min(15, numberPoints);

    double segmentToAddY = double(maxIntervalY - minIntervalY) / counter;
    double labelY = minIntervalY;

    double segmentToAddX = double(maxIntervalX - minIntervalX) / counter;
    double labelX = minIntervalX;

    double coordx = graphX + margin * lengthX;
    double coordy = graphY + margin * lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);

    double segmentX = double(lengthWMX / counter);

    while (counter--) {
        Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, std::to_string(labelX), font, true, textSize);
        bars.push_back(tmpX);
        coordy = graphY + margin * lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
        Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, std::to_string(labelY), font, true, textSize);
        bars.push_back(tmpY);

        labelY += segmentToAddY;
        labelX += segmentToAddX;

        coordx += segmentX;
    }

    Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, std::to_string(labelX), font, true, textSize);
    bars.push_back(tmpX);
    coordy = graphY + margin * lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
    Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, std::to_string(labelY), font, true, textSize);
    bars.push_back(tmpY);

}

void Graph::setPoints(std::vector<point> pointsCoordinates, sf::Color color = sf::Color::White) {
    bars.clear();
    int lastSize = coords.size();

    minIntervalY = std::min(minIntervalY, pointsCoordinates[0].y);
    maxIntervalY = std::max(maxIntervalY, pointsCoordinates[0].y);

    for (int i = 0; i < pointsCoordinates.size(); i++) {
        minIntervalY = std::min(pointsCoordinates[i].y, minIntervalY);
        maxIntervalY = std::max(pointsCoordinates[i].y, maxIntervalY);
        for (int j = i + 1; j < pointsCoordinates.size(); j++)
            if (pointsCoordinates[i].x > pointsCoordinates[j].x)
                std::swap(pointsCoordinates[i], pointsCoordinates[j]);
    }

    minIntervalX = std::min(minIntervalX, pointsCoordinates[0].x);
    maxIntervalX = std::max(maxIntervalX, pointsCoordinates[pointsCoordinates.size() - 1].x);


    points.clear();

    for (int i = 0; i < coords.size(); i++) {
        double x = graphX + margin * lengthX + determineCoordInAxes(coords[i].x, minIntervalX, maxIntervalX, lengthWMX, true);
        double y = graphY + margin * lengthY + determineCoordInAxes(coords[i].y, minIntervalY, maxIntervalY, lengthWMY, false);
        Point p(radiusPoint, x - radiusPoint, y - radiusPoint);
        p.setColor(color);
        points[i] = p;
    }

    for (int i = 0; i < pointsCoordinates.size(); i++) {
        double valX = pointsCoordinates[i].x;
        double valY = pointsCoordinates[i].y;

        double x = graphX + margin * lengthX + determineCoordInAxes(valX, minIntervalX, maxIntervalX, lengthWMX, true);
        double y = graphY + margin * lengthY + determineCoordInAxes(valY, minIntervalY, maxIntervalY, lengthWMY, false);

        Point p(radiusPoint, x - radiusPoint, y - radiusPoint);
        p.setColor(color);

        points.push_back(p);
    }

    int counter = 10;

    double segmentToAddY = double((maxIntervalY - minIntervalY) / counter);
    double labelY = minIntervalY;

    double segmentToAddX = double((maxIntervalX - minIntervalX) / counter);
    double labelX = minIntervalX;

    double coordx = graphX + margin * lengthX;
    double coordy = graphY + margin * lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);

    double segmentX = double(lengthX / counter);

    while (counter--) {
        Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, std::to_string(labelX), font, true, textSize);
        bars.push_back(tmpX);
        coordy = graphY + margin * lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
        Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, std::to_string(labelY), font, true, textSize);
        bars.push_back(tmpY);

        labelY += segmentToAddY;
        labelX += segmentToAddX;

        coordx += segmentX;
    }

    if (margin == 0) {
        Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, std::to_string(labelX), font, true, textSize);
        bars.push_back(tmpX);
        coordy = graphY + margin * lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
        Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, std::to_string(labelY), font, true, textSize);
        bars.push_back(tmpY);
    }

}

void Graph::addPoint(coord p, sf::Color color = sf::Color::White) {

    bars.clear();
    points.clear();

    coords.push_back(p);

    minIntervalY = coords[0].y;
    maxIntervalY = coords[0].y;

    for (int i = 0; i < coords.size(); i++) {
        minIntervalY = std::min(coords[i].y, minIntervalY);
        maxIntervalY = std::max(coords[i].y, maxIntervalY);
        for (int j = i + 1; j < coords.size(); j++)
            if (coords[i].x > coords[j].x)
                std::swap(coords[i], coords[j]);
    }

    minIntervalX = coords[0].x;
    maxIntervalX = coords[coords.size() - 1].x;

    for (int i = 0; i < coords.size(); i++) {
        double valX = coords[i].x;
        double valY = coords[i].y;

        double x = graphX + margin * lengthX + determineCoordInAxes(valX, minIntervalX, maxIntervalX, lengthWMX, true);
        double y = graphY + margin * lengthY + determineCoordInAxes(valY, minIntervalY, maxIntervalY, lengthWMY, false);

        Point p(radiusPoint, x - radiusPoint, y - radiusPoint);
        p.setColor(color);

        points.push_back(p);
    }

    int counter = 10;

    double segmentToAddY = double((maxIntervalY - minIntervalY) / counter);
    double labelY = minIntervalY;

    double segmentToAddX = double((maxIntervalX - minIntervalX) / counter);
    double labelX = minIntervalX;

    double coordx = graphX + margin * lengthX;
    double coordy = graphY + margin * lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);

    double segmentX = double(lengthX / counter);

    int i = 0;
    while (counter--) {
        Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, std::to_string(labelX), font, true, textSize);
        bars.push_back(tmpX);
        coordy = graphY + margin * lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
        Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, std::to_string(labelY), font, true, textSize);
        bars.push_back(tmpY);

        labelY += segmentToAddY;
        labelX += segmentToAddX;

        coordx += segmentX;
    }

    if (margin == 0) {
        Bar tmpX(coordx, graphY + lengthY - 5, coordx, graphY + lengthY + 5, std::to_string(labelX), font, true, textSize);
        bars.push_back(tmpX);
        coordy = graphY + margin * lengthY + determineCoordInAxes(labelY, minIntervalY, maxIntervalY, lengthWMY, false);
        Bar tmpY(graphX - 5, coordy, graphX + 5, coordy, std::to_string(labelY), font, true, textSize);
        bars.push_back(tmpY);
    }

}

void Graph::setRadiusPoint(double radius) {
    radiusPoint = radius;
}

void Graph::setFunction(std::string function, double a, double b, int numberPoints) {
    minIntervalX = a;
    maxIntervalX = b;
    minIntervalY = 0;
    maxIntervalY = 0;
    coords.clear();
    bars.clear();
    points.clear();
    this->plot(function, a, b, numberPoints);
}