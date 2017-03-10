#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "interpreter.hpp"
#include "environment.hpp"

using namespace std;


int main(int argc, char* argv[]) {

	cout << endl;
	cout << endl;
	cout << "////////////////////////" << endl;
	cout << "PROGRAM BEGIN" << endl;
	cout << "////////////////////////" << endl;
	cout << endl;
	Interpreter inter;
	ifstream expression;

	// DEBUGGING CODE
	// cout << "testing is_number()" << endl;
	// string number = "1";
	// bool result_is_number = inter.is_number(number);
	// cout << "result of is_number() call on " << number << " is " << result_is_number << endl;
	//
	// cout << endl;
	// cout << "TESTING//////////////////////////////////" << endl;
	// cout << "testing determine_operation_for_symbols() function" << endl;
	// string result = "\"true\",";
	// string symbol = "\"not\",";
	// Environment environment;
	// bool result_bool;
	// result_bool = environment.determine_operation_for_procedures(inter, symbol, result);
	// cout << "result from the function outside : " << result_bool << endl;
	// cout << "TESTING//////////////////////////////////" << endl;
	// cout << endl;


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
			cout << "READ IN FROM A FILE" << endl;
			expression.open(argv[1]);
			inter.parse(expression);
		}
		else if (argument_string == "-e"){
			cout << "READ IN FROM COMMAND LINE" << endl;
			cout << endl;
			cout << "we're in the -e with the arg: " << argv[2] << endl;
			istringstream stream(argv[2]);
			inter.parse(stream);
		}
		else {
			cout << "ERROR" << endl;
			return EXIT_FAILURE;
		}
	}

	inter.eval();

	return 0;

}
