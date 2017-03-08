#include "environment.hpp"

using namespace std;

typedef unordered_map<string, double> UnorderedMapDynamic;
extern UnorderedMapDynamic tree_map;

Environment::Environment() {

	PI = M_PI;
	pair<string,double> pi_insert("pi", PI);
	default_map.insert(pi_insert);
	cout << "an Environment is created with a default " << default_map["pi"] << endl;

}

Environment::~Environment() {
	default_map.clear();
	tree_map.clear();

}

bool Environment::is_present_in_map(string symbol) {
	
	std::unordered_map<string, double>::const_iterator got_default = default_map.find(symbol); 
	// unordered_map<string.c_str(), string.c_str()>::const_iterator got_tree = tree_map.find(symbol);

	//if default map
	if (got_default == default_map.end()) {
		cout << "not found in DEFAULT_MAP" << endl;
		return false;
	} else {
		cout << got_default->first << " is " << got_default->second;
		return true;
	}

	//if dynamic tree map

	for (auto it = tree_map.begin(); it != tree_map.end(); ++it) {
		if (it->first == symbol) {
			cout << endl;
			cout << "if symbol is found in tree_map" << endl;
			return true;
		} else {
			cout << "symbol not found in tree_map" << endl;
			return false;
		}
	}

	// if (got_tree == tree_map.end()) {
	// 	cout << "not found in TREE_MAP" << endl;
	// 	return false;
	// } else {
	// 	cout << got_tree->first << " is " << got_tree->second;
	// 	return true;
	// }

}

double Environment::value_at_element_in_map(string symbol) {
	std::unordered_map<string, double>::const_iterator got = default_map.find(symbol);
	if (got == default_map.end()) {
		cout << "ERROR NOT IN MAP" << endl;
	}
	// else {
		cout << "The value at elment: " << got->first << " is " << got->second << endl;
		return got->second;
	// }

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