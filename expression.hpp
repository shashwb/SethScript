#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>
#include <iostream>
#include <cstring>
#include <tuple>

using namespace std;


enum Type {
    NoneType = 0,
    BooleanType,
    NumberType,
    SymbolType,
    PointType,
    LineType,
    ArcType
};


typedef struct {
    std::tuple<double,double> point_value;
} Point;

typedef struct {
    Point line_value_start;
    Point line_value_end;
} line;

typedef struct {
    double number_value;
    bool boolean_value;
    string string_value;
    Point point;
    line Line;
    std::tuple<double,double> center_value;
    std::tuple<double,double> start_value;
    double arc_value;
} data;


typedef struct {
    Type type;
    data Data;
} Express;

class Expression {

public:
    Expression();
    Expression(bool value);
    Expression(double value);
    Expression(const std::string & value);
    bool is_number(string s);
    bool operator==(const Expression & exp) const noexcept;
    Expression(std::tuple<double,double> value);
    Expression(std::tuple<double,double> start,
               std::tuple<double,double> end);
    Expression(std::tuple<double,double> center,
               std::tuple<double,double> start,
               double angle);

    data Data;
    Express express;
    line Line;
    Point point;
};

#endif
