#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <map>
#include <gcc-plugin.h>
#include <tree.h>

class Operator
{
	public:
		static const std::string& print(tree_code op);

	private:
		Operator() = default;
		const static std::map<tree_code,std::string> symbols =
		{
			{ PLUS_EXPR, 		"+" },
			{ MINUS_EXPR, 		"-" },
			{ MULT_EXPR,		"*" },
			{ POINTER_PLUS_EXPR,	"+" },
			{ MULT_HIGHPART_EXPR,	"*" },
			{ TRUNC_DIV_EXPR,	"/" },
			{ CEIL_DIV_EXPR,	"/" },
			{ FLOOR_DIV_EXPR,	"/" },
			{ ROUND_DIV_EXPR,	"/" },
			{ TRUNC_MOD_EXPR,	"%" },
			{ CEIL_MOD_EXPR,	"%" },
			{ FLOOR_MOD_EXPR,	"%" },
			{ ROUND_MOD_EXPR,	"%" },
			{ RDIV_EXPR,		"/" },
			{ EXACT_DIV_EXPR,	"/" },
			{ NEGATE_EXPR,		"-" },
			{ LSHIFT_EXPR,		"<<" },
			{ RSHIFT_EXPR,		">>" },
			{ BIT_IOR_EXPR,		"|" },
			{ BIT_XOR_EXPR		"^" },
			{ BIT_AND_EXPR		"&" },
			{ BIT_NOT_EXPR		"~" },
			{ TRUTH_ANDIF_EXPR,	"&&" },
			{ TRUTH_ORIF_EXPR,	"||" },
			{ TRUTH_AND_EXPR	"&&" },
			{ TRUTH_OR_EXPR		"||" },
			{ TRUTH_NOT_EXPR	"!" },
			{ LT_EXPR,		"<" },
			{ LE_EXPR,		"<=" },
			{ GT_EXPR,		">" },
			{ GE_EXPR,		">=" },
			{ EQ_EXPR,		"==" },
			{ NE_EXPR,		"!=" }
		};
};

#endif
