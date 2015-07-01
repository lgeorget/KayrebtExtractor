/**
 * \file return_expr.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a return expression
 */
#ifndef RETURN_EXPR_H
#define RETURN_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"

/**
 * \brief Represent a return statement, with or without a value
 */
class ReturnExpr : public Expression
{
	public:
		/**
		 * \brief Construct a new ReturnExpr from a GCC GIMPLE RETURN
		 * value
		 * \param t the gimple value
		 */
		explicit ReturnExpr(gimple t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		/** The value returned, if any */
		std::shared_ptr<Value> _value;

	friend class ActivityGraphDumper;
};

#endif
