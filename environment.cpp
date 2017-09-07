#include "environment.hpp"

#include "math.h"

using namespace std;


Environment::Environment() {
    double PI = atan2(0, -1);
  Expression *pi_expression = new Expression(PI);
    this->add_element_to_map("pi", pi_expression);
}

Environment::~Environment() {

}

//double Environment::sin(double num) {
//    return sin(num);
//}
//
//double Environment::cos(double num) {
//    return cos(num);
//}
//
//double Environment::arctan(double num_one, double num_two) {
//    double cos_result = num_one;
//    double tan_result = num_two;
//    return tan_result;
//}


void Environment::clearMap() {
    default_map.clear();
}

void Environment::print_map() {

//    if (x.second->express.type.BooleanType) {

//        cout << "boolean" << endl;

        for (auto& x: default_map) std::cout << " " << x.first << " : " << x.second->express.Data.boolean_value;

        cout << endl;
//        cout << "number values" << endl;

        for (auto& y: default_map) std::cout << " " << y.first << " : " << y.second->express.Data.number_value;

//    } else if (x.second->express.type.SymbolType) {

//        for (auto& x: default_map) std::cout << " " << x.first << " : " << x.second->express.Data.string_value;

//    } else if (x.second->express.type.NumberType) {

//        for (auto& x: default_map) std::cout << " " << x.first << " : " << x.second->express.Data.number_value;

//    } else {
//        cout << "SOMETHING IS WRONG HERE!!!" << endl;
//    }

}





bool Environment::is_present_in_map(string symbol) {

    auto got_default = default_map.find(symbol);
    if (got_default == default_map.end()) {
        return false;
    } else {
        return true;
    }

}

double Environment::value_at_element_in_map(string symbol) {
    auto got_default = default_map.find(symbol);
    if (got_default == default_map.end()) {
    }
    if (got_default->second->express.type == NumberType) {
        return got_default->second->express.Data.number_value;
    } else if (got_default->second->express.type == BooleanType) {
        return got_default->second->express.Data.boolean_value;
    }
    return got_default->second->express.Data.boolean_value;
}


void Environment::update_map_with_value(string symbol, Expression *new_value) {
    auto it = default_map.find(symbol);
    if (it != default_map.end()) {
        it->second = new_value;
    }

}

void Environment::add_element_to_map(string symbol, Expression *value) {

//	pair<string,*Expression> add_this(symbol, value);
    default_map.insert({symbol, value});

}
