#include "interpreter.hpp"
#include "tokenize.hpp"
#include "environment.hpp"
#include "expression.hpp"
#include <stack>
#include <algorithm>

using namespace std;

interpreter::interpreter() {
	root = new Node;
	Environment environment;
}

interpreter::~interpreter() {
	root = NULL;
	delete root;
}

bool interpreter::parse(std::istream & expression) noexcept
{
	stack<string> parentheses_checker;
	int parentheses_counter_open = 0;
	int parentheses_checker_closed = 0;

	string output = "";
	string read_from_expression = "";
	while (getline(expression, output)) {
		read_from_expression.insert(0, output);
	}
	getline(expression, read_from_expression);
	cout << "READ FROM FILE: " << read_from_expression << endl;
	cout << endl;
	Tokenize token;	//tokenize returns a vector

	vector<string> vector_of_strings = token.tokenize(read_from_expression);

	for (int vector_index = 0; vector_index < vector_of_strings.size(); vector_index++) {
		if (vector_of_strings.front() != "\"(\"," || vector_of_strings.back() != "\")\"") {
			cout << "ERROR: OUTER PARENTHESIS DO NOT MATCH" << endl;
			return false;
		}
		if (vector_of_strings[vector_index] == "\"(\",") {
			parentheses_checker.push(vector_of_strings[vector_index]);
			parentheses_counter_open++;
		}
		if (vector_of_strings[vector_index] == "\")\"," ||
					vector_of_strings[vector_index] == "\")\"") {
			parentheses_checker.push(vector_of_strings[vector_index]);
			parentheses_checker_closed++;
		}
		if ((vector_of_strings[vector_index] == "\"(\"," && 
				vector_of_strings[vector_index+1] == "\")\"") || 
				(vector_of_strings[vector_index] == "\"(\"," && 
				vector_of_strings[vector_index+1] == "\")\",")) {

			cout << "ERROR: WRONG" << endl;
			return false;

		}
	}

	if (parentheses_counter_open != parentheses_checker_closed) {
		cout << "ERROR: PARENTHESES DONT MATCH NOT VALID" << endl;
		return false;
	}
	if (parentheses_checker_closed == 0 || parentheses_counter_open == 0) {
		cout << "ERROR: NO PARENTHESES REQUIRED" << endl;
		return false;
	}
	cout << "SUCCESS: PARSED CORRECTLY" << endl;
	cout << "opening parentheses: " << parentheses_counter_open << endl;
	cout << "closing parentheses: " << parentheses_checker_closed << endl;
	cout << endl;
	cout << endl;

	return true;
}

Expression interpreter::eval() {

	Expression expression_evaluate;
	return expression_evaluate;

}


bool interpreter::logical_not(Expression x) {
	if (x.Express.Data.boolean_value == false) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::logical_and(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value && y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::logical_or(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value || y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::equals(Expression x, Expression y) {
	if (x.Express.Data.boolean_value == y.Express.Data.boolean_value) {
		return true;
	} else if (x.Express.Data.number_value == y.Express.Data.number_value) {
		return true;
	} else if (x.Express.Data.string_value == y.Express.Data.string_value) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::greater_than(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value > y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::greater_than_or_equal(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value >= y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::less_than_or_equal(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value <= y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::less_than(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value < y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

double interpreter::subtract_expression(Expression x, Expression y) {
	double result = x.Express.Data.number_value - y.Express.Data.number_value;
	return result;
}

double interpreter::negation(Expression x) {
	double result = (x.Express.Data.number_value * (-1));
	return result;
}

double interpreter::division(Expression x, Expression y) {
	double result = x.Express.Data.number_value / y.Express.Data.number_value;
	return result;
}

double interpreter::addition(Expression x, Expression y) {
	double result = x.Express.Data.number_value + y.Express.Data.number_value;
	return result;
}

double interpreter::multiplication(Expression x, Expression y) {
	double result = x.Express.Data.number_value * y.Express.Data.number_value;
	return result;
}



