#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "interpreter.hpp"
#include "environment.hpp"

using namespace std;



int main(int argc, char* argv[]) {

	// cout << endl;
	// cout << endl;
	// cout << "////////////////////////" << endl;
	// cout << "PROGRAM BEGIN" << endl;
	// cout << "////////////////////////" << endl;
	// cout << endl;
	Interpreter inter;
	ifstream expression;

	if (argc <=	1) {
		while (argc) {
			string arguments_from_command_line;
			cout << "vtscript> ";
			while (!(getline(cin, arguments_from_command_line))) {}	//wait for input
			istringstream stream(arguments_from_command_line);
			inter.parse(stream);
			try {
				inter.eval();
			}
			catch(exception& e) {
				cout << e.what() << endl;
			}
		}
	}
	else {
		string argument_string(argv[1]);
		if (argv[1] && !argv[2]) {
			// cout << "READ IN FROM A FILE" << endl;
			expression.open(argv[1]);
			inter.parse(expression);
		}
		else if (argument_string == "-e"){
			// cout << "READ IN FROM COMMAND LINE" << endl;
			// cout << endl;
			// cout << "we're in the -e with the arg: " << argv[2] << endl;
			istringstream stream(argv[2]);
			inter.parse(stream);
		}
		else {
			// cout << "ERROR: NOT VALID INPUT" << endl;
			return EXIT_FAILURE;
		}
	}

	// cout << endl;
	// cout << "does it get to the pre-eval() function?" << endl;
	// cout << endl;

	try {
		inter.eval();
	}
	catch(exception& e) {
		cout << e.what() << endl;
	}
	return EXIT_SUCCESS;

//	return 0;

}
