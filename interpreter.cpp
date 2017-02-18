#include "interpreter.hpp"

using namespace std;

interpreter::interpreter() {
	//create a tree
	//create an enviornment
	cout << "Calling the interpreter constructor" << endl;
}

void interpreter::tokenize(std::istream & expression) {


	vector<string> vector_of_strings;
	string token = "";
	cout << "what is in the vector? : " << endl;
	string str;
	cout << "Calling the tokenize() function" << endl;
	cout << "Tokenizing strings here..." << endl;
	if (!expression.good()) {
		cout << "ERROR: FIle coult not be opened" << endl;
	}
	else {
		cout << "File opened successfully" << endl;
	}
	while (expression >> str) {
		vector_of_strings.push_back(str);
	}

	for (auto & vector_of_strings : vector_of_strings) {
		cout << vector_of_strings << endl;
	}




}

bool interpreter::parse() {

	cout << "Calling the parse() function" << endl;
	return true;

}


//should return an expression
int interpreter::eval() {

	return 0;
}