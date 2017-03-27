#include "environment.hpp"

#include "math.h"

using namespace std;


typedef unordered_map<string, double> map;
// map default_map;

Environment::Environment() {
	// double PI = atan2(0, 1);
	double PI = atan2(0, -1);
	this->add_element_to_map("pi", PI);
	// cout << "an Environment is created with a default " << default_map["pi"] << endl;
}

Environment::~Environment() {

}


void Environment::clearMap() {
	default_map.clear();
}

void Environment::print_map() {
	// cout << "MAP CONTAINS: " << endl;
	for (auto& x: default_map) std::cout << " " << x.first << " : " << x.second;
	cout << endl;
}





bool Environment::is_present_in_map(string symbol) {

	std::unordered_map<string, double>::const_iterator got_default = default_map.find(symbol);

	if (got_default == default_map.end()) {
		cout << "not found in DEFAULT_MAP" << endl;
		return false;
	} else {
		cout << got_default->first << " is " << got_default->second;
		return true;
	}

}

double Environment::value_at_element_in_map(string symbol) {
	std::unordered_map<string, double>::const_iterator got = default_map.find(symbol);
	if (got == default_map.end()) {
		// cout << "ERROR NOT IN MAP" << endl;
	}
		// cout << "The value at elment: " << got->first << " is " << got->second << endl;
		return got->second;
}


void Environment::update_map_with_value(string symbol, double new_value) {
	auto it = default_map.find(symbol);
	if (it != default_map.end()) {
		it->second = new_value;
	}

}

void Environment::add_element_to_map(string symbol, double value) {
	pair<string,double> add_this(symbol, value);
	default_map.insert(add_this);
}
