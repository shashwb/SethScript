#include "tokenize.hpp"

using namespace std;

//REDO TOKENIZE TO WORK THE WAY I WANT IT TO

vector<string> Tokenize::tokenize(string expression) {

	cout << "tokenize() is called" << endl;

	vector<string> vector_of_strings;
	string str = expression;


	cout << "String passed into Tokenize(): " << str << endl;
	cout << endl;


	string str_parentheses;
	string str_special = "";
	string str_back;
	string str_normal;

	int str_index = 0;
	int j = 0;

	while (str_index < str.length()) {

		if (str[str_index] == ' ') {
			//iterate forward and ignore
			str_index = str_index + 1;
		}
		else if (str_index == str.length() - 1) {	//reached end of string

			string result = "";
			string first = "\"";
			string last = "\"";
			string string_holder(1, str[str_index]);
			first.insert(1, string_holder);
			first.insert(2, last);
			vector_of_strings.push_back(first);
			str_index++;

		}
		else if (str[str_index] == '(' || str[str_index] == ')') {
			string first = "\"";
			string last = "\",";
			string string_holder(1, str[str_index]);
			first.insert(1, string_holder);
			first.insert(2, last);
			vector_of_strings.push_back(first);
			str_index++;
		}
		else if (str[str_index] != ' ' && str[str_index + 1] != ' ') {
			string first = "\"";
			string last = "\",";
			string string_holder;
			int iterate_counter = 0;
			for (j = str_index; str[j] != ' ' && str[j] != ')'; j++) {
				string_holder.append(1, str[j]);
			}
			first.insert(1, string_holder);
			iterate_counter = 1 + string_holder.length();
			first.insert(iterate_counter, last);
			vector_of_strings.push_back(first);

			str_index = j;
		}
		else {
			string first = "\"";
			string last = "\",";
			string string_holder(1, str[str_index]);
			first.insert(1, string_holder);
			first.insert(2, last);
			vector_of_strings.push_back(first);
			str_index++;
		}
	}


	// str.replace(str.begin(), str.end(), "(", "\"(\",");
	// str.replace(str.begin(), str.end(), ")", "\")\",");
	// istringstream iss(str);
	// vector_of_strings.insert(vector_of_strings.end(), istream_iterator<string>(iss), istream_iterator<string>());

	// for (int i = 0; i < vector_of_strings.size(); ++i) {
	// 	cout << "vector_of_strings[" << i << "] : " << vector_of_strings[i] << endl;
	// }

	// cout << "VECTOR CONTENTS: " << endl;
	// stringstream ss(str);
	// string vector_contents;
	// // while (getline(ss, vector_contents)) {
	// for (int i = 0; i < str.length(); i++) {
	// 	ss >> vector_contents;
	// 	string opening_paren = "(";
	// 	string closing_paren = ")";
	// 	if (strcmp(vector_contents.c_str(), opening_paren.c_str()) != 0) {
	// 		//split the parentheses
	// 		cout << "IN THE STRCMP() FUNCTION CONDITIONAL" << endl;
	// 		// string paren = vector_contents.c_str();
	// 		// string paren_1 = paren.substr(0, 1);
	// 		// vector_of_strings.push_back(paren_1);
	// 		// vector_of_strings.push_back(vector_contents.substr(vector_contents[1]));
	// 	}
	// 	if (strcmp(vector_contents.c_str(), closing_paren.c_str())) {
	// 		// string paren = vector_contents.c_str();
	// 		// string paren_1 = paren.substr(paren.length() - 1);
	// 		// vector_of_strings.push_back(vector_contents.substr(vector_contents[0], vector_contents[paren.length() - 1]));
	// 		// vector_of_strings.push_back(paren_1);
	// 	}
	// 	cout << vector_contents << endl;
	// }


	cout << endl;
	cout << "VECTOR CONTENTS: " << endl;


	return vector_of_strings;

}



