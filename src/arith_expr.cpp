#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "arith_expr.h"
#include "value.h"
#include "value_factory.h"
#include "dumper.h"
#include "bad_tree_exception.h"

ArithExpr::ArithExpr(tree t, std::string op) : Value(t), _op(op)
{
	if (TREE_CODE(t) != COMPOUND_EXPR
	    && !(TREE_CODE(t) >= TRUTH_ANDIF_EXPR &&
	    TREE_CODE(t) <= TRUTH_XOR_EXPR)
	    && !(TREE_CODE(t) >= PLUS_EXPR &&
		 TREE_CODE(t) <= EXACT_DIV_EXPR)
	    && !(TREE_CODE(t) >= LT_EXPR &&
		 TREE_CODE(t) <= NE_EXPR)
	    && !(TREE_CODE(t) >= LSHIFT_EXPR &&
		 TREE_CODE(t) <= RSHIFT_EXPR)
	    && !(TREE_CODE(t) >= BIT_IOR_EXPR &&
		 TREE_CODE(t) <= BIT_AND_EXPR))
		throw BadTreeException(t,
			"one of : COMPOUND_EXPR, "
				 "TRUTH_ANDIF_EXPR, "
				 "TRUTH_ORIF_EXPR, "
				 "TRUTH_AND_EXPR, "
				 "TRUTH_OR_EXPR, "
				 "TRUTH_XOR_EXPR, "

				 "LSHIFT_EXPR, "
				 "RSHIFT_EXPR, "
				 "BIT_IOR_EXPR, "
				 "BIT_XOR_EXPR, "
				 "BIT_AND_EXPR, "
/* Simple arithmetic.  */
				 "PLUS_EXPR, "
				 "MINUS_EXPR, "
				 "MULT_EXPR, "
/* Pointer addition.  The first operand is always a pointer and the
   second operand is an integer of type sizetype.  */
				 "POINTER_PLUS_EXPR, "
/* Highpart multiplication.  For an integral type with precision B,
   returns bits [2B-1, B] of the full 2*B product.  */
				 "MULT_HIGHPART_EXPR, "
/* Division for integer result that rounds the quotient toward zero.  */
				 "TRUNC_DIV_EXPR, "
/* Division for integer result that rounds the quotient toward infinity.  */
				 "CEIL_DIV_EXPR, "
/* Division for integer result that rounds toward minus infinity.  */
				 "FLOOR_DIV_EXPR, "
/* Division for integer result that rounds toward nearest integer.  */
				 "ROUND_DIV_EXPR, "
/* Four kinds of remainder that go with the four kinds of division.  */
				 "TRUNC_MOD_EXPR, "
				 "CEIL_MOD_EXPR, "
				 "FLOOR_MOD_EXPR, "
				 "ROUND_MOD_EXPR, "
/* Division for real result.  */
				 "RDIV_EXPR, "
				 "EXACT_DIV_EXPR, "
				 "LT_TREE, "
				 "LE_TREE, "
				 "GT_TREE, "
				 "GE_TREE, "
				 "EQ_TREE, "
				 "NE_TREE"
				 );

	_opl = ValueFactory::INSTANCE.build(TREE_OPERAND(t,0));
	_opr = ValueFactory::INSTANCE.build(TREE_OPERAND(t,1));
}

std::string ArithExpr::print() const
{
	return "(" + _opl->print() + ") " + _op + " (" + _opr->print() +")";
}
