#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "expression.hpp"
#include "interpreter.hpp"
#include "tokenize.hpp"

using namespace std;


TEST_CASE("Testing Subtraction", "interpreter.hpp")
{

	Interpreter inter;

	Expression bigger;
	Expression smaller;

	Expression negative;
	Expression positive;

	bigger.express.type = NumberType;
	bigger.express.Data.number_value = 1000;

	smaller.express.type = NumberType;
	smaller.express.Data.number_value = 2;

	negative.express.type = NumberType;
	negative.express.Data.number_value = -20;

	positive.express.type = NumberType;
	positive.express.Data.number_value = 30;

	REQUIRE(inter.subtract_expression(bigger.express.Data.number_value,
	 smaller.express.Data.number_value) == 998);

	REQUIRE(inter.subtract_expression(smaller.express.Data.number_value,
	 bigger.express.Data.number_value) == -998);

	REQUIRE(inter.subtract_expression(positive.express.Data.number_value,
	 negative.express.Data.number_value) == 50.0);

	REQUIRE(inter.subtract_expression(negative.express.Data.number_value,
	 positive.express.Data.number_value) == -50.0);


}

//add
TEST_CASE("Testing Addition", "interpreter.hpp")
{
	Interpreter inter;

	Expression bigger;
	Expression smaller;

	Expression negative;
	Expression positive;

	bigger.express.type = NumberType;
	bigger.express.Data.number_value = 1000;

	smaller.express.type = NumberType;
	smaller.express.Data.number_value = 2;

	negative.express.type = NumberType;
	negative.express.Data.number_value = -20;

	positive.express.type = NumberType;
	positive.express.Data.number_value = 30;


	REQUIRE(inter.addition(bigger.express.Data.number_value,
	 smaller.express.Data.number_value) == 1002);

	REQUIRE(inter.addition(smaller.express.Data.number_value,
	 bigger.express.Data.number_value) == 1002);

	REQUIRE(inter.addition(positive.express.Data.number_value,
	 negative.express.Data.number_value) == 10);

	REQUIRE(inter.addition(negative.express.Data.number_value,
	 negative.express.Data.number_value) == -40);

	REQUIRE(inter.addition(negative.express.Data.number_value,
	 positive.express.Data.number_value) == 10.0);

}

//mutliply
TEST_CASE("Testing multiplication", "interpreter.hpp")
{
	Interpreter inter;

	Expression bigger;
	Expression smaller;

	Expression negative;
	Expression positive;

	bigger.express.type = NumberType;
	bigger.express.Data.number_value = 10;

	smaller.express.type = NumberType;
	smaller.express.Data.number_value = 2;

	negative.express.type = NumberType;
	negative.express.Data.number_value = -2;

	positive.express.type = NumberType;
	positive.express.Data.number_value = 3;


	REQUIRE(inter.multiplication(bigger.express.Data.number_value,
	 smaller.express.Data.number_value) == 20);

	REQUIRE(inter.multiplication(smaller.express.Data.number_value,
	 bigger.express.Data.number_value) == 20);

	REQUIRE(inter.multiplication(positive.express.Data.number_value,
	 negative.express.Data.number_value) == -6);

	REQUIRE(inter.multiplication(negative.express.Data.number_value,
	 negative.express.Data.number_value) == 4.0);

	REQUIRE(inter.multiplication(negative.express.Data.number_value,
	 positive.express.Data.number_value) == -6);

}


//divide

TEST_CASE("Testing division", "interpreter.hpp")
{
	Interpreter inter;

	Expression bigger;
	Expression smaller;

	Expression negative;
	Expression positive;

	bigger.express.type = NumberType;
	bigger.express.Data.number_value = 10;

	smaller.express.type = NumberType;
	smaller.express.Data.number_value = 2;

	negative.express.type = NumberType;
	negative.express.Data.number_value = -2;

	positive.express.type = NumberType;
	positive.express.Data.number_value = 2;


	REQUIRE(inter.division(bigger.express.Data.number_value,
	 smaller.express.Data.number_value) == 5);

	REQUIRE(inter.division(smaller.express.Data.number_value,
	 bigger.express.Data.number_value) == 0.2);

	REQUIRE(inter.division(positive.express.Data.number_value,
	 negative.express.Data.number_value) == -1);

	REQUIRE(inter.division(negative.express.Data.number_value,
	 negative.express.Data.number_value) == 1);

	REQUIRE(inter.division(negative.express.Data.number_value,
	 positive.express.Data.number_value) == -1);

}


TEST_CASE("Testing the Interpreter's equality", "interpreter.hpp")
{
	Expression left;
	Expression right;
	Expression one_more;
	Interpreter inter;
	left.express.type = NumberType;
	left.express.Data.number_value = 55;
	right.express.type = NumberType;
	right.express.Data.number_value = 55;
	one_more.express.type = NumberType;
	one_more.express.Data.number_value = -10;

	REQUIRE(inter.equals(left.express.Data.number_value,
	 right.express.Data.number_value) == true);

	REQUIRE(inter.equals(left.express.Data.number_value,
	 one_more.express.Data.number_value) == true);

}





TEST_CASE("Testing Negation Function", "interpreter.hpp")
{
	Expression express;
	Interpreter inter;
	express.express.type = NumberType;
	express.express.Data.number_value = 50;

	Expression express_negative;
	express_negative.express.type = NumberType;
	express_negative.express.Data.number_value = -40;

	REQUIRE(inter.negation(express.express.Data.number_value) ==  -50);
	REQUIRE(inter.negation(express) ==  -50);

	REQUIRE(inter.negation(express_negative.express.Data.number_value) ==  40);
	REQUIRE(inter.negation(express_negative) ==  40);



}

TEST_CASE("Testing Less Than and Greater Than functions", "interpreter.hpp")
{
	Expression express_one;
	Expression express_two;
	Expression express_less_equal_one;
	Interpreter inter;

	express_one.express.type = NumberType;
	express_one.express.Data.number_value = 100;

	express_two.express.type = NumberType;
	express_two.express.Data.number_value = 200.1;

	express_less_equal_one.express.type = NumberType;
	express_less_equal_one.express.Data.number_value = 100;


	REQUIRE(inter.less_than(express_one.express.Data.number_value,
	 express_two.express.Data.number_value) == true);

	REQUIRE(inter.less_than(express_two.express.Data.number_value,
	 express_one.express.Data.number_value) == false);

	REQUIRE(inter.less_than_or_equal(express_one.express.Data.number_value,
	 express_two.express.Data.number_value) == true);

	REQUIRE(inter.less_than_or_equal(express_two.express.Data.number_value,
	 express_one.express.Data.number_value) == false);

	REQUIRE(inter.less_than_or_equal(express_two.express.Data.number_value,
	 express_two.express.Data.number_value) == true);

	REQUIRE(inter.greater_than(express_two.express.Data.number_value,
	 express_one.express.Data.number_value) == true);

	REQUIRE(inter.greater_than(express_one.express.Data.number_value,
	 express_two.express.Data.number_value) == false);

	REQUIRE(inter.greater_than_or_equal(express_less_equal_one.express.Data.number_value,
	 express_less_equal_one.express.Data.number_value) == true);

	REQUIRE(inter.greater_than_or_equal(express_one.express.Data.number_value,
	 express_less_equal_one.express.Data.number_value) == true);

	REQUIRE(inter.greater_than_or_equal(express_two.express.Data.number_value,
	 express_one.express.Data.number_value) == true);


}


TEST_CASE("SymbolType testing through Constructor", "expression.hpp")
{
	string value = "blahblahblah";
	Interpreter inter;
	Expression *express = new Expression(value);
	REQUIRE(express->express.type == SymbolType);
	REQUIRE(express->express.Data.string_value == value);
}

TEST_CASE("NoneType testing through Constructor", "expression.hpp")
{
	Interpreter inter;
	Expression *express = new Expression();
	REQUIRE(express->express.type == NoneType);
}

TEST_CASE("BooleanType testing through Constructor", "expression.hpp")
{
	bool value = true;
	Interpreter inter;
	Expression express = new Expression(value);
	REQUIRE(express.express.type == BooleanType);
	REQUIRE(inter.equals(express, express));
	REQUIRE(express.express.Data.boolean_value == true);

	bool value_two = false;
	Expression express2 = new Expression(value_two);
	REQUIRE(express2.express.type == BooleanType);
	REQUIRE(inter.equals(express2, express2));
	REQUIRE(express2.express.Data.boolean_value == true);
}


TEST_CASE("Tesing NumberType methods and constructors", "expression.hpp")
{
	string value = "42";
	Interpreter inter;
	Expression express = new Expression(value);
	express.express.Data.number_value = 42;
	express.express.type = NumberType;
	REQUIRE(express.express.type == NumberType);
	REQUIRE(express.express.Data.number_value == 42);

	string value_two = "1050.0";
	Expression express_two = new Expression(value_two);
	express_two.express.Data.number_value = 1050.0;
	express_two.express.type = NumberType;
	REQUIRE(express_two.express.type ==  NumberType);

	string value_three = "28";
	Expression express_three = new Expression(value_three);
	express_three.express.type = NumberType;
	REQUIRE(express_three.express.type ==  NumberType);

	REQUIRE(inter.negation(express_two) == -1050.0);

}


TEST_CASE("Testing Logical Not and negation", "interpreter.hpp")
{
	bool value = true;
	Expression express = new Expression(value);
	Interpreter inter;
	express.express.type = BooleanType;
	REQUIRE(inter.logical_not(express) == false);

	bool value_two = false;
	Expression express_two = new Expression();
	express_two.express.type = BooleanType;
	express_two.express.Data.boolean_value = false;
	REQUIRE(inter.logical_not(express_two) == true);

}
