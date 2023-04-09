#pragma once

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <SFML/Graphics.hpp>

struct coord{
    double x, y;
};

struct dim{
    double w, h;
};

struct point{
    double x, y;
    bool visible;
};
double determineCoordInAxes(double number, double minInterval, double maxInterval, double length, bool xORy);