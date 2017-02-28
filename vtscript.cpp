#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "interpreter.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	interpreter inter;
	ifstream expression;


	if (argc <=	1) {
		while (argc) {
			string arguments_from_command_line;
			cout << "vtscript> ";
			while (!(getline(cin, arguments_from_command_line))) {}	//wait for input
			istringstream stream(arguments_from_command_line);
			inter.parse(stream);
		}
	}
	else {
		string argument_string(argv[1]);
		if (argv[1] && !argv[2]) {
			expression.open(argv[1]);
		}
		else if (argument_string == "-e"){
			cout << "we're in the -e with the arg: " << argv[2] << endl;
			istringstream stream(argv[2]);
			inter.parse(stream);
		}
		else {
			cout << "ERROR" << endl;
		}
	}

	Environment enviornment;
	inter.parse(expression);
	inter.eval();

	return 0;

}