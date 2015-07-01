/**
 * \file call_expr.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a function calling statement
 */
#ifndef CALL_EXPR_H
#define CALL_EXPR_H

#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"
#include "dumper.h"

/**
 * \brief Represent a function calling statement
 */
class CallExpr : public Expression
{
	public:
		/**
		 * \brief Build a new function calling expression from
		 * a GIMPLE CALL strcuture
		 */
		explicit CallExpr(gimple t);
		void accept(Dumper& d) override;

	private:
		/** Number of arguments of the function */
		unsigned int _nbArgs;
		/** Variable the returned value from the function is assigned to */
		std::shared_ptr<Value> _var;
		/** Name of the function */
		std::shared_ptr<Value> _name;
		/** Arguments of the function */
		std::list<std::shared_ptr<Value>> _args;
		/** String representing the function for dumping purpose */
		std::string _built_str;

	friend class ActivityGraphDumper;
};

#endif
