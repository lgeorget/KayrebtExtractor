#ifndef RVALUE_H
#define RVALUE_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "expression.h"
#include "dumper.h"

class Leaf : public Expression
{
	public:
		explicit Leaf(tree t);
		void accept(Dumper& d) override;

	private:
		std::shared_ptr<Value> _val;

	friend class Dumper;
};

#endif
