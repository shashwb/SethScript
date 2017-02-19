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

	enum Type {
		NoneType = 0,
		BooleanType,
		NumberType,
		SymbolType
	};

	struct {
		Type type;
		union {
			double number_value;
			bool boolean_value;
			char * string_value;
		} data;
	};

private:


	//private tree


	//private enviornment

};
