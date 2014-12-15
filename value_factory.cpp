#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "value_factory.h"
#include "integer_cst.h"
#include "string_cst.h"

const ValueFactory ValueFactory::INSTANCE;

std::shared_ptr<Value> ValueFactory::build(tree t) const
{
	switch (TREE_CODE(t)) {
		case STRING_CST:
			return std::shared_ptr<Value>(new StringCst(t));
		case INTEGER_CST:
			return std::shared_ptr<Value>(new IntegerCst(t));
		default:
			return std::shared_ptr<Value>(new Value());
	}
}

