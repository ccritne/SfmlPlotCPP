#include "../include/NecessaryLib.hpp"

double determineCoordInAxes(double number, double minInterval, double maxInterval, double length, bool xORy){

    double percentage = (double)(double(number - minInterval) / double(maxInterval - minInterval));

    if (xORy) //x
        return percentage * length;
    else     //y
        return (1 - percentage) * length;


}

std::string to_string_with_precision(double value, const int fixedPrecision = 3){
    std::ostringstream out;
    out.precision(fixedPrecision);
    out << std::fixed << value;
    return std::move(out).str();
}