#ifndef ASM_EXPR_H
#define ASM_EXPR_H

#include <iostream>
#include <memory>
#include <string>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class AsmExpr : public Value
{
	public:
		explicit AsmExpr(tree t);
		std::string print() const override;

	private:
		std::shared_ptr<Value> _stmt;

	friend class TextDumper;
	friend class ActivityGraphDumper;
};

#endif
