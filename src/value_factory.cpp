/**
 * \file value_factory.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the singleton ValueFactory
 */
#include <iostream>
#include <memory>
#include <utility>
#include <map>
#include <gcc-plugin.h>
#include <tree.h>
#include "array_ref.h"
#include "component_ref.h"
#include "constructor.h"
#include "mem_ref.h"
#include "value.h"
#include "value_factory.h"
#include "integer_cst.h"
#include "string_cst.h"
#include "identifier.h"
#include "label.h"
#include "case_label.h"
#include "unary.h"
#include "ssa_name.h"

//the instance itself is not const, because of the maps
ValueFactory ValueFactory::INSTANCE;

std::shared_ptr<Value> ValueFactory::build(tree t)
{
	std::map<tree,std::shared_ptr<Value>>::iterator it;
	if (!t || t == NULL_TREE)
		return std::shared_ptr<Value>();

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
		case VIEW_CONVERT_EXPR:
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

		case SSA_NAME:
			it = ssas.find(t);
			if (it == ssas.end())
				it = ssas.insert(std::make_pair(t,std::make_shared<SsaName>(SsaName(t)))).first;
			return it->second;

		case IDENTIFIER_NODE:
			it = idents.find(t);
			if (it == idents.end())
				it = idents.insert(std::make_pair(t,std::make_shared<Identifier>(Identifier(t)))).first;
			return it->second;

		case LABEL_DECL:
			return std::make_shared<Label>(Label(t));

		case CASE_LABEL_EXPR:
			return std::make_shared<CaseLabel>(CaseLabel(t));

		case ADDR_EXPR:
			return std::make_shared<Unary>(Unary(t,"&"));

		case INDIRECT_REF:
			return std::make_shared<Unary>(Unary(t,"*"));

		case ARRAY_REF:
			return std::make_shared<ArrayRef>(ArrayRef(t));

		case BIT_NOT_EXPR:
			return std::make_shared<Unary>(Unary(t,"~"));

		case NEGATE_EXPR:
			return std::make_shared<Unary>(Unary(t,"-"));

		case COMPONENT_REF:
			return std::make_shared<ComponentRef>(ComponentRef(t, "."));

		case CONSTRUCTOR:
			return std::make_shared<Constructor>(Constructor(t));

		case MEM_REF:
			return std::make_shared<MemRef>(MemRef(t));

		case TARGET_MEM_REF:
			return std::make_shared<MemRef>(MemRef(t));

		default:
#ifndef NDEBUG
			std::cerr << "Building " << tree_code_name[TREE_CODE(t)] << std::endl;
#endif
			return std::make_shared<Value>(Value(t));
	}
}

