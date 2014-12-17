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

	private:
		uintptr_t _uid;
};

#endif
