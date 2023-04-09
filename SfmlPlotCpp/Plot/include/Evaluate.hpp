#pragma once
#include "NecessaryLib.hpp"

bool isF(std::string);
int prec(std::string);
bool isO(std::string op);
std::vector<std::string> infixToPostfix(std::vector<std::string>);
bool is_number(std::string);
std::vector<std::string> tokenization(std::string);
double apply(double , double, std::string);
double cbl(double, double);
double applyF(double, std::string);
double evaluate(std::string);
std::string change(std::string, double);