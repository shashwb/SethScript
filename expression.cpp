#include "expression.hpp"
#include <cstring>
#include <string>

//empty constructor
Expression::Expression() {
	Express.type = NoneType;
	Express.Data.number_value = 0.0;
}

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

bool Expression::operator==(const Expression & exp) const noexcept {
	return true;
}

