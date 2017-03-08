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
	if (recursive_vector[0] == "\"(\"" && recursive_vector.back() == "\")\"") {
		cout << "Valid data" << endl;
		// cout << "IN IF STATEMENT (processTokensToTree()" << endl;
		//if the first or last element in the vector is a parentheses
		recursive_vector.erase(recursive_vector.begin());
		recursive_vector.pop_back();	//pop matching parentheses

		Node* newNode = new Node(recursive_vector[0]); // new node holds first value
		recursive_vector.erase(recursive_vector.begin());
		cout << "Ready to loop" << endl;
		while (recursive_vector.size() > 0) {
			Node * new_child;
			// cout << "IN WHILE LOOP (processTokensToTree()" << endl;

			if (recursive_vector[0] != "\"(\"") {
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
				children_of_node.push_back(recursive_vector[0]); //parentheses loaded into vector
				recursive_vector.erase(recursive_vector.begin());
				cout << "Building " << endl;
				while (open_parentheses_counter > 0) {
					cout << "parens: " << open_parentheses_counter << ": " << recursive_vector[0] << endl;
					if (recursive_vector[0] == "\"(\"") {
						open_parentheses_counter = open_parentheses_counter + 1;
					}
					else if (recursive_vector[0] == "\")\"") {
						open_parentheses_counter = open_parentheses_counter - 1;
					}

					//else {
						//push everything that isn't a parentheses into the vector
						children_of_node.push_back(recursive_vector[0]);
						recursive_vector.erase(recursive_vector.begin());
					//}
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
			cout << "!!!recursive_vector[" << i << "] : " << newNode->children[i]->data << endl;
		}
		return newNode;
	}
	else {
		return nullptr;
	} 	//badly formed

	// return nullptr;

}


Expression interpreter::expression_factory(string changeToExpression) {

	bool boolean_expression;
	double number_expression;
	string symbol_expression;

	if (isdigit(changeToExpression[0])) {
		number_expression = stod(changeToExpression);
		return Expression(number_expression);
	}
	else if (changeToExpression == "false") {
		boolean_expression = false;
		return Expression(boolean_expression);
	}
	else if (changeToExpression == "true") {
		boolean_expression = true;
		return Expression(boolean_expression);
	}
	else {
		symbol_expression = changeToExpression;
		return Expression(symbol_expression);
	}
}

bool interpreter::parse(std::istream & expression) noexcept
{
	cout << endl;
	cout << "parse() function called" << endl;
	stack<string> parentheses_checker;
	int parentheses_counter_open = 0;
	int parentheses_checker_closed = 0;

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
	cout << "ROOT CHILD[0][0]: " << root->children[0]->children[0]->data << endl;
	cout << "ROOT CHILD[0][1]: " << root->children[0]->children[1]->data << endl;


	cout << endl;
	cout << "SUCCESS: PARSED CORRECTLY" << endl;
	return true;
}


//this should return an expression
string interpreter::evaluate_helper(Node * node) {

	string result;
	cout << "evaluate_helper() called" << std::endl;


	cout << endl;
	cout << "node children size: " << node->children.size() << endl;

	if (node->children.size() == 0) {
	// if (true) {
 		if (environment->is_present_in_map(node->data)) {
			// return node.data;
			cout << "the data is in the map, return it" << endl;
		}
		else {
			cout << "may be a constant" << endl;
		}
	}


	if (node->data == "+") {
		// int sum = 0;
		
	}
	if (node->data == "*") {
		int product = 1;
		for (int i = 0; i < node->children.size() - 1; i++) {
			int eval_int = atoi(evaluate_helper(node->children[i]).c_str());
			product = product * eval_int;
		}
		return to_string(product);
	}
	//etc for the other functions HAVE TO DO THE OTHER FUNCTIONS

	return result;
}




Expression interpreter::eval() {

	cout << endl;
	cout << "evaluate() function called" << endl;
	cout << endl;

	Expression expression_evaluate;

	string result = "";
	result = evaluate_helper(root);
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














