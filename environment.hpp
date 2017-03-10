#ifndef ENVIRONMENT_H					
#define ENVIRONMENT_H
#define USE_MATH_DEFINES

#include <unordered_map>
#include <string>
#include <cmath>
#include "interpreter.hpp"
#include "expression.hpp"

using namespace std;


class Environment {
public:
	Environment();
	~Environment();

	bool is_present_in_map(unordered_map<string, double> &map, string symbol);
	double value_at_element_in_map(unordered_map<string, double> &map, string symbol);
	void update_map_with_value(unordered_map<string, double> &map, string symbol, double new_value);
	void add_element_to_map(string symbol, double value);
	bool determine_operation_for_procedures(Interpreter &inter, string symbol, string other);
	double determine_operation_for_arithmetic(Interpreter &inter, string symbol, string lhs, string rhs);
	double PI;

private:


};


#endif
