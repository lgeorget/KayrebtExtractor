/**
 * \file operator.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the static class Operator
 */
#include <cstdlib>
#include <gcc-plugin.h>
#include <tree.h>
#include <stdexcept>
#include "operator.h"

const std::string& Operator::print(tree_code op)
{
	try {
		return symbols.at(op);
	} catch (std::out_of_range& e) {
		std::cerr << " Unknown expression or operator " << TREE_CODE_CLASS_STRING(op) << std::endl;
		return symbols.at(LAST_AND_UNUSED_TREE_CODE);
	}
}

const std::map<tree_code,std::string> Operator::symbols =
{
	{ PLUS_EXPR, 		" + " },
	{ MINUS_EXPR, 		" - " },
	{ MULT_EXPR,		" * " },
	{ POINTER_PLUS_EXPR,	" + " },
	{ MULT_HIGHPART_EXPR,	" * " },
	{ TRUNC_DIV_EXPR,	" / " },
	{ CEIL_DIV_EXPR,	" / " },
	{ FLOOR_DIV_EXPR,	" / " },
	{ ROUND_DIV_EXPR,	" / " },
	{ TRUNC_MOD_EXPR,	" % " },
	{ CEIL_MOD_EXPR,	" % " },
	{ FLOOR_MOD_EXPR,	" % " },
	{ ROUND_MOD_EXPR,	" % " },
	{ RDIV_EXPR,		" / " },
	{ EXACT_DIV_EXPR,	" / " },
	{ NEGATE_EXPR,		" - " },
	{ LSHIFT_EXPR,		" << " },
	{ RSHIFT_EXPR,		" >> " },
	{ BIT_IOR_EXPR,		" | " },
	{ BIT_XOR_EXPR,		" ^ " },
	{ BIT_AND_EXPR,		" & " },
	{ BIT_NOT_EXPR,		" ~ " },
	{ TRUTH_ANDIF_EXPR,	" && " },
	{ TRUTH_ORIF_EXPR,	" || " },
	{ TRUTH_AND_EXPR,	" && " },
	{ TRUTH_OR_EXPR,	" || " },
	{ TRUTH_NOT_EXPR,	" ! " },
	{ LT_EXPR,		" < " },
	{ LE_EXPR,		" <= " },
	{ GT_EXPR,		" > " },
	{ GE_EXPR,		" >= " },
	{ EQ_EXPR,		" == " },
	{ NE_EXPR,		" != " },
	{ COMPONENT_REF,	" . " },
	{ BIT_FIELD_REF,	" . " },
	{ MIN_EXPR,		" `min` " },
	{ MAX_EXPR,		" `max` " },
	{ LAST_AND_UNUSED_TREE_CODE,	" `op` "}
};

