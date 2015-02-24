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
#include "function_body.h"

FunctionBody::FunctionBody(function* fn) : _fn(fn)
{
	std::cerr << "Building function body" << std::endl;
	basic_block bb;
	FOR_EACH_BB_FN(bb, fn)
	{
		std::cerr << "Entering basic block" << std::endl;
		std::vector<std::shared_ptr<Expression>> stmts;
		for (gimple_stmt_iterator it = gsi_start_bb(bb) ;
				!gsi_end_p(it) ;
				gsi_next(&it)) {
			std::cerr << "Next expression" << std::endl;
			gimple inner = gsi_stmt(it);
			stmts.push_back(ExprFactory::INSTANCE.build(inner));
		}
		_bb.emplace_back(bb,stmts);
	}
}

void FunctionBody::accept(Dumper& d)
{
	d.dumpFunctionBody(this);
}
