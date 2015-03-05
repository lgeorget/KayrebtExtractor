/**
 * \file nop_expr.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a no-op expression
 */
#ifndef NOP_EXPR_H
#define NOP_EXPR_H

#include <iostream>
#include <memory>
#include <list>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"

/**
 * \brief Represent a no-op statement (for example, a cast without effect)
 */
class NopExpr : public Expression
{
	public:
		/**
		 * \brief Construct a NopExpr from a GCC GIMPLE statements
		 *
		 * GIMPLE statements causing the creation of NopExpr are typically
		 * PREDICT expressions.
		 * \param t the gimple value
		 */
		explicit NopExpr(gimple t);
		void accept(Dumper& d) override;

	friend class ActivityGraphDumper;
};

#endif
