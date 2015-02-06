#ifndef UNARY_H
#define UNARY_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class Unary : public Value
{
	public:
		explicit Unary(tree t, const std::string& symbol);
		std::string print() const override;

	private:
		std::shared_ptr<Value> _inside;
		const std::string _symbol;
};

#endif
