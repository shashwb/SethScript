#include "environment.hpp"

using namespace std;

Environment::Environment() {

	pair<string,double> pi_insert("pi", PI);
	default_map.insert(pi_insert);
	PI = M_PI;
	cout << "an Environment is created with a default " << PI << endl;

}

Environment::~Environment() {
	default_map.clear();
}

bool Environment::isInMap(string symbol) {
	
	std::unordered_map<string, double>::const_iterator got = default_map.find(symbol);
	if (got == default_map.end()) {
		cout << "not found!" << endl;
		return false;
	}
	else {
		cout << got->first << " is " << got->second;
		return true;
	}
}

double Environment::value_at_element(string symbol) {
	std::unordered_map<string, double>::const_iterator got = default_map.find(symbol);
	if (got == default_map.end()) {
		cout << "ERROR NOT IN MAP" << endl;
	}
	// else {
		cout << "The value at elment: " << got->first << " is " << got->second << endl;
		return got->second;
	// }

}

void Environment::update_map(string symbol, double new_value) {
	auto it = default_map.find(symbol);
	if (it != default_map.end()) {
		it->second = new_value;
	}
		
	
}

void Environment::add_element_to_map(string symbol, double value) {
	pair<string,double> add_this(symbol, value);
	default_map.insert(add_this);
}