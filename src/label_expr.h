/**
 * \file label_expr.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a label declaration
 */
#ifndef LABEL_EXPR_H
#define LABEL_EXPR_H

#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"

/**
 * \brief Represent a label declaration in a program
 */
class LabelExpr : public Expression
{
	public:
		/**
		 * \brief Construct a new label from a GCC GIMPLE
		 * \param t the gimple value
		 */
		explicit LabelExpr(gimple t);
		virtual void accept(Dumper& d); // Visitor design pattern

	private:
		/** The actual label inside the label declaration */
		std::shared_ptr<Value> _label;

	friend class ActivityGraphDumper;
};

#endif
