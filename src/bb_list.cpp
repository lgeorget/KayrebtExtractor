#include <iostream>
#include <list>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include <gimple.h>
#include <function.h>
#include "expression.h"
#include "bad_gimple_exception.h"
#include "expr_factory.h"
#include "dumper.h"
#include "bb_list.h"

BbList::BbList(function* fn) : _fn(fn)
{
	for (gimple_stmt_iterator it = gsi_start(_fn->gimple_body) ;
			!gsi_end_p(it) ;
			gsi_next(&it)) {
		gimple inner = gsi_stmt(it);
		std::cerr << "new stmt" << std::endl;
		_exprs.push_back(ExprFactory::INSTANCE.build(inner));
	}
}

void BbList::accept(Dumper& d)
{
	d.dumpBbList(this);
}
