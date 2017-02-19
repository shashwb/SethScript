#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "interpreter.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	interpreter inter;

	ifstream expression;

	//if there are no arguments
	if (!argv[1]) {
		cout << endl;
		cout << "ERROR: please set a filename in the directory or type in a valid expression" << endl;
	}
	// if (strcmp(argv[2], "-e")) {
	// 	cout << "READ IN FROM THE CONSOLE" << endl;
	// 	ifstream expression;
	// }
	if (argv[1]) {
		expression.open(argv[1]);
	}

	inter.parse(expression);

	//go through and evaulaute the tree, cross referencing the environment
	inter.eval();

	return 0;

}