/**
 * \file bad_tree_exception.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the BadTreeException
 */
#include <exception>
#include <stdexcept>
#include <gcc-plugin.h>
#include <tree.h>
#include "bad_tree_exception.h"

BadTreeException::BadTreeException(tree got, const char* expected) :
	std::domain_error(std::string("Got ") + tree_code_name[TREE_CODE(got)] + std::string(" while we were expecting ") + expected)
{}
