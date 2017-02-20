#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <iostream>
#include <cstring>

using namespace std;

class Expression {

public:
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

	//a struct called data that has a type AND one of the union values
	//any object of this class has a structure like this
	struct {
		Type type;
		union {
			double number_value;
			bool boolean_value;
			char * string_value;
		};
	} data;

private:


	//private tree


	//private enviornment

};

#endif
