#include "expression.hpp"
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>


Expression::Expression() {
    express.type = NoneType;
    express.Data.number_value = 0.0;
}


Expression::Expression(bool value) {
    express.type = BooleanType;
    express.Data.boolean_value = value;
}

Expression::Expression(double value) {
    express.type = NumberType;
    express.Data.number_value = value;
}

Expression::Expression(const std::string & value) {
    if (is_number(value)) {
        express.type = NumberType;
        express.Data.number_value = stod(value);
    } else {
        express.type = SymbolType;
        express.Data.string_value = value;
    }
}

Expression::Expression(std::tuple<double,double> value) {
    express.type = PointType;
    express.Data.point.point_value = value;
}

//this is the line expression
Expression::Expression(std::tuple<double,double> start, std::tuple<double,double> end) {
    express.type = LineType;
    express.Data.Line.line_value_start.point_value = start;
    express.Data.Line.line_value_end.point_value = end;
}


Expression::Expression(std::tuple<double,double> center, std::tuple<double,double> start, double angle) {
    express.type = ArcType;
    express.Data.center_value = center;
    express.Data.center_value = start;
    express.Data.arc_value = angle;
}

bool Expression::is_number(string s) {
    char * p;
    strtol(s.c_str(), &p, 10);
    return *p == 0;
}

bool Expression::operator==(const Expression & exp) const noexcept {
    if (this->express.type == exp.express.type) {
        if (this->express.type == NumberType
            && exp.express.type == NumberType) {
            if (this->express.Data.number_value == exp.express.Data.number_value) {
                return true;
            } else if (this->express.Data.number_value != exp.express.Data.number_value) {
                return false;
            }
        }
        if (this->express.type == BooleanType
            && exp.express.type == BooleanType) {
            if (this->express.Data.boolean_value == exp.express.Data.boolean_value) {
                return true;
            } else if (this->express.Data.boolean_value != exp.express.Data.boolean_value) {
                return false;
            }
        }
        if (this->express.type == SymbolType
            && exp.express.type == SymbolType) {
            if (this->express.Data.string_value == exp.express.Data.string_value) {
                return true;
            } else if (this->express.Data.string_value != exp.express.Data.string_value) {
                return false;
            }
        }
    }
    return false;
}
