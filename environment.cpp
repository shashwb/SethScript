#include "environment.hpp"

using namespace std;

Environment::Environment() {
	cout << "an Environment is created" << endl;
}

Environment::~Environment() {

}

bool Environment::isInMap(Expression symbol) {
	return true;
}

Expression Environment::valueOfElement(Expression symbol) {
	return symbol;
}