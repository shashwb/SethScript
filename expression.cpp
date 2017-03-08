#include "expression.hpp"
#include <cstring>
#include <string>

//empty constructor
//whe we create an Expression, it starts with the following values
Expression::Expression() {
	Express.type = NoneType;
	Express.Data.number_value = 0.0;
}

//when given a boolean value, return an Expression structure 
//	this structure will have the type BooleanType and the value in the parameter
Expression::Expression(bool value) {
	Express.type = BooleanType;
	Express.Data.boolean_value = value;
}

Expression::Expression(double value) {
	Express.type = NumberType;
	Express.Data.number_value = value;
}

Expression::Expression(const std::string & value) {
	Express.type = SymbolType;
	Express.Data.string_value = value;
}

//overrride the "==" operator so that we can compare expressions
// WORK WITH TUTOR TO FIX THIS
bool Expression::operator==(const Expression & exp) const noexcept {
	return true;
}

