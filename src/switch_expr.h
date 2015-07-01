/**
 * \file switch_expr.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a 'switch' branching
 */
#ifndef SWITCH_EXPR_H
#define SWITCH_EXPR_H

#include <iostream>
#include <memory>
#include <vector>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"

class Dumper;

/**
 * \brief Represent a switch-case branching
 */
class SwitchExpr : public Expression
{
	public:
		/**
		 * \brief Construct a new SwitchExpr from a GIMPLE SWITCH
		 * value
		 * \param t the gimple value
		 */
		explicit SwitchExpr(gimple t);
		void accept(Dumper& d) override;

	private:
		/** The variable tested in the switch expression */
		std::shared_ptr<Value> _var;
		/** The labels corresponding to the cases of the switch */
		std::vector<std::shared_ptr<Value>> _labels;

	friend class ActivityGraphDumper;
};

#endif
