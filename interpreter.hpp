#include <iostream>
#include <string>
#include <fstream>
#include <vector>


using namespace std;

class interpreter {

public:
	//public functions
	interpreter();
	void tokenize(std::istream & expression);
	bool parse();
	int eval();

private:
	//private tree
	//private enviornment

};