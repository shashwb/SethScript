#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "interpreter.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	interpreter inter;

	ifstream expression;

	//IF THERE IS LESS THAN ONE ARGUMENT (ONLY RUNNING SCRIPT)
	if (argc <=	 1) {

		while (argc) {
			string arguments_from_command_line;
			cout << "vtscript> ";
			while (!(getline(cin, arguments_from_command_line))) {}	//wait for input
			istringstream stream(arguments_from_command_line);
			inter.parse(stream);
		}
	}
	else if (argv[1]) {
		bool is_this_shit_true = strcmp(argv[1], "-e");
		if (is_this_shit_true) {
			cout << "in the -e function" << endl;
		}
		// cout << "in the -e function" << endl;

		// inter.parse(expression);
	}

	else if (argv[1] && !argv[2]) {
		// ifstream expression;
		expression.open(argv[1]);
	}
	else {
		cout << "ERROR: Please try again..." << endl;
	}


	inter.parse(expression);

	//go through and evaulaute the tree, cross referencing the environment
	inter.eval();

	return 0;

}