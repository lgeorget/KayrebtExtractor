#include <iostream>
#include <sstream>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "expression.h"
#include "dumper.h"
#include "leaf.h"
#include "value_factory.h"

Leaf::Leaf(tree t) : Expression(t)
{
	_val = ValueFactory::INSTANCE.build(t);
}

void Leaf::accept(Dumper& d)
{
	d.dumpLeaf(this);
}

