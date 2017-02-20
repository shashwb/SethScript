#include "interpreter.hpp"
#include "tokenize.hpp"
#include "environment.hpp"
#include "expression.hpp"

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
	string output = "";
	string read_from_expression = "";
	while (getline(expression, output)) {
		read_from_expression.insert(0, output);
	}
	getline(expression, read_from_expression);
	cout << "READ FROM FILE: " << read_from_expression << endl;
	cout << endl;
	Tokenize token;
	token.tokenize(read_from_expression);
	return true;
}

Expression interpreter::eval() {
	Expression e;
	return e;
}


bool interpreter::logical_not(Expression x) {
	if (x.data.boolean_value == false) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::logical_and(Expression x, Expression y) {
	if ((x.data.boolean_value && y.data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::logical_or(Expression x, Expression y) {
	if ((x.data.boolean_value || y.data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}
bool interpreter::equals(Expression x, Expression y) {
	if (x.data.boolean_value == y.data.boolean_value) {
		return true;
	} else {
		return false;
	}
}
bool interpreter::greater_than(Expression x, Expression y) {
	if ((x.data.boolean_value > y.data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}
bool interpreter::greater_than_or_equal(Expression x, Expression y) {
	if ((x.data.boolean_value >= y.data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}
bool interpreter::less_than_or_equal(Expression x, Expression y) {
	if ((x.data.boolean_value <= y.data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}
bool interpreter::less_than(Expression x, Expression y) {
	if ((x.data.boolean_value < y.data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

double interpreter::subtract_expression(Expression x, Expression y) {
	double result = x.data.number_value - y.data.number_value;
	return result;
}

double interpreter::negation(Expression x) {
	double result = (x.data.number_value * (-1));
	return result;
}

double interpreter::division(Expression x, Expression y) {
	double result = x.data.number_value / y.data.number_value;
	return result;
}

double interpreter::addition(Expression x, Expression y) {
	double result = x.data.number_value + y.data.number_value;
	return result;
}

double interpreter::multiplication(Expression x, Expression y) {
	double result = x.data.number_value * y.data.number_value;
	return result;
}



