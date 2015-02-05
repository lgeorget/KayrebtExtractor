#include <gcc-plugin.h>
#include <tree.h>
#include "operator.h"

const std::string& Operator::print(tree_code op)
{
	return symbols[op];
}
