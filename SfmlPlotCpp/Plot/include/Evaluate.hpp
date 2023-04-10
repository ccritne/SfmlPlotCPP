#pragma once
#include "NecessaryLib.hpp"

bool isFunction(std::string);
int precedenceOperators(char);
int precedenceOperatorsAndFunctions(std::string);
bool isOperation(char op);
bool isOperation(std::string op);
std::vector<std::string> infixToPostfix(std::vector<std::string>);
bool is_number(std::string);
std::vector<std::string> tokenization(std::string);
double apply(double , double, char);
double cbl(double, double);
double applyF(double, std::string);
double evaluate(std::string);
std::string change(std::string, double);