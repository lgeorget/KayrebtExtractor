#ifndef ASM_EXPR_H
#define ASM_EXPR_H

#include <iostream>
#include <memory>
#include <string>
#include <gcc-plugin.h>
#include <gimple.h>
#include "value.h"

class AsmExpr : public Value
{
	public:
		explicit AsmExpr(gimple t);
		std::string print() const override;

	private:
		std::shared_ptr<Value> _stmt;

	friend class TextDumper;
	friend class ActivityGraphDumper;
};

#endif
