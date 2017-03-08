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

	bool is_present_in_map(string symbol);
	double value_at_element_in_map(string symbol);
	void update_map_with_value(string symbol, double new_value);
	void add_element_to_map(string symbol, double value);
	double PI;

private:
	typedef unordered_map<string, double> UnorderedMap;
	UnorderedMap default_map;

	//this is where I will put my variables from eval
	//this will map symbol to symbol
	// typedef unordered_map<string, string> UnorderedMapDynamic;
	// UnorderedMapDynamic tree_map;



};


#endif