#ifndef EXPR_FACTORY_H
#define EXPR_FACTORY_H

#include <memory>
#include <gcc-plugin.h>
#include "expression.h"

class ExprFactory
{
	private:
		ExprFactory() = default;

	public:
		static const ExprFactory INSTANCE;
		std::shared_ptr<Expression> build(tree t) const;
};

#endif
