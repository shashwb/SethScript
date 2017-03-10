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
	cout << "Arg to expression constructor: " << value << endl;
	Express.type = SymbolType;
	cout << "Type: " << Express.type;
	Express.Data.string_value = value;
	cout << "String: " << Express.Data.string_value << endl;
}



//overrride the "==" operator so that we can compare expressions
bool Expression::operator==(const Expression & exp) const noexcept {
	//if the two types are the same
	if (this->Express.type == exp.Express.type) {
		//if its a number type
		if (this->Express.type == Expression::NumberType
			&& exp.Express.type == Expression::NumberType) {
			//check the value
			if (this->Express.Data.number_value == exp.Express.Data.number_value) {
				return true;
			} else if (this->Express.Data.number_value != exp.Express.Data.number_value) {
				return false;
			}
		}

		//if its a boolean value
		if (this->Express.type == Expression::BooleanType
			&& exp.Express.type == Expression::BooleanType) {
			//if the values of boolean are equal
			if (this->Express.Data.boolean_value == exp.Express.Data.boolean_value) {
				return true;
			} else if (this->Express.Data.boolean_value != exp.Express.Data.boolean_value) {
				return false;
			}
		}

		//if it's a string value (symbol)
		if (this->Express.type == Expression::SymbolType
			&& exp.Express.type == Expression::SymbolType) {
			//if the values of boolean are equal
			if (this->Express.Data.string_value == exp.Express.Data.string_value) {
				return true;
			} else if (this->Express.Data.string_value != exp.Express.Data.string_value) {
				return false;
			}
		}
	}
	//else
	return false;
}
