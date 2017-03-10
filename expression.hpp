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
	bool operator==(const Expression & exp) const noexcept;	//TODO

	enum Type {
		NoneType = 0,
		BooleanType,
		NumberType,
		SymbolType
	};

	typedef struct {
		double number_value;
		bool boolean_value;
		string string_value;
	} data;

	// an expression can have a type (options are the enums)
	// and can also have data (options are the struct "data" members)
	struct {
		Type type;
		data Data;
	} Express;

	// data myData;
	// Express myExpress;

private:

};








#endif
