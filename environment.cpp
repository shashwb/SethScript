#include "environment.hpp"

using namespace std;


typedef unordered_map<string, double> UnorderedMap;
UnorderedMap default_map;

Environment::Environment() {

	PI = M_PI;
	pair<string,double> pi_insert("pi", PI);
	default_map.insert(pi_insert);
	cout << "an Environment is created with a default " << default_map["pi"] << endl;

}

Environment::~Environment() {
	default_map.clear();

}


bool Environment::determine_operation_for_procedures(Interpreter &inter, string symbol, string other) {

	symbol.erase(symbol.begin());	//pop off "
	symbol.pop_back();
	symbol.pop_back();


	cout << "SYMBOL: " << symbol << endl;
	cout << "OTHER: " << other << endl;

	cout << "determine_operation_for_symbols CALLED()" << endl;

	Expression expression = inter.expression_factory(other);
	cout << "NOT CONDITIONAL RESULT EXPRESSION: " << expression.express.Data.boolean_value << endl;
	if (symbol == "not") {
		Expression expression = inter.expression_factory(other);
		cout << "NOT CONDITIONAL RESULT EXPRESSION: " << expression.express.Data.boolean_value << endl;
		return inter.logical_not(expression);
	}
	//fill in the rest of the procedures that have boolean values

	else {
		cout << endl;
		cout << "not going into any of the functions!!!!" << endl;
		cout << endl;
	}
	return false;
}


double Environment::determine_operation_for_arithmetic(Interpreter &inter, string symbol, string lhs, string rhs) {
	symbol.erase(symbol.begin());	//pop off "
	symbol.pop_back();
	symbol.pop_back();

	cout << "SYMBOL: " << symbol << endl;
	cout << "LHS: " << lhs << endl;
	cout << "RHS: " << rhs << endl;

	if (symbol == "+") {
		return inter.addition(lhs, rhs);
	}
	return 987.654;
}



bool Environment::is_present_in_map(unordered_map<string, double> &map, string symbol) {

	std::unordered_map<string, double>::const_iterator got_default = default_map.find(symbol);

	if (got_default == default_map.end()) {
		cout << "not found in DEFAULT_MAP" << endl;
		return false;
	} else {
		cout << got_default->first << " is " << got_default->second;
		return true;
	}

}

double Environment::value_at_element_in_map(unordered_map<string, double> &map, string symbol) {
	std::unordered_map<string, double>::const_iterator got = default_map.find(symbol);
	if (got == default_map.end()) {
		cout << "ERROR NOT IN MAP" << endl;
	}
		cout << "The value at elment: " << got->first << " is " << got->second << endl;
		return got->second;
}


void Environment::update_map_with_value(unordered_map<string, double> &map, string symbol, double new_value) {
	auto it = default_map.find(symbol);
	if (it != default_map.end()) {
		it->second = new_value;
	}


}

void Environment::add_element_to_map(string symbol, double value) {
	pair<string,double> add_this(symbol, value);
	default_map.insert(add_this);
}
