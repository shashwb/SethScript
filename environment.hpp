#ifndef ENVIRONMENT_H					// avoid repeated expansion
#define ENVIRONMENT_H

#include <unordered_map>
#include "expression.hpp"

using namespace std;

class Environment {
public: 
	Environment();
	~Environment();

	bool isInMap(Expression symbol);
	// Expression elems(Expression symbol);
	// void Environment::update_map(Expression symbol, Expression value);

private:
	// typedef unordered_map<Expression, Expression> Map;
	// Map TheGreatMap;

};


#endif