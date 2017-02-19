#include "expression.hpp"


Expression::Expression() {

}

Expression::Expression(bool value) {

}

Expression::Expression(double value) {

}

Expression::Expression(const std::string & value) {

}

bool operator==(const Expression & exp) const noexcept {
	return true;
}