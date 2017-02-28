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

	struct data {
		double number_value;
		bool boolean_value;
		string string_value;
	};

	//this struct "expression", has a enum Type and actual data that it can be
	struct {
		Type type;
		data Data;
	} Express;


private:
	//private tree
	//private enviornment
};








#endif
