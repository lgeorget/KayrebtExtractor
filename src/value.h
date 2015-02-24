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
		uintptr_t getUid() const;

	protected:
		tree _inner;
		uintptr_t _uid;
};

std::ostream& operator<<(std::ostream& out, const Value* v);
#endif
