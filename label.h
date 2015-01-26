#ifndef LABEL_H
#define LABEL_H

#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class Label : public Value
{
	public:
		explicit Label(tree t);
		virtual std::string print() const;
		//needed for hash maps
		bool operator<(const Label& other) const;

	private:
		uintptr_t _uid;
};

#endif
