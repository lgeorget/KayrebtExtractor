#ifndef CASE_LABEL_H
#define CASE_LABEL_H

#include <iostream>
#include <memory>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "expression.h"
#include "value.h"

class CaseLabel : public Value
{
	public:
		explicit CaseLabel(tree t);
		virtual std::string print() const override;

	private:
		std::shared_ptr<Value> _highValue;
		std::shared_ptr<Value> _lowValue;
		std::shared_ptr<Value> _label;
		std::string _built_str;

	friend class TextDumper;
	friend class ActivityGraphDumper;
};

#endif

