#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class Identifier : public Value
{
	public:
		explicit Identifier(tree t);
		std::string print() const override;

	private:
		std::string _name;
};

#endif
