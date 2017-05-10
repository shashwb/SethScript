#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#define USE_MATH_DEFINES

#include <unordered_map>
#include <string>
#include <cmath>
#include "expression.hpp"

using namespace std;

class Environment {
public:
    Environment();
    ~Environment();
    void clearMap();
    void print_map();
    bool is_present_in_map(string symbol);
    double value_at_element_in_map(string symbol);
    void update_map_with_value(string symbol, Expression *new_value);
    void add_element_to_map(string symbol, Expression *value);
//    double sin(double num);
//    double cos(double num);
//    double arctan(double num_one, double num_two);

private:
    unordered_map<string, Expression *> default_map;
};

#endif
