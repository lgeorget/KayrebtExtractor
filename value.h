#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>

class Value
{
	public:
		explicit Value(tree t);
		virtual std::string print() const;
		bool operator<(const Value& other) const;

	protected:
		tree _inner;
};

std::ostream& operator<<(std::ostream& out, const Value* v);
#endif
