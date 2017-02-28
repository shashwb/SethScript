#include "tokenize.hpp"

using namespace std;


vector<string> Tokenize::tokenize(string expression) {

	vector<string> vector_of_strings;
	string str = expression;
	cout << "Original String: " << str << endl;
	cout << endl;


	string str_parentheses;
	string str_special = "";
	string str_back;
	string str_normal;

	int str_index = 0;

	while (str_index < str.length()) {
		//BEGIN
		if (str[str_index] == 'b' && str[str_index+1] == 'e' &&
		 str[str_index+2] == 'g' && str[str_index+3] == 'i' 
		 && str[str_index+4] == 'n') {

			// cout << "\"" << str[str_index - 1] << "\"," << endl;
			str_special = "\"begin\",";
			cout << str_special << endl;
			vector_of_strings.push_back(str_special);
			str_index = str_index + 5;
		}

		//DEFINE
		else if (str[str_index] == 'd' && str[str_index+1] == 'e' &&
		 str[str_index+2] == 'f' && str[str_index+3] == 'i' && 
		 str[str_index+4] == 'n' && str[str_index+5] == 'e') {

			// cout << "\"" << str[str_index - 1] << "\"," << endl;
			str_special = "\"define,\"";
			cout << str_special << endl;
			vector_of_strings.push_back(str_special);
			str_index = str_index + 6;
		}

		//IF
		else if (str[str_index] == 'i' && str[str_index+1] == 'f') {

			// cout << "\"" << str[str_index - 1] << "\"," << endl;
			str_special = "\"if\",";
			cout << str_special << endl;
			vector_of_strings.push_back(str_special);
			str_index = str_index + 2;
		}
		else if (str_index == str.length() - 1) {
			string prepend = "\"";
			string append = "\"";
			string together(1, str[str_index]);
			prepend.insert(1, together);
			prepend.insert(2, append);
			cout << prepend << endl;
			vector_of_strings.push_back(prepend);
			str_index++;
		}
		else if (str[str_index] == ' ') {
		}
		else {
			//for everything else 
			string prepend = "\"";
			string append = "\",";
			string together(1, str[str_index]);
			prepend.insert(1, together);
			prepend.insert(2, append);
			cout << prepend << endl;
			vector_of_strings.push_back(prepend);
		}

		str_index++;
	}

	cout << endl;
	cout << "VECTOR CONTENTS: " << endl;


	return vector_of_strings;

}