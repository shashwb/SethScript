#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include "expression.hpp"


using namespace std;

class interpreter {

public:
	//public functions
	interpreter();
	~interpreter();
	bool parse(std::istream & expression) noexcept;
	int eval();	//FIX THIS

private:
	
	struct Node {
		// Expression data;
		vector<Node *> children;
	};

	//private tree


	//private enviornment

};