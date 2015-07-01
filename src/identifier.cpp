/**
 * \file identifier.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the Identifier
 */
#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"
#include "identifier.h"
#include "bad_tree_exception.h"

unsigned int Identifier::counter = 1;

Identifier::Identifier(tree t) : Value(t)
{
	if (t && TREE_CODE(t) != IDENTIFIER_NODE)
		throw BadTreeException(t,"decl_name");

	if (t && t != NULL_TREE)
		_name = IDENTIFIER_POINTER(t);
	else
		_name = "<" + std::to_string(counter++) + ">";
}

std::string Identifier::print() const
{
	return _name;
}

