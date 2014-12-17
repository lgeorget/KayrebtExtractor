#include <iostream>
#include <list>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include <tree-iterator.h>
#include "expression.h"
#include "bad_tree_exception.h"
#include "expr_factory.h"
#include "dumper.h"
#include "stmt_list.h"

StmtList::StmtList(tree t) : Expression(t)
{
	if (TREE_CODE(t) != STATEMENT_LIST)
		throw BadTreeException(t,"statement_list");

		
	for (tree_stmt_iterator it = tsi_start(t) ;
			!tsi_end_p(it) ;
			tsi_next(&it)) {
		tree inner = tsi_stmt(it);
		_exprs.push_back(ExprFactory::INSTANCE.build(inner));
	}
}

void StmtList::accept(Dumper& d)
{
	d.dumpStmtList(this);
}
