#include "interpreter.hpp"
#include "tokenize.hpp"
#include "environment.hpp"
#include "expression.hpp"
#include <stack>
#include <algorithm>

using namespace std;

	//GLOBAL
	typedef unordered_map<string, string> UnorderedMapDynamic;
	UnorderedMapDynamic tree_map;

// unordered_map<string, double> environment_map;

interpreter::interpreter() {
	Environment environment;	//creates default environment
}

interpreter::~interpreter() {
	// root = NULL;
	// delete root;
}

Node * interpreter::processTokensToTree(vector<string> recursive_vector) {
	cout << endl;
	cout << "we are currently in the processTokensToTree() function" << endl;
	// cout << "front of vector: " << recursive_vector[0] << "back of vector: " << recursive_vector.back();
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

		//pop matching parentheses
		recursive_vector.erase(recursive_vector.begin());
		recursive_vector.pop_back();

		Node* newNode = new Node(recursive_vector[0]); // new node holds first value
		Expression newExpress = expression_factory(recursive_vector[0]);
		newNode->data_expression = newExpress;
		newNode->data_expression.Express.Data.number_value = round(newNode->data_expression.Express.Data.number_value);
		//cout << newNode->data_expression << endl;
		cout << endl;
		cout << "HEY" << newNode->data_expression.Express.Data.number_value << endl;
		cout << "newNode value: " << newNode->data_expression.Express.Data.number_value << endl;
		cout << "newNode type: " << newNode->data_expression.Express.type << endl;
		cout << endl;

		recursive_vector.erase(recursive_vector.begin());
		cout << "Ready to loop" << endl;
		while (recursive_vector.size() > 0) {
			Node * new_child;
			// cout << "IN WHILE LOOP (processTokensToTree()" << endl;
			if (recursive_vector[0] != "\"(\",") {
				cout << "NEW SIMPLE CHILD: ";
				cout << recursive_vector[0] << endl;
				new_child = new Node(recursive_vector[0]);
				recursive_vector.erase(recursive_vector.begin());
			}
			else {
				cout << "NEW EXPRESSION CHILD: ";
				cout << recursive_vector[0] << endl;
				// cout << "IF HIT ANOTHER PARENTHESES(processTokensToTree()" << endl;
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
Expression interpreter::expression_factory(string changeToExpression) {

	bool boolean_expression;
	double number_expression;
	string symbol_expression;

	cout << "changeToExpression value: " << changeToExpression << endl;

	//get rid of parentheses;
	changeToExpression.erase(changeToExpression.begin());
	changeToExpression.pop_back();
	changeToExpression.pop_back();

	cout << "changeToExpression value after POPS(): " << changeToExpression << endl;

	// if (isdigit(changeToExpression[0])) {
	// 	number_expression = stod(changeToExpression);
	// 	return Expression(number_expression);
	// }
	if (changeToExpression == "false") {
		cout << "gets to boolean condition false" << endl;
		boolean_expression = false;
		return Expression(boolean_expression);
	}
	else if (changeToExpression == "true") {
		cout << "gets to boolean condition true" << endl;
		boolean_expression = true;
		return Expression(boolean_expression);
	}
	else {
		cout << "gets to what I want!!!!" << endl;
		symbol_expression = changeToExpression;
		cout << endl;
		cout << "symbol_expression WHY ISNT THIS WORKING???: " << symbol_expression << endl;
		return Expression(symbol_expression);
	}
}


bool interpreter::parse(std::istream & expression) noexcept
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
	cout << "ROOT DATA: " << root->data << endl;
	cout << "ROOT CHILD[0]: " << root->children[0]->data << endl;
	// cout << "ROOT CHILD[0][0]: " << root->children[0]->children[0]->data << endl;
	// cout << "ROOT CHILD[0][1]: " << root->children[0]->children[1]->data << endl;


	cout << endl;
	cout << "SUCCESS: PARSED CORRECTLY" << endl;
	return true;
}


//this should return an expression
Expression interpreter::evaluate_helper(Node * node) {

	string result;
	cout << "evaluate_helper() called" << std::endl;
	cout << endl;
	cout << "node children size: " << node->children.size() << endl;

	//SHOULD I ITERATE THROUGH THE TREE HERE AND ADD THE EXPRESSION VARIABLES TO EVERYTHING?

	//all functions
	string add = "+";
	// string subtract_binary = "-";
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

	}

	if (add.compare(node->data)) {
		cout << "IN THE + CONDITION" << endl;
		Expression expression;
		expression.Express.type = Expression::NumberType;
		cout << "Expression Type: " << expression.Express.type << endl;
		double sum = 0;
		for (int i = 0; i < node->children.size(); i++) {
			expression = evaluate_helper(node->children[i]);
			sum += expression.Express.Data.number_value;
			cout << "sum in loop: " << sum << endl;
		}
		expression.Express.Data.number_value = sum;
		cout << "sum out of loop: " << expression.Express.Data.number_value << endl;


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
	return node->data;





	// return result;
}




Expression interpreter::eval() {

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
bool interpreter::logical_not(Expression x) {
	if (x.Express.Data.boolean_value == false) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::logical_and(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value && y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::logical_or(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value || y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::equals(Expression x, Expression y) {
	if (x.Express.Data.boolean_value == y.Express.Data.boolean_value) {
		return true;
	} else if (x.Express.Data.number_value == y.Express.Data.number_value) {
		return true;
	} else if (x.Express.Data.string_value == y.Express.Data.string_value) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::greater_than(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value > y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::greater_than_or_equal(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value >= y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::less_than_or_equal(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value <= y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

bool interpreter::less_than(Expression x, Expression y) {
	if ((x.Express.Data.boolean_value < y.Express.Data.boolean_value) == true) {
		return true;
	} else {
		return false;
	}
}

double interpreter::subtract_expression(Expression x, Expression y) {
	double result = x.Express.Data.number_value - y.Express.Data.number_value;
	return result;
}

double interpreter::negation(Expression x) {
	double result = (x.Express.Data.number_value * (-1));
	return result;
}

double interpreter::division(Expression x, Expression y) {
	double result = x.Express.Data.number_value / y.Express.Data.number_value;
	return result;
}

double interpreter::addition(Expression x, Expression y) {
	double result = x.Express.Data.number_value + y.Express.Data.number_value;
	return result;
}

double interpreter::multiplication(Expression x, Expression y) {
	double result = x.Express.Data.number_value * y.Express.Data.number_value;
	return result;
}
