#include "interpreter.hpp"
#include "tokenize.hpp"

using namespace std;

interpreter::interpreter() {
	
	// Tokenize token;
	Node * root = new Node;

	//create an enviornment

}


interpreter::~interpreter() {

}

bool interpreter::parse(std::istream & expression) noexcept
{
	cout << endl;
	cout << "Calling the parse() function" << endl;
	cout << endl;
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
	// token.tokenize(read_from_expression);
	// token.tokenize(read_from_expression);
	return true;

}


//should return an expression
int interpreter::eval() {
	return 0;
}



