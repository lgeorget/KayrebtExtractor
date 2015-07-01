/**
 * \file case_label.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a label in a case statement (inside a switch block)
 */
#ifndef CASE_LABEL_H
#define CASE_LABEL_H

#include <iostream>
#include <memory>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"

/**
 * \brief Represent the label of a case inside a switch block
 */
class CaseLabel : public Value
{
	public:
		/**
		 * \brief Construct a new CaseLabel from a TREE CASE LABEL
		 * structure
		 */
		explicit CaseLabel(tree t);
		virtual std::string print() const override;

	private:
		/** The upper bound for the case */
		std::shared_ptr<Value> _highValue;
		/** The lower bound for the case */
		std::shared_ptr<Value> _lowValue;
		/** The actual label to which divert the control flow */
		std::shared_ptr<Value> _label;
		/** A textual representation of the case label for dumping */
		std::string _built_str;

	friend class ActivityGraphDumper;
};

#endif

