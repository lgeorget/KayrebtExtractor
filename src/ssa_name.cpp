/**
 * \file ssa_name.cpp
 * \author Laurent Georget
 * \date 2015-11-16
 * \brief Implementation of the SsaName
 */
#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "ssa_name.h"
#include "bad_tree_exception.h"

unsigned int SsaName::counter = 1;

SsaName::SsaName(tree t) : Value(t)
{
	if (t && TREE_CODE(t) != SSA_NAME)
		throw BadTreeException(t,"ssa_name");

	tree ident = SSA_NAME_IDENTIFIER(t);

	if (ident && ident != NULL_TREE && TREE_CODE(ident) == IDENTIFIER_NODE)
		_name = IDENTIFIER_POINTER(ident);
	else
		_name = "<ssa " + std::to_string(counter++) + ">";
}

std::string SsaName::print() const
{
	return _name;
}

