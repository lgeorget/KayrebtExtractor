#ifndef BAD_TREE_EXCEPTION_H
#define BAD_TREE_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <gcc-plugin.h>
#include <tree.h>

class BadTreeException : public std::domain_error
{
	public:
		BadTreeException(tree got, const char* expected);
};

#endif
