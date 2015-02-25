#ifndef ASM_EXPR_H
#define ASM_EXPR_H

#include <iostream>
#include <memory>
#include <string>
#include <gcc-plugin.h>
#include <gimple.h>
#include "expression.h"
#include "value.h"
#include "dumper.h"

class AsmExpr : public Expression
{
	public:
		explicit AsmExpr(gimple t);
		void accept(Dumper& h) override;

	private:
		const char* _stmt;

	friend class ActivityGraphDumper;
};

#endif
