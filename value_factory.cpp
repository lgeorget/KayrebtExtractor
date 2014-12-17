#include <iostream>
#include <memory>
#include <utility>
#include <map>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "value_factory.h"
#include "integer_cst.h"
#include "string_cst.h"
#include "identifier.h"
#include "rvalue.h"
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
				it = strings.insert(std::make_pair(t,std::shared_ptr<Value>(new StringCst(t)))).first;
			return it->second;

		case INTEGER_CST:
			it = integers.find(t);
			if (it == integers.end())
				it = integers.insert(std::make_pair(t,std::shared_ptr<Value>(new IntegerCst(t)))).first;
			return it->second;

		case NOP_EXPR:
		case ADDR_EXPR:
			return build(TREE_OPERAND(t,0));
		case VAR_DECL:
		case PARM_DECL:
		case RESULT_DECL:
			it = idents.find(t);
			if (it == idents.end())
				it = idents.insert(std::make_pair(t,std::shared_ptr<Value>(new Identifier(DECL_NAME(t))))).first;
			return it->second;

		case LABEL_DECL:
			return std::shared_ptr<Value>(new Label(t));

		case NEGATE_EXPR:
			return std::shared_ptr<Value>(new NegateOp(t));

		case COND_EXPR:
			return std::shared_ptr<Value>(new TernaryOp(t));

		case MODIFY_EXPR:
			return std::shared_ptr<Value>(new RValue<ModifyExpr>(t));
		default:
			return std::shared_ptr<Value>(new Value(t));
	}
}

