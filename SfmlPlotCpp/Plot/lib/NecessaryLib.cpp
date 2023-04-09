#include "../include/NecessaryLib.hpp"

double determineCoordInAxes(double number, double minInterval, double maxInterval, double length, bool xORy){

    double percentage = (double)(double(number - minInterval) / double(maxInterval - minInterval));

    if (xORy) //x
        return percentage * length;
    else     //y
        return (1 - percentage) * length;


}