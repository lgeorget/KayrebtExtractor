#ifndef EXPR_FACTORY_H
#define EXPR_FACTORY_H

#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"

class ExprFactory
{
	private:
		ExprFactory() = default;
		std::shared_ptr<Expression> _nop;

	public:
		static ExprFactory INSTANCE;
		std::shared_ptr<Expression> build(gimple t);
		std::shared_ptr<Expression> build(basic_block t);
};

#endif
