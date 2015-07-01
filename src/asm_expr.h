/**
 * \file asm_expr.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of an asm expression
 */
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

/**
 * \brief Represent an asm statement
 */
class AsmExpr : public Expression
{
	public:
		/**
		 * Construct an AsmExpr from a GIMPLE ASM structure
		 */
		explicit AsmExpr(gimple t);
		void accept(Dumper& h) override;

	private:
		std::string _stmt; /*!< The asm statement */

	friend class ActivityGraphDumper;
};

#endif
