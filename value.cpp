#include <iostream>
#include <string>
#include "value.h"

std::string Value::print() const
{
	return "Uninitialized value";
}

std::ostream& operator<<(std::ostream& out, const Value* v)
{
	out << v->print();
	return out;
}
