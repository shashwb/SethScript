#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

class interpreter {

public:
	//public functions
	interpreter();
	void tokenize(string expression);
	bool parse(std::istream & expression);
	int eval();

private:
	//private tree
	//private enviornment

};