#include "expression.hpp"
#include <cstring>
#include <string>


Expression::Expression() {
	data.type = NoneType;
	data.number_value = 0.0;
}

Expression::Expression(bool value) {
	data.type = BooleanType;
	data.boolean_value = value;

}

Expression::Expression(double value) {
	data.type = NumberType;
	data.number_value = value;
}

Expression::Expression(const std::string & value) {
	data.type = SymbolType;
	data.string_value = new char[value.length()];
	strcpy(data.string_value, value.c_str());
	
}

bool Expression::operator==(const Expression & exp) const noexcept {
	
	// return (exp.data.string_value);
	// if (exp.data.type == Expression::SymbolType) {
	// 	return true;
	// }
	// return false;
	// if (exp.data.type == Expression::SymbolType) {

	// }
	// else if (exp.data.type == Expression::BooleanType) {

	// }
	// else if (exp.data.type == Expression::NumberType) {

	// }
	// else if (exp.data.type == Expression::NoneType) {

	// }
	// else {
	// 	return false;
	// }
	return true;
}