/**
 * \file assign_expr.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of the assignment expression
 */
#ifndef ASSIGN_EXPR_H
#define ASSIGN_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"

/**
 * \brief Represent an assignment statement
 */
class AssignExpr : public Expression
{
	public:
		/**
		 * Construct an AssignExpr from a GIMPLE ASSIGN structure
		 */
		explicit AssignExpr(gimple t);
		virtual void accept(Dumper& d); // Visitor design pattern

	protected:
		std::shared_ptr<Value> 	_whatToSet; /*!< The varirable assigned */
		tree_code		_op; /*!< The operation in the right-hand value */
		std::shared_ptr<Value>	_rhs1; /*!< The first operand */
		std::shared_ptr<Value>	_rhs2; /*!< The second operand */
		bool _anonymous; /*!< Whether the variable is a temporary */

	friend class ActivityGraphDumper;
};

#endif
