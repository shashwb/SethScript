//this is basically the concept of an ATOM
//wrap this into expression

enum VariantType {NoneType, BoolType, IntType, DoubleType}

struct Variant {
	VariantType type;
	bool bool_value;
	int int_value;
	double double_value;
}