#ifndef ENVIRONMENT_H					// avoid repeated expansion
#define ENVIRONMENT_H
#define USE_MATH_DEFINES

#include <unordered_map>
#include "expression.hpp"
#include <string>
#include <cmath>

using namespace std;

class Environment {
public: 
	Environment();
	~Environment();

	bool isInMap(string symbol);
	double value_at_element(string symbol);
	void update_map(string symbol, double new_value);
	void add_element_to_map(string symbol, double value);
	double PI;

private:
	typedef unordered_map<string, double> UnorderedMap;
	UnorderedMap default_map;


};


#endif