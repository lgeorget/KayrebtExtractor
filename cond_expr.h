#ifndef COND_EXPR_H
#define COND_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"

class Dumper;

class CondExpr : public Expression
{
	public:
		explicit CondExpr(tree t);
		void accept(Dumper& d) override;

	private:
		std::shared_ptr<Expression> _cond;
		std::shared_ptr<Expression> _then;
		std::shared_ptr<Expression> _else;

	friend std::ostream& operator<<(std::ostream& out, const CondExpr& e);
	friend class TextDumper;	friend class ActivityGraphDumper;
};

#endif
