#ifndef EXPR_FACTORY_H
#define EXPR_FACTORY_H

#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include <function.h>
#include "expression.h"
#include "bb_list.h"

class ExprFactory
{
	private:
		ExprFactory() = default;
		std::shared_ptr<Expression> _nop;

	public:
		static ExprFactory INSTANCE;
		std::shared_ptr<Expression> build(gimple t);
		std::shared_ptr<BbList> build(function* t);
};

#endif
