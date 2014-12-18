#ifndef ARRAY_REF_H
#define ARRAY_REF_H

#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class ArrayRef : public Value
{
	public:
		explicit ArrayRef(tree t);
		std::string print() const override;

	private:
		std::shared_ptr<Value> _array;
		std::shared_ptr<Value> _index;
};

#endif
