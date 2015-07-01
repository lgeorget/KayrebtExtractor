/**
 * \file goto_expr.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of an unconditional branching
 */
#ifndef GOTO_EXPR_H
#define GOTO_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"
#include "label.h"

/**
 * \brief Represent a goto statement
 */
class GotoExpr : public Expression
{
	public:
		/**
		 * \brief Construct a new GotoExpr from a GIMPLE GOTO expression
		 * \param t the gimple goto expression
		 */
		explicit GotoExpr(gimple t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		/** The destination of the branching */
		std::shared_ptr<Value> _label;
		// that probably supports computed gotos as well

	friend class ActivityGraphDumper;
};

#endif
