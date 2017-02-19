#include <string>
#include <iostream>

using namespace std;

class Expression {

public:
	//public functions
	Expression();
	Expression(bool value);
	Expression(double value);
	Expression(const std::string & value);
	bool operator==(const Expression & exp) const noexcept;

private:
	
	struct Node {
		// Expression data;
		vector<Node *> children;
	};

	//private tree


	//private enviornment

};
