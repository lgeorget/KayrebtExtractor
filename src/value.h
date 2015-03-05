/**
 * \file value.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of an abstract value
 */
#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>

/**
 * \brief Represent any kind of value in a program, i.e. something on which
 * an operation can be done, something that can be used as a parameter or a
 * return value...
 */
class Value
{
	public:
		/**
		 * \brief Construct a new Value from a GCC TREE value
		 * \param t the tree
		 */
		explicit Value(tree t);
		/**
		 * \brief Build a textual representation of the value
		 * \return the textual representation of the value
		 */
		virtual std::string print() const;
		/**
		 * \brief Compare the value with another
		 *
		 * This comparator allows using Value as keys in maps, for example.
		 * \param other the value to compare to
		 * \return true if the current value's uid in inferior
		 * to the \a other value's uid
		 */
		bool operator<(const Value& other) const;
		/**
		 * \brief Return a unique identifier for a value
		 *
		 * All values built from the same GCC tree have the same uid,
		 * all values built from distinct GCC trees have distinct uids.
		 * \return a unique, numerical, identifier for the current value
		 */
		uintptr_t getUid() const;

	protected:
		/** The tree the value is built from */
		tree _inner;
		/** The value's uid */
		uintptr_t _uid;
};

/**
 * \brief Output a value on an output stream
 * \param out the output stream
 * \param v the value *
 * \return the output stream received as argument
 */
std::ostream& operator<<(std::ostream& out, const Value* v);
#endif
