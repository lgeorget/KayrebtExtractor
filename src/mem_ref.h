/**
 * \file mem_ref.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a memory taking operation
 */
#ifndef MEM_REF_H
#define MEM_REF_H

#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

/**
 * \brief Represent a memory taking operation
 */
class MemRef : public Value
{
	public:
		/**
		 * \brief Construct a new MemRef from a TREE MEM REF value
		 * \param t the tree
		 */
		explicit MemRef(tree t);
		std::string print() const override;

	private:
		/** The symbol whose address is taken */
		std::shared_ptr<Value> _ptr;
		/** The operator used to take the address of \a _ptr (usually '&') */
		const std::string _symbol;
};

#endif
