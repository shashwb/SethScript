#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "interpreter.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	interpreter inter;

	ifstream expression;

	if (strcmp(argv[1], "-e") && argv[2]) {
		cout << "READ IN FROM THE CONSOLE" << endl;
		inter.parse(expression);
	}
	else if (argv[1] && !argv[2]) {
		expression.open(argv[1]);
	}
	else if (!argv[1]) {
		cout << endl;
		cout << "ERROR: Please set a filename in the directory or type in a valid expression" << endl;
	}
	else {
		cout << "ERROR: Please try again..." << endl;
	}

	inter.parse(expression);

	//go through and evaulaute the tree, cross referencing the environment
	inter.eval();

	return 0;

}