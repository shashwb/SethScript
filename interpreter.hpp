#ifndef INTERPRETER_H					// avoid repeated expansion
#define INTERPRETER_H


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>

#include "expression.hpp"
// #include "environment.hpp"


using namespace std;


struct Node {
	public:
		vector<Node*> children;
		string data;
		Expression data_expression;
		Node(string data) {
			this->data = data;
		}
};


class test {
public:
	test(){};
	~test(){};
};


class interpreter {


public:

	interpreter();
	~interpreter();
	bool parse(std::istream & expression) noexcept;
	Expression eval();
	void createTree();
	Node * processTokensToTree(vector<string> recursive_vector);
	Expression evaluate_helper(Node * node);
	Expression expression_factory(string changeToExpression);



	bool logical_not(Expression x);
	bool logical_and(Expression x, Expression y);
	bool logical_or(Expression x, Expression y);
	bool equals(Expression x, Expression y);
	bool greater_than(Expression x, Expression y);
	bool greater_than_or_equal(Expression x, Expression y);
	bool less_than_or_equal(Expression x, Expression y);
	bool less_than(Expression x, Expression y);
	double subtract_expression(Expression x, Expression y);
	double negation(Expression x);
	double division(Expression x, Expression y);
	double addition(Expression x, Expression y);
	double multiplication(Expression x, Expression y);

	// double addition(string x, string y);


private:
	test e;

	//private tree default (empty tree)
	Node * root;

	//default enviornment variable
	// Environment * environment;

};

#endif
