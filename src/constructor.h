#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class Constructor : public Value
{
	public:
		explicit Constructor(tree t);
		std::string print() const override;

	private:
		std::vector<std::shared_ptr<Value>> _fields;
		std::string _built_str;
};

#endif
