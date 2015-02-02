#include <exception>
#include <stdexcept>
#include "bad_tree_exception.h"

BadTreeException::BadTreeException(tree got, const char* expected) :
	std::domain_error(std::string("Got ") + tree_code_name[TREE_CODE(got)] + std::string(" while we were expecting ") + expected)
{}

BadTreeException::BadTreeException(tree got, tree expected) :
	BadTreeException(got, tree_code_name[TREE_CODE(expected)])
{}


