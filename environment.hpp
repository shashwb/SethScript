#include <unordered_map>
#include "expression.hpp"

using namespace std;

class Environment {
public: 
	Environment();
	~Environment();

	bool isInMap(Expression symbol);
	Expression valueOfElement(Expression symbol);

private:
	typedef unordered_map<string, double> Map;
	Map SymbolsToAtoms;

};