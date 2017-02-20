#include "interpreter.hpp"
#include "tokenize.hpp"
// #include "environment.hpp"
// #include "expression.hpp"

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



