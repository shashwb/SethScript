#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "expression.hpp"
#include "interpreter.hpp"
#include "tokenize.hpp"

using namespace std;




TEST_CASE("Testing the Interpreter's equality", "interpreter.hpp")
{
	Expression left;
	Expression right;
	Expression one_more;
	interpreter inter;
	left.data.type = Expression::NumberType;
	left.data.number_value = 55;
	right.data.type = Expression::NumberType;
	right.data.number_value = 55;
	one_more.data.type = Expression::NumberType;
	one_more.data.number_value = -10;

	REQUIRE(inter.equals(left.data.number_value,
	 right.data.number_value) == true);

	REQUIRE(inter.equals(left.data.number_value,
	 one_more.data.number_value) == false);

}





TEST_CASE("Testing Negation Function", "interpreter.hpp")
{
	Expression express;
	interpreter inter;
	express.data.type = Expression::NumberType;
	express.data.number_value = 50;

	Expression express_negative;
	express_negative.data.type = Expression::NumberType;
	express_negative.data.number_value = -40;

	REQUIRE(inter.negation(express.data.number_value) ==  -50);
	REQUIRE(inter.negation(express) ==  -50);

	REQUIRE(inter.negation(express_negative.data.number_value) ==  40);
	REQUIRE(inter.negation(express_negative) ==  40);



}

TEST_CASE("Testing Less Than and Greater Than functions", "interpreter.hpp")
{
	Expression express_one;
	Expression express_two;
	Expression express_less_equal_one;
	interpreter inter;

	express_one.data.type = Expression::NumberType;
	express_one.data.number_value = 100;

	express_two.data.type = Expression::NumberType;
	express_two.data.number_value = 200.1;

	express_less_equal_one.data.type = Expression::NumberType;
	express_less_equal_one.data.number_value = 100;


	REQUIRE(inter.less_than(express_one.data.number_value,
	 express_two.data.number_value) == true);

	REQUIRE(inter.less_than(express_two.data.number_value,
	 express_one.data.number_value) == false);

	REQUIRE(inter.less_than_or_equal(express_one.data.number_value,
	 express_two.data.number_value) == true);

	REQUIRE(inter.less_than_or_equal(express_two.data.number_value,
	 express_one.data.number_value) == false);

	REQUIRE(inter.less_than_or_equal(express_two.data.number_value,
	 express_two.data.number_value) == true);

	REQUIRE(inter.greater_than(express_two.data.number_value,
	 express_one.data.number_value) == true);

	REQUIRE(inter.greater_than(express_one.data.number_value,
	 express_two.data.number_value) == false);

	REQUIRE(inter.greater_than_or_equal(express_less_equal_one.data.number_value,
	 express_less_equal_one.data.number_value) == true);

	REQUIRE(inter.greater_than_or_equal(express_one.data.number_value,
	 express_less_equal_one.data.number_value) == false);

	REQUIRE(inter.greater_than_or_equal(express_two.data.number_value,
	 express_one.data.number_value) == true);


}


TEST_CASE("SymbolType testing through Constructor", "expression.hpp")
{
	string value = "blahblahblah";
	interpreter inter;
	Expression *express = new Expression(value);
	REQUIRE(express->data.type == Expression::SymbolType);
	REQUIRE(express->data.string_value == value);
}

TEST_CASE("NoneType testing through Constructor", "expression.hpp")
{
	interpreter inter;
	Expression *express = new Expression();
	REQUIRE(express->data.type == Expression::NoneType);
}

TEST_CASE("BooleanType testing through Constructor", "expression.hpp")
{
	bool value = true;
	interpreter inter;
	Expression express = new Expression(value);
	REQUIRE(express.data.type == Expression::BooleanType);
	REQUIRE(inter.equals(express, express));
	REQUIRE(express.data.boolean_value == true);

	bool value_two = false;
	Expression express2 = new Expression(value_two);
	REQUIRE(express2.data.type == Expression::BooleanType);
	REQUIRE(inter.equals(express2, express2));
	REQUIRE(express2.data.boolean_value == true);
}


TEST_CASE("Tesing NumberType methods and constructors", "expression.hpp")
{
	string value = "42";
	interpreter inter;
	Expression express = new Expression(value);
	express.data.number_value = 42;
	express.data.type = Expression::NumberType; 
	REQUIRE(express.data.type == Expression::NumberType);
	REQUIRE(express.data.number_value == 42);

	string value_two = "1050.0";
	Expression express_two = new Expression(value_two);
	express.data.number_value = 1050.0;
	express.data.type = Expression::NumberType;
	REQUIRE(express_two.data.type ==  Expression::NumberType);

	string value_three = "28";
	Expression express_three = new Expression(value_three);
	express_three.data.type = Expression::NumberType;
	REQUIRE(express_three.data.type ==  Expression::NumberType);

	REQUIRE(inter.negation(value) == -42);

}


TEST_CASE("Testing Logical Not and negation", "interpreter.hpp")
{
	bool value = true;
	Expression express = new Expression(value);
	interpreter inter;
	express.data.type = Expression::BooleanType;
	REQUIRE(inter.logical_not(express) == false);

	bool value_two = false;
	Expression express_two = new Expression();
	express_two.data.type = Expression::BooleanType;
	express_two.data.boolean_value = false;
	REQUIRE(inter.logical_not(express_two) == true);

}



//subtract
TEST_CASE("Testing Subtraction", "interpreter.hpp")
{

	interpreter inter;

	Expression bigger;
	Expression smaller;

	Expression negative;
	Expression positive;

	bigger.data.type = Expression::NumberType;
	bigger.data.number_value = 1000;

	smaller.data.type = Expression::NumberType;
	smaller.data.number_value = 2;

	negative.data.type = Expression::NumberType;
	negative.data.number_value = -20;

	positive.data.type = Expression::NumberType;
	positive.data.number_value = 30;


	REQUIRE(inter.subtract_expression(bigger.data.number_value,
	 smaller.data.number_value) == 998);

	REQUIRE(inter.subtract_expression(smaller.data.number_value,
	 bigger.data.number_value) == -998);

	REQUIRE(inter.subtract_expression(positive.data.number_value,
	 negative.data.number_value) == 50.0);

	REQUIRE(inter.subtract_expression(negative.data.number_value,
	 positive.data.number_value) == -50.0);


}

//add
TEST_CASE("Testing Addition", "interpreter.hpp")
{
	interpreter inter;

	Expression bigger;
	Expression smaller;

	Expression negative;
	Expression positive;

	bigger.data.type = Expression::NumberType;
	bigger.data.number_value = 1000;

	smaller.data.type = Expression::NumberType;
	smaller.data.number_value = 2;

	negative.data.type = Expression::NumberType;
	negative.data.number_value = -20;

	positive.data.type = Expression::NumberType;
	positive.data.number_value = 30;


	REQUIRE(inter.addition(bigger.data.number_value,
	 smaller.data.number_value) == 1002);

	REQUIRE(inter.addition(smaller.data.number_value,
	 bigger.data.number_value) == 1002);

	REQUIRE(inter.addition(positive.data.number_value,
	 negative.data.number_value) == 10);

	REQUIRE(inter.addition(negative.data.number_value,
	 negative.data.number_value) == -40);

	REQUIRE(inter.addition(negative.data.number_value,
	 positive.data.number_value) == 10.0);

}

//mutliply
TEST_CASE("Testing division", "interpreter.hpp")
{
	interpreter inter;

	Expression bigger;
	Expression smaller;

	Expression negative;
	Expression positive;

	bigger.data.type = Expression::NumberType;
	bigger.data.number_value = 10;

	smaller.data.type = Expression::NumberType;
	smaller.data.number_value = 2;

	negative.data.type = Expression::NumberType;
	negative.data.number_value = -2;

	positive.data.type = Expression::NumberType;
	positive.data.number_value = 3;


	REQUIRE(inter.multiplication(bigger.data.number_value,
	 smaller.data.number_value) == 20);

	REQUIRE(inter.multiplication(smaller.data.number_value,
	 bigger.data.number_value) == 20);

	REQUIRE(inter.multiplication(positive.data.number_value,
	 negative.data.number_value) == -6);

	REQUIRE(inter.multiplication(negative.data.number_value,
	 negative.data.number_value) == 36);

	REQUIRE(inter.multiplication(negative.data.number_value,
	 positive.data.number_value) == -6);

}


//divide

TEST_CASE("Testing division", "interpreter.hpp")
{
	interpreter inter;

	Expression bigger;
	Expression smaller;

	Expression negative;
	Expression positive;

	bigger.data.type = Expression::NumberType;
	bigger.data.number_value = 10;

	smaller.data.type = Expression::NumberType;
	smaller.data.number_value = 2;

	negative.data.type = Expression::NumberType;
	negative.data.number_value = -2;

	positive.data.type = Expression::NumberType;
	positive.data.number_value = 3;


	REQUIRE(inter.multiplication(bigger.data.number_value,
	 smaller.data.number_value) == 20);

	REQUIRE(inter.multiplication(smaller.data.number_value,
	 bigger.data.number_value) == 20);

	REQUIRE(inter.multiplication(positive.data.number_value,
	 negative.data.number_value) == -6);

	REQUIRE(inter.multiplication(negative.data.number_value,
	 negative.data.number_value) == 36);

	REQUIRE(inter.multiplication(negative.data.number_value,
	 positive.data.number_value) == -6);

}
