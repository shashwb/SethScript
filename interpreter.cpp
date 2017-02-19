#include "interpreter.hpp"

using namespace std;

interpreter::interpreter() {
	//create a tree
	//create an enviornment
}

void interpreter::tokenize(string expression) {

	vector<string> vector_of_strings;
	string holder;
	string token = "";
	string str = expression;
	cout << "Original String: " << str << endl;
	cout << endl;


	string str_parentheses;
	string str_special = "";
	string str_back;
	string str_normal;

	int str_index = 0;
	int j_index = 0;

	while (str_index < str.length()) {
		//BEGIN
		if (str[str_index] == 'b' && str[str_index+1] == 'e' &&
		 str[str_index+2] == 'g' && str[str_index+3] == 'i' 
		 && str[str_index+4] == 'n') {

			// cout << "\"" << str[str_index - 1] << "\"," << endl;
			str_special = "\"begin\",";
			cout << str_special << endl;
			str_index = str_index + 5;
		}

		//DEFINE
		else if (str[str_index] == 'd' && str[str_index+1] == 'e' &&
		 str[str_index+2] == 'f' && str[str_index+3] == 'i' && 
		 str[str_index+4] == 'n' && str[str_index+5] == 'e') {

			// cout << "\"" << str[str_index - 1] << "\"," << endl;
			str_special = "\"define,\"";
			cout << str_special << endl;
			str_index = str_index + 6;
		}

		//IF
		else if (str[str_index] == 'i' && str[str_index+1] == 'f') {

			// cout << "\"" << str[str_index - 1] << "\"," << endl;
			str_special = "\"if\",";
			cout << str_special << endl;
			str_index = str_index + 2;
		}
		else if (str[str_index] == ' ') {
			str_index++;	//SKIP
		}
		else if (str_index == str.length() - 1) {
			string prepend = "\"";
			string append = "\"";
			string together(1, str[str_index]);
			prepend.insert(1, together);
			prepend.insert(2, append);
			cout << prepend;
		}
		else {
			//for everything else 
			string prepend = "\"";
			string append = "\",";
			string together(1, str[str_index]);
			prepend.insert(1, together);
			prepend.insert(2, append);
			cout << prepend;
		}

		str_index++;
	}


}

bool interpreter::parse(std::istream & expression) {

	cout << endl;
	cout << "Calling the parse() function" << endl;
	cout << endl;

	string read_from_expression = "";
	getline(expression, read_from_expression);
	cout << "read_from_description: " << read_from_expression << endl;;

	// tokenize("hello world");
	return true;

}


//should return an expression
int interpreter::eval() {

	return 0;
}