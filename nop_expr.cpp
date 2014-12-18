#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "nop_expr.h"
#include "bad_tree_exception.h"
#include "dumper.h"

NopExpr::NopExpr(tree t) : Expression(t)
{}

void NopExpr::accept(Dumper& d)
{
	d.dumpNopExpr(this);
}
