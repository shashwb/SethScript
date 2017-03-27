#include "expression.hpp"
#include <cstring>
#include <string>

//empty constructor
//whe we create an Expression, it starts with the following values
Expression::Expression() {
	express.type = NoneType;
	express.Data.number_value = 0.0;
}

//when given a boolean value, return an Expression structure
//	this structure will have the type BooleanType and the value in the parameter
Expression::Expression(bool value) {
	// cout << "BOOL Arg to expression constructor: " << value << endl;
	express.type = BooleanType;
	// cout << "BOOL Type: " << express.type << endl;
	express.Data.boolean_value = value;
	// cout << "bool value: " << express.Data.boolean_value << endl;
}

Expression::Expression(double value) {
	// cout << "DOUBLE Arg to expression constructor: " << value << endl;
	express.type = NumberType;
	// cout << "DOUBLE Type: " << express.type << endl;
	express.Data.number_value = value;
	// cout << "Double value: " << express.Data.number_value << endl;
}

Expression::Expression(const std::string & value) {
	// cout << "STRING Arg to expression constructor: " << value << endl;
	express.type = SymbolType;
	// cout << "STRING Type: " << express.type << endl;
	express.Data.string_value = value;
	// cout << "String value: " << express.Data.string_value << endl;
}



//overrride the "==" operator so that we can compare expressions
bool Expression::operator==(const Expression & exp) const noexcept {
	//if the two types are the same
	if (this->express.type == exp.express.type) {
		//if its a number type
		if (this->express.type == NumberType
			&& exp.express.type == NumberType) {
			//check the value
			if (this->express.Data.number_value == exp.express.Data.number_value) {
				return true;
			} else if (this->express.Data.number_value != exp.express.Data.number_value) {
				return false;
			}
		}

		//if its a boolean value
		if (this->express.type == BooleanType
			&& exp.express.type == BooleanType) {
			//if the values of boolean are equal
			if (this->express.Data.boolean_value == exp.express.Data.boolean_value) {
				return true;
			} else if (this->express.Data.boolean_value != exp.express.Data.boolean_value) {
				return false;
			}
		}

		//if it's a string value (symbol)
		if (this->express.type == SymbolType
			&& exp.express.type == SymbolType) {
			//if the values of boolean are equal
			if (this->express.Data.string_value == exp.express.Data.string_value) {
				return true;
			} else if (this->express.Data.string_value != exp.express.Data.string_value) {
				return false;
			}
		}
	}
	//else
	return false;
}
