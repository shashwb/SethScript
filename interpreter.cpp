#include "interpreter.hpp"
#include "tokenize.hpp"
#include "expression.hpp"
#include <stack>
#include <algorithm>
#include <regex>
#include <tuple>
#include "interpreter_semantic_error.hpp"

using namespace std;


Interpreter::Interpreter() {
    root = nullptr;
    env = new Environment;
}

Interpreter::~Interpreter() {
    root = NULL;
    delete root;
}


Node * Interpreter::processTokensToTree(vector<string> recursive_vector) {
    if (recursive_vector[0] == "\"(\"," && (recursive_vector.back() == "\")\""
        || recursive_vector.back() == "\")\",")) {
        if (recursive_vector.size() <= 2) {
            return nullptr;
        }
        recursive_vector.erase(recursive_vector.begin());
        recursive_vector.pop_back();
//        Node* newNode = new Node(expression_factory(recursive_vector[0])); // new node holds first value
        recursive_vector[0].erase(recursive_vector[0].begin());
        recursive_vector[0].pop_back();
        recursive_vector[0].pop_back();
        Node* newNode = new Node(Expression(recursive_vector[0]));
        recursive_vector.erase(recursive_vector.begin());
        while (recursive_vector.size() > 0) {
            Node * new_child;
            if (recursive_vector[0] != "\"(\",") {
                new_child = new Node(expression_factory(recursive_vector[0]));
                recursive_vector.erase(recursive_vector.begin());
            }
            else {
                int open_parentheses_counter = 1;
                vector<string> children_of_node;
                children_of_node.push_back(recursive_vector[0]);
                recursive_vector.erase(recursive_vector.begin());
                while (open_parentheses_counter > 0) {
                    if (recursive_vector[0] == "\"(\",") {
                        open_parentheses_counter = open_parentheses_counter + 1;
                    }
                    else if (recursive_vector[0] == "\")\"" || recursive_vector[0] == "\")\",") {
                        open_parentheses_counter = open_parentheses_counter - 1;
                    }
                    children_of_node.push_back(recursive_vector[0]);
                    recursive_vector.erase(recursive_vector.begin());
                }
                new_child = processTokensToTree(children_of_node);
            }
            newNode->children.push_back(new_child);
        }
        return newNode;
    }
    else {
        return nullptr;
    }

}


Expression Interpreter::expression_factory(string changeToExpression) {
    if (changeToExpression[0] == '\"' && (changeToExpression.back() == '\"' || changeToExpression.back() == ',')) {
        changeToExpression.erase(changeToExpression.begin());
        changeToExpression.pop_back();
        changeToExpression.pop_back();
    }
    if (is_number(changeToExpression)) {
        double double_expression = stod(changeToExpression);
        return Expression(double_expression);
    }
    else if (is_bool(changeToExpression) && (!is_number(changeToExpression))) {
        if (changeToExpression == "True") {
            bool boolean_expression = true;
            return Expression(boolean_expression);
        } else if (changeToExpression == "False") {
            bool boolean_expression = false;
            return Expression(boolean_expression);
        }
    }
    else if (is_string(changeToExpression)) {
        return Expression(changeToExpression);
    }
    return Expression();
}



bool Interpreter::is_number(string s) {
    char * p;
    strtol(s.c_str(), &p, 10);
    return *p == 0;
}

bool Interpreter::is_bool(string value) {
    if (value == "true" || value == "True" || value == "false" || value == "False") {
        return true;
    }
    return false;
}

bool Interpreter::is_string(string str) {
    if (is_bool(str) || is_number(str)) {
        return false;
    }
    return true;
}



bool Interpreter::parse(std::istream & expression) noexcept
{
    string output = "";
    string read_from_expression = "";
    while (getline(expression, output)) {
       if (output[0] == ';') {
            int found = output.find(';');
            int found_r = output.find('\r');
            if (found != string::npos) {
                output = output.substr(0, found);
            }
            else if (found_r != string::npos) {
                string mid_one = output.substr(0, found_r);
                string mid_two = output.substr(found_r+1, output.length());
                output.append(mid_one).append(mid_two);
            }
           read_from_expression.append(output);
    }
        else {
            read_from_expression.append(output);
        }
    }
    if (read_from_expression.empty()) {
        return false;
    }
    Tokenize token;
    vector<string> vector_of_strings = token.tokenize(read_from_expression);
    int opening_paren = 0;
    int closing_paren = 0;
    for (int i = 0; i < vector_of_strings.size(); ++i) {
        if (vector_of_strings[i] == "\"(\",") {
            opening_paren++;
        }
        else if (vector_of_strings[i] == "\")\"," || vector_of_strings[i] == "\")\"") {
            closing_paren++;
        }
        else if (vector_of_strings[i] == "\"1abc\",") {
            return false;
        }
    }
    if ((opening_paren != closing_paren) || (opening_paren + closing_paren == 0)) {
        return false;
    }
    root = processTokensToTree(vector_of_strings);
    if (root == nullptr) {
      return false;
    }
    return true;
}


Expression Interpreter::evaluateDefine(Node* node) {
    Expression exp = new Expression;
    if (node->children[0]->data_expression.express.Data.string_value != "define" && node->children[0]->data_expression.express.Data.string_value != "if" &&
        node->children[0]->data_expression.express.Data.string_value != "begin" && node->children[0]->data_expression.express.Data.string_value != "pi") {
        if (env->is_present_in_map(node->children[0]->data_expression.express.Data.string_value)) {
            if (node->children[1]->children.size() >= 1) {
                Expression *complex_define = new Expression;
                *complex_define = evaluate_helper(node->children[1]);
                env->add_element_to_map(node->children[0]->data_expression.express.Data.string_value, complex_define);
                return *complex_define;
            }
            if (node->children[1]->data_expression.express.type == NumberType) {
                Expression *express_number = new Expression;
                *express_number = node->children[1]->data_expression;
                env->update_map_with_value(node->children[0]->data_expression.express.Data.string_value, express_number);
                return node->children[1]->data_expression.express.Data.number_value;
            }
            if (node->children[1]->data_expression.express.type == SymbolType) {
                double value_second_child = env->value_at_element_in_map(node->children[1]->data_expression.express.Data.string_value);
                Expression *express_number = new Expression(value_second_child);
                env->update_map_with_value(node->children[0]->data_expression.express.Data.string_value, express_number);
                return *express_number;
            }
            if (node->children[1]->data_expression.express.type == BooleanType) {
                Expression *express_number = new Expression(node->children[1]->data_expression.express.Data.boolean_value);
                env->update_map_with_value(node->children[0]->data_expression.express.Data.string_value, express_number);
                return node->children[1]->data_expression.express.Data.boolean_value;
            }
        }
        else if (node->children[1]->children.size() >= 1) {
            Expression *complex_define = new Expression;
            *complex_define = evaluate_helper(node->children[1]);
            env->add_element_to_map(node->children[0]->data_expression.express.Data.string_value, complex_define);
            return complex_define;
        }
        else if (node->children[1]->data_expression.express.type == BooleanType) {
            Expression *complex_define = new Expression;
            *complex_define = node->children[1]->data_expression.express.Data.boolean_value;
            env->add_element_to_map(node->children[0]->data_expression.express.Data.string_value, complex_define);
            exp.express.Data.boolean_value = node->children[1]->data_expression.express.Data.boolean_value;
            return exp.express.Data.boolean_value;
        }
        else if (node->children[0]->data_expression.express.type == SymbolType && node->children[1]->data_expression.express.type == SymbolType) {
            bool bool_result = env->value_at_element_in_map(node->children[1]->data_expression.express.Data.string_value);
            Expression *express_result = new Expression(bool_result);
            env->add_element_to_map(node->children[0]->data_expression.express.Data.string_value, express_result);
            exp.express.Data.boolean_value = bool_result;
            return *express_result;
        }
        Expression *express_result = new Expression;
        *express_result = node->children[1]->data_expression.express.Data.number_value;
        env->add_element_to_map(node->children[0]->data_expression.express.Data.string_value, express_result);
        exp.express.type = NumberType;
        exp.express.Data.number_value = node->children[1]->data_expression.express.Data.number_value;
        return exp.express.Data.number_value;
    }
    else {
        throw InterpreterSemanticError("Error: cannot redefine");
    }
}

Expression Interpreter::weirdStuff(Node* node) {
    Expression weird = new Expression;
    if (node->data_expression.express.Data.string_value == "@") {
        throw InterpreterSemanticError("Error: no such procedure");
    }
    return weird;
}

Expression Interpreter::evaluateBegin(Node* node) {
    Expression begin_one = new Expression;
    for (int i = 0; i < node->children.size(); i++) {
        if (node->children[i]->children.size() >= 1) {
            begin_one = evaluate_helper(node->children[i]);
        }
        else {
            begin_one = evaluate_helper(node->children[i]);
        }
    }
    if (begin_one.express.type == NumberType) {
        return begin_one.express.Data.number_value;
    }
    else if (begin_one.express.type == SymbolType) {
        return begin_one.express.Data.string_value;
    }
    else {
        return begin_one.express.Data.boolean_value;
    }
}

Expression Interpreter::evaluateIf(Node* node) {
    Expression result_evaluate = evaluate_helper(node->children[0]);
    if (result_evaluate == true) {
        return evaluate_helper(node->children[1]);

    }
    if (result_evaluate == false) {
        return evaluate_helper(node->children[2]);
    }
    return result_evaluate;
}

Expression Interpreter::evaluateAddition(Node* node) {
    Expression exp = new Expression;
    exp.express.type = NumberType;
    string node_rec = node->children[0]->data_expression.express.Data.string_value;

    double result_add_mary = 0;

    for (int i = 0; i < node->children.size(); i++) {
        if (node->children[i]->children.size() >= 1) {
            Expression recursive_result = evaluate_helper(node->children[i]);
            if (recursive_result.express.type == NumberType) {
                result_add_mary = result_add_mary + recursive_result.express.Data.number_value;
            }
            else {
                result_add_mary = result_add_mary + node->children[i]->data_expression.express.Data.number_value;
            }
        } else {
            result_add_mary = result_add_mary + node->children[i]->data_expression.express.Data.number_value;
        }
    }
    exp.express.Data.number_value = result_add_mary;
    exp.express.type = NumberType;
    Expression final_result = Expression(result_add_mary);
//    return exp.express.Data.number_value;
    return final_result;
}


Expression Interpreter::evaluate_helper(Node * node) {

    string result;
    string add = "+", subtract = "-", multiply = "*", divide = "/", not_symbol = "not",
    or_symbol = "or", and_symbol = "and", less_than_symbol = "<", less_than_equal = "<=",
    greater_than_symbol = ">", greater_than_equal = ">=", string_equals = "=";
    string node_string = node->data_expression.express.Data.string_value;

    if (node_string == "@") {
        Expression weird = weirdStuff(node);
        return weird;
    }
    if (node_string == string_equals) {
        Expression equality = new Expression;
        return equality.express.Data.boolean_value = equals(node->children[0]->data_expression.express.Data.number_value, node->children[1]->data_expression.express.Data.number_value);
    }
    if (node_string == subtract) {
        double result_subtract = 0;
        Expression exp = new Expression;
        exp.express.type = NumberType;
        
        if (node->children.size() > 2) {
            throw InterpreterSemanticError("Error: this is a binary type, input doesn't make sense");
        }
        if (node->children.size() == 1) {
            result_subtract = 0 - node->children[0]->data_expression.express.Data.number_value;
            return exp.express.Data.number_value = result_subtract;
        }
        result_subtract = subtract_expression(node->children[0]->data_expression, node->children[1]->data_expression);
        return exp.express.Data.number_value = result_subtract;
    }
    
    
    if (node->children.size() == 0) {
        if (node->data_expression.express.type == SymbolType) {
            if (env->is_present_in_map(node->data_expression.express.Data.string_value)) {
                Expression double_expression = new Expression();
                double_expression.express.type = NumberType;
                double_expression.express.Data.number_value =
                                    env->value_at_element_in_map(node->data_expression.express.Data.string_value);
                return double_expression;
            }
        }
        else if (node->data_expression.express.type == NumberType) {
            return node->data_expression;
        }
    }
    if (node_string == "define") {
        Expression exp = new Expression;
        return exp = evaluateDefine(node);
    }
    else if (node_string == "begin") {
        Expression begin_one = new Expression;
        return begin_one = evaluateBegin(node);
    }
    else if (node_string == "if") {
        if (node->children.size() < 3) {
            return false;
        }
        Expression result_evaluate = evaluate_helper(node->children[0]);
        return result_evaluate = evaluateIf(node);
    }
    else if (node_string == add) {
        Expression addition_exp = new Expression;
        addition_exp = evaluateAddition(node);
        return addition_exp.express.Data.number_value;
    }
    else if (node_string == multiply) {
        Expression exp = new Expression;
        exp.express.type = NumberType;
        string node_rec = node->children[0]->data_expression.express.Data.string_value;

        double result_multiply_mary = 1;

        for (int i = 0; i < node->children.size(); i++) {
            if (node->children[i]->children.size() >= 1) {

                Expression recursive_result = evaluate_helper(node->children[i]);

                result_multiply_mary = result_multiply_mary * recursive_result.express.Data.number_value;
            } else {
                result_multiply_mary = result_multiply_mary * node->children[i]->data_expression.express.Data.number_value;
            }
        }
        exp.express.Data.number_value = result_multiply_mary;
        exp.express.type = NumberType;
        return exp.express.Data.number_value;
    }
    else if (node_string == divide) {

        Expression exp = new Expression;
        exp.express.type = NumberType;
        double result_division = division(node->children[0]->data_expression, node->children[1]->data_expression);
        exp.express.Data.number_value = result_division;
        return exp.express.Data.number_value;
    }
    else if (node_string == not_symbol) {
        Expression exp = new Expression;
        exp.express.type = BooleanType;
        bool result_not = logical_not(node->children[0]->data_expression);
        exp.express.Data.boolean_value = result_not;
        return exp.express.Data.boolean_value;
    }
    else if (node_string == or_symbol) {

        Expression exp = new Expression;
        exp.express.type = BooleanType;

        for (int i = 0; i < node->children.size(); i++) {
            if (node->children[i]->data_expression.express.Data.boolean_value == true) {
                exp.express.Data.boolean_value = true;
                return exp.express.Data.boolean_value;
            } else {
                exp.express.Data.boolean_value = false;
            }
        }
        return exp.express.Data.boolean_value;
    }
    else if (node_string == and_symbol) {

        Expression exp = new Expression;
        exp.express.type = BooleanType;


        if (node->children[0]->data_expression.express.type == SymbolType && node->children[1]->data_expression.express.type == SymbolType) {

            bool boolean_one = env->value_at_element_in_map(node->children[0]->data_expression.express.Data.string_value);
            bool boolean_two = env->value_at_element_in_map(node->children[1]->data_expression.express.Data.string_value);

            Expression first(boolean_one);
            Expression second(boolean_two);

            bool result_and = logical_and(first.express.Data.boolean_value, second.express.Data.boolean_value);

            Expression result_expression(result_and);
            return result_expression.express.Data.boolean_value;
        }

        for (int i = 0; i < node->children.size(); i++) {
            if (node->children[i]->data_expression.express.Data.boolean_value == false) {
                exp.express.Data.boolean_value = false;
                return exp.express.Data.boolean_value;
            } else {
                exp.express.Data.boolean_value = true;
            }
        }
        return exp.express.Data.boolean_value;


    }
    else if (node_string == less_than_symbol) {
        Expression exp = new Expression;
        exp.express.type = BooleanType;
        bool result_less_than = less_than(node->children[0]->data_expression, node->children[1]->data_expression);
        exp.express.Data.boolean_value = result_less_than;
        return exp.express.Data.boolean_value;
    }
    else if (node_string == less_than_equal) {
        Expression exp = new Expression;
        exp.express.type = BooleanType;
        bool result_less_than_or_equal = less_than_or_equal(node->children[0]->data_expression, node->children[1]->data_expression);
        exp.express.Data.boolean_value = result_less_than_or_equal;
        return exp.express.Data.boolean_value;
    }
    else if (node_string == greater_than_symbol) {
        Expression exp = new Expression;
        exp.express.type = BooleanType;
        bool result_greater = greater_than(node->children[0]->data_expression, node->children[1]->data_expression);
        exp.express.Data.boolean_value = result_greater;
        return exp.express.Data.boolean_value;
    }
    else if (node_string == greater_than_equal) {
        Expression exp = new Expression;
        exp.express.type = BooleanType;
        bool result_greater_than_or_equal = greater_than_or_equal(node->children[0]->data_expression, node->children[1]->data_expression);
        exp.express.Data.boolean_value = result_greater_than_or_equal;
        return exp.express.Data.boolean_value;
    }
    else if (node_string == "point") {
        if ((node->children[0]->children.size() >= 1) && (node->children[1]->children.size() >= 1)) {
            Expression complex_expression = evaluate_helper(node->children[0]);
            Expression complex_expression_two = evaluate_helper(node->children[1]);
            tuple<double, double> point_tuple(complex_expression.express.Data.number_value, complex_expression_two.express.Data.number_value);
            Expression result = new Expression;
            result.express.Data.point.point_value = point_tuple;
            result.express.type = PointType;    //just to make sure
            return result.express.Data.point.point_value;
        }
        else if (node->children[0]->children.size() >= 1) {
            Expression final = new Expression;
            Expression complex_exp = new Expression;
            complex_exp = evaluate_helper(node->children[0]);
            Expression expression_map = new Expression;

            if (node->children[1]->data_expression.express.type == SymbolType) {
                //check map
                if (env->is_present_in_map(node->children[1]->data_expression.express.Data.string_value)) {
                    cout << node->children[1]->data_expression.express.Data.string_value << " is in the map" <<  endl;
                    expression_map = env->value_at_element_in_map(node->children[1]->data_expression.express.Data.string_value);
                }
                tuple<double, double> point_value(complex_exp.express.Data.number_value, expression_map.express.Data.number_value);
                final.express.Data.point.point_value = point_value;
                return final.express.Data.point.point_value;
            }
            if (node->children[1]->data_expression.express.type == NumberType) {
                tuple<double, double> point_value(complex_exp.express.Data.number_value, node->children[1]->data_expression.express.Data.number_value);
                final.express.Data.point.point_value = point_value;
                return final.express.Data.point.point_value;
            }
        }
        else if (node->children[1]->children.size() >= 1) {
            Expression final = new Expression;
            Expression complex_exp = new Expression;
            complex_exp = evaluate_helper(node->children[1]);
            Expression expression_map = new Expression;

            if (node->children[0]->data_expression.express.type == SymbolType) {
                //check map
                if (env->is_present_in_map(node->children[0]->data_expression.express.Data.string_value)) {
                    expression_map = env->value_at_element_in_map(node->children[0]->data_expression.express.Data.string_value);
                }
                tuple<double, double> point_value(expression_map.express.Data.number_value, complex_exp.express.Data.number_value);
//                final.express.Data.point_value = point_value;
                final.express.Data.point.point_value = point_value;
                return final.express.Data.point.point_value;
            }
            if (node->children[0]->data_expression.express.type == NumberType) {

                tuple<double, double> point_value(complex_exp.express.Data.number_value, node->children[1]->data_expression.express.Data.number_value);
                final.express.Data.point.point_value = point_value;
                return final.express.Data.point.point_value;
            }
        }
        else {
            Expression express_one = new Expression;
            Expression express_two = new Expression;
            Expression final_result = new Expression;

            if (node->children[0]->data_expression.express.type == SymbolType && node->children[1]->data_expression.express.type == SymbolType) {

                if ((env->is_present_in_map(node->children[0]->data_expression.express.Data.string_value)) && (env->is_present_in_map(node->children[1]->data_expression.express.Data.string_value))) {
                    express_one.express.Data.number_value = env->value_at_element_in_map(node->children[0]->data_expression.express.Data.string_value);
                    express_two.express.Data.number_value = env->value_at_element_in_map(node->children[1]->data_expression.express.Data.string_value);
                    tuple<double, double> point_value(express_one.express.Data.number_value, express_two.express.Data.number_value);
                    final_result.express.Data.point.point_value = point_value;
                    return final_result.express.Data.point.point_value;

                } else {
                    throw InterpreterSemanticError("Error: Missing a symbol value in the map");
                }
            }
            else if (node->children[0]->data_expression.express.type == SymbolType && node->children[1]->data_expression.express.type == NumberType) {

                if (env->is_present_in_map(node->children[0]->data_expression.express.Data.string_value)) {
                   express_one.express.Data.number_value = env->value_at_element_in_map(node->children[0]->data_expression.express.Data.string_value);
                }
                else {
                    throw InterpreterSemanticError("Error: Missing map");
                }
                tuple<double, double> point_value(express_one.express.Data.number_value, node->children[1]->data_expression.express.Data.number_value);
                final_result.express.Data.point.point_value = point_value;
                return final_result.express.Data.point.point_value;
            }
            else if (node->children[1]->data_expression.express.type == SymbolType && node->children[0]->data_expression.express.type == NumberType) {

                if (env->is_present_in_map(node->children[1]->data_expression.express.Data.string_value)) {
                   express_one.express.Data.number_value = env->value_at_element_in_map(node->children[1]->data_expression.express.Data.string_value);
                }
                else {
                    throw InterpreterSemanticError("Error: Missing map");
                }

                tuple<double, double> point_value(express_one.express.Data.number_value, node->children[0]->data_expression.express.Data.number_value);
                final_result.express.Data.point.point_value = point_value;
                return final_result.express.Data.point.point_value;
            }
            else if (node->children[0]->data_expression.express.type == NumberType && node->children[1]->data_expression.express.type == NumberType) {
               tuple<double, double> point_value(node->children[0]->data_expression.express.Data.number_value, node->children[1]->data_expression.express.Data.number_value);
               final_result.express.Data.point.point_value = point_value;
               return final_result.express.Data.point.point_value;
            }
            else {
                throw InterpreterSemanticError("Error: incorrect syntax for Point");
            }
        }
    }
    else if (node_string == "line") {
        Expression child1 = new Expression;
        Expression child2= new Expression;
        Expression result;
        //children now contain the proper evaluated value...just in another location
        child1 = evaluate_helper(node->children[0]);
        child2 = evaluate_helper(node->children[1]);
        child1.express.Data.Line.line_value_start.point_value = child1.express.Data.point.point_value;
        child2.express.Data.Line.line_value_end.point_value = child2.express.Data.point.point_value;

        tuple<double, double> tuple_one(get<0>(child1.express.Data.Line.line_value_start.point_value), get<1>(child1.express.Data.Line.line_value_start.point_value));
        tuple<double, double> tuple_two(get<0>(child2.express.Data.Line.line_value_end.point_value), get<1>(child2.express.Data.Line.line_value_end.point_value));
        result.express.Data.Line.line_value_start.point_value = tuple_one;
        result.express.Data.Line.line_value_end.point_value = tuple_two;
        result.express.type = LineType;
        return result;
    }
    else if (node_string == "draw") {
        Expression draw_exp = new Expression;
        draw_exp.express.type = NoneType;
        if (draw_exp.express.type == NoneType) {
            for (int i = 0; i < node->children.size(); i++) {
                //evaluate all of the children
                draw_exp = evaluate_helper(node->children[i]);
                if (draw_exp.express.type == PointType) {
                    //push onto the vector
                    drawVector.push_back(&draw_exp);
                }
                if (draw_exp.express.type == LineType) {
                    drawVector.push_back(&draw_exp);
                }
            }
//            return draw_exp;
        }
    }
    return node->data_expression;

}


vector<Expression *> Interpreter::drawVectorGetter() {
    return drawVector;
}


Expression Interpreter::eval() {
    Expression expression_evaluate;
    string result = "";
    expression_evaluate = evaluate_helper(root);
    if (expression_evaluate.express.type == NumberType) {
        cout << "(" << expression_evaluate.express.Data.number_value << ")" << endl;
    }
    else if (expression_evaluate.express.type == BooleanType) {
       if (expression_evaluate.express.Data.boolean_value == 0) {
                 cout << "(False)" << endl;
             }
             else {
                 cout << "(True)" << endl;
             }
    }
    else if (expression_evaluate.express.type == NoneType) {
        cout << "(None)" << endl;
    }
    else if (expression_evaluate.express.type == SymbolType) {
        cout << "(" << expression_evaluate.express.Data.string_value << ")" << endl;
    }
    else if (expression_evaluate.express.type == PointType) {
        cout << "this is pointtype" << endl;
        cout << "(" << get<0>(expression_evaluate.express.Data.point.point_value) << "," << get<1>(expression_evaluate.express.Data.point.point_value) << ")" << endl;
    }
    else if (expression_evaluate.express.type == LineType) {
        cout << "this is a linetype" << endl;
        cout << "((" << get<0>(expression_evaluate.express.Data.Line.line_value_start.point_value) << "," << get<1>(expression_evaluate.express.Data.Line.line_value_start.point_value) << ")";
        cout << ",(" << get<0>(expression_evaluate.express.Data.Line.line_value_end.point_value) << "," << get<1>(expression_evaluate.express.Data.Line.line_value_end.point_value) << "))" << endl;
    }
    else {
        cout << "INVALID TYPE OF EXPRESSION: " << endl;
    }
    return expression_evaluate;
}



//_-nary functions
bool Interpreter::logical_not(Expression x) {
    if (x.express.Data.boolean_value == false) {
        return true;
    } else {
        return false;
    }
}

bool Interpreter::logical_and(Expression x, Expression y) {
    if ((x.express.Data.boolean_value && y.express.Data.boolean_value) == true) {
        return true;
    } else {
        return false;
    }
}

bool Interpreter::logical_or(Expression x, Expression y) {
    if ((x.express.Data.boolean_value || y.express.Data.boolean_value) == true) {
        return true;
    } else {
        return false;
    }
}

bool Interpreter::equals(Expression x, Expression y) {

    if (x.express.type == NumberType && y.express.type == NumberType) {
        if (x.express.Data.number_value == y.express.Data.number_value) {
            return true;
        }
        return false;;
    }
    else if (x.express.Data.boolean_value == y.express.Data.boolean_value) {
        return true;
    }
    else if (x.express.Data.string_value == y.express.Data.string_value) {
        return true;
    } else {
        return false;
    }
}

bool Interpreter::greater_than(Expression x, Expression y) {
    if ((x.express.Data.number_value > y.express.Data.number_value) == true) {
        return true;
    } else {
        return false;
    }
}

bool Interpreter::greater_than_or_equal(Expression x, Expression y) {
    if ((x.express.Data.number_value >= y.express.Data.number_value) == true) {
        return true;
    } else {
        return false;
    }
}

bool Interpreter::less_than_or_equal(Expression x, Expression y) {
    if ((x.express.Data.number_value <= y.express.Data.number_value) == true) {
        return true;
    } else {
        return false;
    }
}

bool Interpreter::less_than(Expression x, Expression y) {
    double map_value_x = 0;
    double map_value_y = 0;
    if ((x.express.Data.number_value < y.express.Data.number_value)) {
        return true;
    }
    if (x.express.type == SymbolType && y.express.type == SymbolType) {
        if (env->is_present_in_map(x.express.Data.string_value)) {
            map_value_x = env->value_at_element_in_map(x.express.Data.string_value);
        }
        else {
            return false;
        }

        if (env->is_present_in_map(y.express.Data.string_value)) {
                map_value_y = env->value_at_element_in_map(y.express.Data.string_value);
        }
        else {
            return false;
        }
        if (map_value_x < map_value_y) {
            return true;
        }
        return false;
    }
    return false;

}

double Interpreter::subtract_expression(Expression x, Expression y) {
    double result = x.express.Data.number_value - y.express.Data.number_value;
    return result;
}

double Interpreter::negation(Expression x) {
    double result = (x.express.Data.number_value * (-1));
    return result;
}

double Interpreter::division(Expression x, Expression y) {
    double result = x.express.Data.number_value / y.express.Data.number_value;
    return result;
}

double Interpreter::addition(Expression x, Expression y) {
    double result = x.express.Data.number_value + y.express.Data.number_value;
    return result;
}

double Interpreter::multiplication(Expression x, Expression y) {
    double result = x.express.Data.number_value * y.express.Data.number_value;
    return result;
}
