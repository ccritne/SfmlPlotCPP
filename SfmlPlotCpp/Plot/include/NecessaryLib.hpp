#pragma once

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <sstream>
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

double determineCoordInAxes(double, double, double, double, bool);

std::string to_string_with_precision(double, const int);