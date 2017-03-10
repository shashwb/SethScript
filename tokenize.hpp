#ifndef TOKENIZE_H					// avoid repeated expansion
#define TOKENIZE_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>

using namespace std;

class Tokenize {

public:
	vector<string> tokenize(string expression);
};

#endif
