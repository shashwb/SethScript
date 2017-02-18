#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "interpreter.hpp"

using namespace std;

int main(int argc, char* argv[]) {


	cout << "We are in the main function" << endl;

	//creates a tree
	//creates a default environment
	interpreter inter;

	//read in data and parse it into "tokens"
	//put the tokens into a list, or something


	ifstream expression("example.txt");

	inter.tokenize(expression);

	//go through the tree and populate it with the tokens
	//returns true or false if it is possible to parse
	inter.parse();

	//go through and evaulaute the tree, cross referencing the enironment
	inter.eval();

	return 0;

}