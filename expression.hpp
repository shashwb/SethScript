#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <iostream>
#include <cstring>

using namespace std;


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


typedef struct {
	Type type;
	data Data;
} Express;

class Expression {

public:
	Expression();
	Expression(bool value);
	Expression(double value);
	Expression(const std::string & value);
	bool operator==(const Expression & exp) const noexcept;	//TODO



	data Data;
	Express express;

private:

};








#endif
