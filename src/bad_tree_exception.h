/**
 * \file bad_tree_exception.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a runtime exception indicating that another tree
 * structure was expected at some point
 */
#ifndef BAD_TREE_EXCEPTION_H
#define BAD_TREE_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <gcc-plugin.h>
#include <tree.h>

/**
 * \brief Represent a kind of caught error in the control flow: the wrong
 * tree value was supplied to some constructor
 */
class BadTreeException : public std::domain_error
{
	public:
		/**
		 * \brief Construct a new BadTreeExpression explaining
		 * which tree value was seen and which was expected
		 * \param got the tree value caught
		 * \param expected the expected tree value name
		 */
		BadTreeException(tree got, const char* expected);
};

#endif
