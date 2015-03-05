/**
 * \file debug.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of macros useful for debugging
 */
#ifndef DEBUG_H
#define DEBUG_H

#include <cassert>

#ifndef NDEBUG
/**
 * \brief Assert that a tree does exist
 * \param t the tree
 */
#define assert_tree(t) do {\
	auto my_tree = (t);\
	assert(my_tree && my_tree != NULL_TREE);\
	} while(0)
#else
#define assert_tree(t) (void(0))
#endif

#endif
