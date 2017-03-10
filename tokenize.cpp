#include "tokenize.hpp"

using namespace std;


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
		else if (str_index == str.length() - 1) {
			string result = "";
			string beginning_quote = "\"";
			string ending_quote = "\"";
			string string_holder(1, str[str_index]);

			result.append(beginning_quote);
			result.append(string_holder);
			result.append(ending_quote);
			vector_of_strings.push_back(result);
			str_index++;


		}
		else if (str[str_index] == '(' || str[str_index] == ')') {
			string first_quote = "\"";
			string last_quote = "\",";
			string string_holder(1, str[str_index]);
			string result = "";

			result.append(first_quote);
			result.append(string_holder);
			result.append(last_quote);

			vector_of_strings.push_back(result);
			str_index++;
		}

		else if (str[str_index] != ' ' && str[str_index + 1] != ' ') {
			string base = "\"";
			string ending_quote = "\",";
			string string_holder;

			int iterate_counter = 0;
			for (j = str_index; str[j] != ' ' && str[j] != ')'; j++) {
				string_holder.append(1, str[j]);
			}
			
			base.insert(1, string_holder);
			iterate_counter = 1 + string_holder.length();
			base.insert(iterate_counter, ending_quote);
			vector_of_strings.push_back(base);

			str_index = j;
		}

		else {
			string beginning_quote = "\"";
			string ending_quote = "\",";
			string string_holder(1, str[str_index]);

			string result = "";
			result.append(beginning_quote);
			result.append(string_holder);
			result.append(ending_quote);

			vector_of_strings.push_back(result);
			str_index++;
		}
	}

	cout << endl;
	cout << "VECTOR CONTENTS: " << endl;


	return vector_of_strings;

}
