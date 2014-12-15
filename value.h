#ifndef VALUE_H
#define VALUE_H

#include <iostream>

class Value
{
	public:
		Value() = default;
		virtual std::string print() const;
};

std::ostream& operator<<(std::ostream& out, const Value* v);
#endif
