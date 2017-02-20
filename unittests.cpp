#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "expression.hpp"
#include "interpreter.hpp"
#include "tokenize.hpp"

using namespace std;

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
	std::string value_one = "True";
	interpreter inter;
	Expression express = new Expression(value_one);
	REQUIRE(express.data.type == Expression::BooleanType);
	REQUIRE(inter.equals(express, express));
	REQUIRE(express.data.boolean_value == true);

	string value_two = "False";
	Expression express2 = new Expression(value_two);
	REQUIRE(express2.data.type == Expression::BooleanType);
	REQUIRE(inter.equals(express2, express2));
	REQUIRE(express2.data.boolean_value == false);
}



// TEST_CASE("Test Bool Constructor - False", "expression.hpp")
// {
// 	//we pass in a string but our expression should be able to 
// 	//know that it is a boolean...
// 	std::string value = "False";
// 	interpreter inter;
// 	Expression express = new Expression(value);

// 	REQUIRE(express.data.type == Expression::BooleanType);
// 	REQUIRE(express.data.boolean_value == false);
// }

// TEST_CASE("Test Number Constructor - 250", "expression.hpp")
// {
// 	std::string value = "250";
// 	Interpreter I;
// 	Expression exp = I.expChooser(value);

// 	REQUIRE(exp.Atom.type == Expression::DoubleType);
// 	REQUIRE(exp.Atom.DoubleValue == 250);
// }

// TEST_CASE("Test Number Constructor - 1.0053", "expression.hpp")
// {
// 	std::string value = "1.0053";
// 	Interpreter I;
// 	Expression exp = I.expChooser(value);

// 	REQUIRE(exp.Atom.type == Expression::DoubleType);
// 	REQUIRE(exp.Atom.DoubleValue == 1.0053);
// }

// TEST_CASE("Test Not Function", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::BoolType;
// 	lhs.Atom.BoolValue = true;

// 	REQUIRE(I.NotFunc(lhs) == (!lhs.Atom.BoolValue));

// }

// TEST_CASE("Test lessThanFunc Function - 1", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 5;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 3;

// 	REQUIRE(I.lessThanFunc(lhs,rhs) == false);

// }

// TEST_CASE("Test lessThanFunc Function - 2", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 3;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 5;

// 	REQUIRE(I.lessThanFunc(lhs,rhs) == true);

// }


// TEST_CASE("Test lessThanEqFunc Function - 1", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 5;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 3;

// 	REQUIRE(I.lessThanEqFunc(lhs,rhs) == false);

// }

// TEST_CASE("Test lessThanEqFunc Function - 2", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 4;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 4;

// 	REQUIRE(I.lessThanEqFunc(lhs,rhs) == true);

// }

// TEST_CASE("Test lessThanEqFunc Function - 3", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 6;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 20;

// 	REQUIRE(I.lessThanEqFunc(lhs,rhs) == true);

// }



// TEST_CASE("Test greaterThanFunc Function - 1", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 6;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 20;

// 	REQUIRE(I.greaterThanFunc(lhs,rhs) == false);

// }

// TEST_CASE("Test greaterThanFunc Function - 2", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 20;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 6;

// 	REQUIRE(I.greaterThanFunc(lhs,rhs) == true);

// }

// TEST_CASE("Test greaterThanEqFunc Function - 1", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 10;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 10;

// 	REQUIRE(I.greaterThanEqFunc(lhs,rhs) == true);

// }

// TEST_CASE("Test greaterThanEqFunc Function - 2", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 20;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 10;

// 	REQUIRE(I.greaterThanEqFunc(lhs,rhs) == true);

// }

// TEST_CASE("Test greaterThanEqFunc Function - 3", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 10;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 20;

// 	REQUIRE(I.greaterThanEqFunc(lhs,rhs) == false);

// }


// TEST_CASE("Test equalityFunc Function - 1", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 10;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 10;

// 	REQUIRE(I.equalityFunc(lhs,rhs) == true);

// }

// TEST_CASE("Test equalityFunc Function - 2", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 10;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 50;

// 	REQUIRE(I.equalityFunc(lhs,rhs) == false);

// }


// TEST_CASE("Test equalityFunc Function - 3", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 50;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 10;

// 	REQUIRE(I.equalityFunc(lhs,rhs) == false);

// }

// TEST_CASE("Test negateFunc Function - 1", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 50;

// 	REQUIRE(I.negateFunc(lhs) ==  -50);

// }

// TEST_CASE("Test minusFunc Function - 1", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 50;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 10;

// 	REQUIRE(I.minusFunc(lhs,rhs) == 40);

// }


// TEST_CASE("Test minusFunc Function - 2", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 10;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 50;

// 	REQUIRE(I.minusFunc(lhs,rhs) == -40);

// }

// TEST_CASE("Test minusFunc Function - 3", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 50;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 50;

// 	REQUIRE(I.minusFunc(lhs,rhs) == 0);

// }

// TEST_CASE("Test divideFunc Function - 1", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 50;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 50;

// 	REQUIRE(I.divideFunc(lhs,rhs) == 1);

// }

// TEST_CASE("Test divideFunc Function - 2", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 100;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 4;

// 	REQUIRE(I.divideFunc(lhs,rhs) == 25);

// }

// TEST_CASE("Test divideFunc Function - 3", "interpreter.hpp")
// {
// 	Expression lhs;
// 	Expression rhs;
// 	Interpreter I;
// 	lhs.Atom.type = Expression::DoubleType;
// 	lhs.Atom.DoubleValue = 153;
// 	rhs.Atom.type = Expression::DoubleType;
// 	rhs.Atom.DoubleValue = 6;

// 	REQUIRE(I.divideFunc(lhs,rhs) == 25.5);

// }

// TEST_CASE("Test Token cleaner", "tokenizer.hpp")
// {
// 	Tokenizer T;
// 	std::string value = "(begin)";

// 	REQUIRE(T.inputCleaner(value) == "( begin )");
// }