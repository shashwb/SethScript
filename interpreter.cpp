#include "interpreter.hpp"
#include "tokenize.hpp"
#include "environment.hpp"
#include "expression.hpp"
#include <stack>
#include <algorithm>
#include <regex>

using namespace std;

	//GLOBAL maps
	typedef unordered_map<string, double> UnorderedMap;
	extern UnorderedMap default_map;


Interpreter::Interpreter() {
	Environment env;	//creates default environment
}

Interpreter::~Interpreter() {
	root = NULL;
	delete root;
}

Node * Interpreter::processTokensToTree(vector<string> recursive_vector) {
	cout << endl;
	cout << "we are currently in the processTokensToTree() function" << endl;
	cout << endl;
	for(int i=0;i<recursive_vector.size();i++)
	{
		cout << i << "  --- " << recursive_vector[i] << endl;
	}
	cout << "Done printing" << endl;
	cout << "Front is " << recursive_vector[0] << endl;
	cout << "Back is " << recursive_vector.back() << endl;
	if (recursive_vector[0] == "\"(\"," && (recursive_vector.back() == "\")\""
		|| recursive_vector.back() == "\")\",")) {
		cout << "Valid data" << endl;
		cout << endl;

		//pop matching parentheses
		recursive_vector.erase(recursive_vector.begin());
		recursive_vector.pop_back();

		Node* newNode = new Node(expression_factory(recursive_vector[0])); // new node holds first value

		//DEBUGGING OUTPUT STATEMENTS
		cout << endl;
		cout << "EXPRESSION value " << newNode->data_expression.express.Data.string_value << endl;
		cout << "EXPRESSION newNode value: " << newNode->data_expression.express.Data.boolean_value << endl;
		cout << "EXPRESSION newNode type: " << newNode->data_expression.express.type << endl;
		cout << endl;

		recursive_vector.erase(recursive_vector.begin());
		cout << "Ready to loop" << endl;
		while (recursive_vector.size() > 0) {
			Node * new_child;
			if (recursive_vector[0] != "\"(\",") {
				cout << "NEW SIMPLE CHILD: ";
				cout << recursive_vector[0] << endl;
				new_child = new Node(expression_factory(recursive_vector[0]));

				//DEBUGGING OUTPUT STATEMENTS
				cout << endl;
				cout << "EXPRESSION value " << new_child->data_expression.express.Data.string_value << endl;
				cout << "EXPRESSION child_value: " << new_child->data_expression.express.Data.number_value << endl;
				cout << "EXPRESSION child_type: " << new_child->data_expression.express.type << endl;
				cout << endl;

				recursive_vector.erase(recursive_vector.begin());
			}
			else {
				cout << "NEW EXPRESSION CHILD: ";
				cout << recursive_vector[0] << endl;
				int open_parentheses_counter = 1;
				vector<string> children_of_node;
				children_of_node.push_back(recursive_vector[0]);
				recursive_vector.erase(recursive_vector.begin());
				cout << "Building " << endl;
				while (open_parentheses_counter > 0) {
					cout << "parens: " << open_parentheses_counter << ": " << recursive_vector[0] << endl;
					if (recursive_vector[0] == "\"(\",") {
						open_parentheses_counter = open_parentheses_counter + 1;
					}
					else if (recursive_vector[0] == "\")\"" || recursive_vector[0] == "\")\",") {
						open_parentheses_counter = open_parentheses_counter - 1;
					}
					children_of_node.push_back(recursive_vector[0]);
					recursive_vector.erase(recursive_vector.begin());
				}
				cout << "tokens:" << endl;
				for(int i=0;i<children_of_node.size();i++)
				{
					cout << i << ": " << children_of_node[i] << endl;
				}
				new_child = processTokensToTree(children_of_node);
			}
			cout << "Pushed back " << new_child->data << endl;
			newNode->children.push_back(new_child);	//add to children vector

		}
		cout << "RETURNING: " << newNode->data << endl;
		cout << "WITH " << newNode->children.size() << " CHILDREN" << endl;
		for (int i = 0; i < newNode->children.size(); ++i) {
			cout << "!!!children[" << i << "] : " << newNode->children[i]->data << endl;
		}
		return newNode;
	}
	else {
		return nullptr;
	}

}

//this is how I can return expressions and put it into the nodes
Expression Interpreter::expression_factory(string changeToExpression) {

	//get rid of parentheses;
	changeToExpression.erase(changeToExpression.begin());
	changeToExpression.pop_back();
	changeToExpression.pop_back();


	cout << "THIS IS BEING PASSED INTO EXPRESSION_FACTORY: " << changeToExpression << endl;
	cout << endl;

	// IF ITS A NUMBER
	// && (!is_bool(changeToExpression))
	if (is_number(changeToExpression)) {
		cout << "ITS A NUMBER" << endl;
		double double_expression = stod(changeToExpression);
		return Expression(double_expression);
	}

	//IF ITS A BOOLEAN
	else if (is_bool(changeToExpression) && (!is_number(changeToExpression))) {
		cout << "ITS A STRING" << endl;
		if (changeToExpression == "True") {
			bool boolean_expression = true;
			return Expression(boolean_expression);
		} else if (changeToExpression == "False") {
			bool boolean_expression = false;
			return Expression(boolean_expression);
		}
		cout << "does not go through the BOOLEAN LOOP for expression_factory()" << endl;
	}
	//OTHERWISE IT IS A STRING (SYMBOL)
	else if (is_string(changeToExpression)) {
		cout << "ITS A STRING" << endl;
		return Expression(changeToExpression);
	}
	cout << "ERROR: IT DIDNT GO THROUGH FUNCTION :: RETURN EMPTY EXPRESSION" << endl;
	// return Expression(changeToExpression);
	return Expression();


}



bool Interpreter::is_number(string s) {
	return( strspn( s.c_str(), "-.0123456789" ) == s.size() );
}

bool Interpreter::is_bool(string value) {
	if (value == "true" || value == "True" || value == "false" || value == "False") {
		return true;
	}
	return false;
}

bool Interpreter::is_string(string str) {
	if (is_bool(str) || is_number(str)) {
		return false;
	}
	return true;
}


bool Interpreter::parse(std::istream & expression) noexcept
{
	cout << endl;
	cout << "parse() function called" << endl;

	string output = "";
	string read_from_expression = "";
	while (getline(expression, output)) {
		read_from_expression.insert(0, output);
	}
	getline(expression, read_from_expression);
	cout << endl;
	Tokenize token;	//tokenize returns a vector

	vector<string> vector_of_strings = token.tokenize(read_from_expression);

	for (int i = 0; i < vector_of_strings.size(); ++i) {
		cout << "vector_of_strings[" << i << "] : " << vector_of_strings[i] << endl;
	}

	root = processTokensToTree(vector_of_strings);
	cout << endl;

	cout << endl;
	cout << "what is in the tree: " << endl;
	cout << "ROOT DATA: " << root->data_expression.express.Data.string_value << endl;
	cout << "ROOT CHILD[0]: " << root->children[0]->data << endl;
	// cout << "ROOT CHILD[0][0]: " << root->children[0]->children[0]->data << endl;
	// cout << "ROOT CHILD[0][1]: " << root->children[0]->children[1]->data << endl;


	cout << endl;
	cout << "SUCCESS: PARSED CORRECTLY" << endl;
	return true;
}


//this should return an expression
Expression Interpreter::evaluate_helper(Node * node) {

	Environment env;

	string result;
	cout << "evaluate_helper() called" << std::endl;
	cout << endl;
	cout << "node children size: " << node->children.size() << endl;

	//all functions
	string add = "+";
	string subtract= "-";
	string multiplication = "*";
	string division = "/";
	string not_symbol = "not";
	string or_symbol = "or";
	string less_than = "<";
	string less_than_equal = "<=";
	string greater_than = ">";
	string greater_than_equal = ">=";
	string equals = "=";


	//if its the last node, then just return that
	if (node->children.size() == 0) {
		cout << "INSIDE OF THE CHILDREN SIZE 0" << endl;
		if (node->data_expression.express.type == SymbolType) {
			if (env.is_present_in_map(default_map, node->data_expression.express.Data.string_value)) {
				Expression double_expression = new Expression();
				double_expression.express.type = NumberType;
				double_expression.express.Data.number_value =
									env.value_at_element_in_map(default_map, node->data_expression.express.Data.string_value);
				return double_expression;
			}
		}

	}

	if (node->data_expression.Data.string_value == "+") {
		Expression exp = new Expression;
		exp.express.type = NumberType;
		double result_add_sum = addition(node->children[0]->data_expression, node->children[1]->data_expression);
		exp.express.Data.number_value = result_add_sum;
		return result_add_sum;

	}

	// if (add.compare(node->data)) {
	// 	cout << "IN THE + CONDITION" << endl;
	// 	Expression expression;
	// 	expression.express.type = NumberType;
	// 	cout << "Expression Type: " << expression.express.type << endl;
	// 	double sum = 0;
	// 	for (int i = 0; i < node->children.size(); i++) {
	// 		expression = evaluate_helper(node->children[i]);
	// 		sum += expression.express.Data.number_value;
	// 		cout << "sum in loop: " << sum << endl;
	// 	}
	// 	expression.express.Data.number_value = sum;
	// 	cout << "sum out of loop: " << expression.express.Data.number_value << endl;


		// cout << "INSIDE OF THE + FUNCTION" << endl;
		// double sum = 0;
		// string sum_string = "";
		// for (int index = 0; index < node->children.size(); index++) {
		// 	string addition = evaluate_helper(node->children[index]);
		// 	cout << "evaluated STRING: " << addition << endl;
		// 	int add_int = atoi(addition.substr(1, 2).c_str());
		// 	cout << "evaluated DOUBLE: " << add_int << endl;
		// 	// cout << "result of stoi(addition) : " << add << endl;
		// 	// sum = sum + addition;
		// 	sum = sum + add_int;
		// 	sum_string = to_string(sum);
		// 	cout << "final sum string " << sum_string << endl;
		// }
	// return sum_string;
	// }

	if (node->data_expression.express.type == BooleanType) {
		Expression exp = new Expression;
		exp.express.type = BooleanType;
		exp.express.Data.boolean_value = node->data_expression.express.Data.boolean_value;
		return exp;
	}


	else if (subtract.compare(node->data)) {
		cout << "IN THE - CONDITION" << endl;
		// cout << "INSIDE OF THE - FUNCTION" << endl;
		// double sum = 0;
		// string subtract_string = "";
		// for (int i = 0; i < node->children.size(); i++) {
		// 	string subtraction = evaluate_helper(node->children[i]);
		// 	cout << "evaluated STRING: " << subtraction << endl;
		// 	int sub_int = atoi(subtraction.substr(1, 2).c_str());
		// 	cout << "evaluated DOUBLE: " << sub_int << endl;
		// 	sum = sum - sub_int;
		// 	subtract_string = to_string(sum);
		// 	cout << "final subtract string " << subtract_string << endl;
		// }
	}

	else {
		cout << "didnt go through any of the if statements" << endl;
	}
	return node->data_expression;

}




Expression Interpreter::eval() {
	cout << endl;
	cout << "evaluate() function called" << endl;
	cout << endl;
	Expression expression_evaluate;
	string result = "";
	expression_evaluate = evaluate_helper(root);
	cout << endl;
	cout << "RESULT: " << result << endl;
	cout << endl;
	return expression_evaluate;
}


//_-nary functions
bool Interpreter::logical_not(Expression x) {
	if (x.express.Data.boolean_value == false) {
		return true;
	} else {
		return false;
	}
}

bool Interpreter::logical_and(Expression x, Expression y) {
	if ((x.express.Data.boolean_value && y.express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool Interpreter::logical_or(Expression x, Expression y) {
	if ((x.express.Data.boolean_value || y.express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool Interpreter::equals(Expression x, Expression y) {
	if (x.express.Data.boolean_value == y.express.Data.boolean_value) {
		return true;
	} else if (x.express.Data.number_value == y.express.Data.number_value) {
		return true;
	} else if (x.express.Data.string_value == y.express.Data.string_value) {
		return true;
	} else {
		return false;
	}
}

bool Interpreter::greater_than(Expression x, Expression y) {
	if ((x.express.Data.boolean_value > y.express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool Interpreter::greater_than_or_equal(Expression x, Expression y) {
	if ((x.express.Data.boolean_value >= y.express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool Interpreter::less_than_or_equal(Expression x, Expression y) {
	if ((x.express.Data.boolean_value <= y.express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool Interpreter::less_than(Expression x, Expression y) {
	if ((x.express.Data.boolean_value < y.express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

double Interpreter::subtract_expression(Expression x, Expression y) {
	double result = x.express.Data.number_value - y.express.Data.number_value;
	return result;
}

double Interpreter::negation(Expression x) {
	double result = (x.express.Data.number_value * (-1));
	return result;
}

double Interpreter::division(Expression x, Expression y) {
	double result = x.express.Data.number_value / y.express.Data.number_value;
	return result;
}

double Interpreter::addition(Expression x, Expression y) {
	double result = x.express.Data.number_value + y.express.Data.number_value;
	return result;
}

double Interpreter::multiplication(Expression x, Expression y) {
	double result = x.express.Data.number_value * y.express.Data.number_value;
	return result;
}
