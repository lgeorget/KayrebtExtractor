#ifndef MEM_REF_H
#define MEM_REF_H

#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class MemRef : public Value
{
	public:
		explicit MemRef(tree t);
		std::string print() const override;

	private:
		std::shared_ptr<Value> _ptr;
		const std::string _symbol;
};

#endif
