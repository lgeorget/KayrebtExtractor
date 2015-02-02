#ifndef DEBUG_H
#define DEBUG_H

#include <cassert>

#ifndef NDEBUG
#define assert_tree(t) do {\
	auto my_tree = (t);\
	assert(my_tree && my_tree != NULL_TREE);\
	} while(0)
#else
#define assert_tree(t) (void(0))
#endif

#endif
