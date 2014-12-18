#include <iostream>
#include <memory>
#include <utility>
#include <map>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "value_factory.h"
#include "arith_expr.h"
#include "integer_cst.h"
#include "indirection.h"
#include "string_cst.h"
#include "identifier.h"
#include "ternary_op.h"
#include "modify_expr.h"
#include "cond_expr.h"
#include "negate_op.h"
#include "label.h"

//the instance itself is not const, due to the maps
ValueFactory ValueFactory::INSTANCE;

std::shared_ptr<Value> ValueFactory::build(tree t)
{
	std::map<tree,std::shared_ptr<Value>>::iterator it;
	switch (TREE_CODE(t)) {
		case STRING_CST:
			it = strings.find(t);
			if (it == strings.end())
				it = strings.insert(std::make_pair(t,std::make_shared<StringCst>(StringCst(t)))).first;
			return it->second;

		case INTEGER_CST:
			it = integers.find(t);
			if (it == integers.end())
				it = integers.insert(std::make_pair(t,std::make_shared<IntegerCst>(IntegerCst(t)))).first;
			return it->second;
		case PLUS_EXPR:
		case POINTER_PLUS_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"+"));
		case MINUS_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"-"));
		case MULT_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"*"));
		case MULT_HIGHPART_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"*#"));
		case TRUNC_DIV_EXPR:
		case CEIL_DIV_EXPR:
		case FLOOR_DIV_EXPR:
		case ROUND_DIV_EXPR:
		case RDIV_EXPR:
		case EXACT_DIV_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"/"));
		case TRUNC_MOD_EXPR:
		case CEIL_MOD_EXPR:
		case FLOOR_MOD_EXPR:
		case ROUND_MOD_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"%"));

		case LSHIFT_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"<<"));
                case RSHIFT_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,">>"));
		
		case BIT_IOR_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"|"));
		case BIT_XOR_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"^"));
		case BIT_AND_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"&"));

		case TRUTH_ANDIF_EXPR:
		case TRUTH_AND_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"&&"));
		case TRUTH_ORIF_EXPR:
		case TRUTH_OR_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"||"));
		case TRUTH_XOR_EXPR: //Doesn't exist in C, AFAIR...
			return std::make_shared<ArithExpr>(ArithExpr(t,"^"));
		case LT_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"<"));
		case LE_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"<="));
		case GT_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,">"));
		case GE_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,">="));
		case EQ_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"=="));
		case NE_EXPR:
			return std::make_shared<ArithExpr>(ArithExpr(t,"!="));

		case ADDR_EXPR:
			return std::make_shared<Indirection>(Indirection(t,"&"));

		case INDIRECT_REF:
			return std::make_shared<Indirection>(Indirection(t,"*"));

		case NOP_EXPR: //happens when functions arguments need trivial cast
			return build(TREE_OPERAND(t,0));

		case VAR_DECL:
		case PARM_DECL:
		case RESULT_DECL:
			it = idents.find(t);
			if (it == idents.end())
				it = idents.insert(std::make_pair(t,std::make_shared<Identifier>(Identifier(DECL_NAME(t))))).first;
			return it->second;

		case LABEL_DECL:
			return std::make_shared<Label>(Label(t));

		case BIT_NOT_EXPR:
			return std::make_shared<NegateOp>(NegateOp(t,"~"));
		case NEGATE_EXPR:
			return std::make_shared<NegateOp>(NegateOp(t,"-"));

		case COND_EXPR:
			return std::make_shared<TernaryOp>(TernaryOp(t));

		default:
			return std::make_shared<Value>(Value(t));
	}
}

