#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

// #include "expression.hpp"
#include "environment.hpp"


using namespace std;

class interpreter {

public:
	//public functions
	interpreter();
	~interpreter();
	bool parse(std::istream & expression) noexcept;
	Expression eval();


	//helper function
	// bool logical_not(Expression x);
	// bool logical_add(Expression x, Expression y);
	// bool logical_or(Expression x, Expression y);
	// bool equals(Expression x, Expression y);
	// bool greater_than(Expression x, Expression y); 
	// bool greater_than_or_equal(Expression x, Expression y); 
	// bool less_than_or_equal(Expression x, Expression y); 
	// bool less_than(Expression x, Expression y);
	// double subtract_expression(Expression x, Expression y);
	// double negation(Expression x);
	// double division(Expression x, Expression y);
	// double addition(Expression x, Expression y);
	// double multiplication(Expression x, Expression y);


private:
	
	struct Node {
		Expression expression;
		vector<Node *> children;
	};

	//private tree default (empty tree)
	Node * root;

	//default enviornment variable 
	Environment * environment;

};