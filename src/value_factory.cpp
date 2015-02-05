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
#include "label.h"

//the instance itself is not const, because of the maps
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

		case NOP_EXPR: //happens when functions arguments need trivial cast
		case CONVERT_EXPR:
			return build(TREE_OPERAND(t,0));

		case VAR_DECL:
		case PARM_DECL:
		case RESULT_DECL:
		case FIELD_DECL:
		case FUNCTION_DECL:
			it = idents.find(t);
			if (it == idents.end())
				it = idents.insert(std::make_pair(t,std::make_shared<Identifier>(Identifier(DECL_NAME(t))))).first;
			return it->second;

		case LABEL_DECL:
			return std::make_shared<Label>(Label(t));

		default:
			return std::make_shared<Value>(Value(t));
	}
}

