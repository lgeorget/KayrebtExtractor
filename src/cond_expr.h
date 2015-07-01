/**
 * \file cond_expr.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a conditional branching
 */
#ifndef COND_EXPR_H
#define COND_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"

class Dumper;

/**
 * \brief Represent a condition and its branchings
 */
class CondExpr : public Expression
{
	public:
		/**
		 * Construct a new CondExpr from a GIMPLE COND value
		 * \param t the GIMPLE COND value
		 */
		explicit CondExpr(gimple t);
		void accept(Dumper& d) override;

	private:
		/** The first operand in the boolean operation used as condition */
		std::shared_ptr<Value> _lhs;
		/** The second operand in the boolean operation used as condition */
		std::shared_ptr<Value> _rhs;
		/** The boolean operation in the condition */
		tree_code		_op;
		/** The label of the 'true' branch */
		std::shared_ptr<Value> _then;
		/** The label of the 'false' branch */
		std::shared_ptr<Value> _else;

	friend class ActivityGraphDumper;
};

#endif
