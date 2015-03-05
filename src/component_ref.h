/**
 * \file component_ref.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a reference to a field inside a structure or union
 */
#ifndef COMPONENT_REF_H
#define COMPONENT_REF_H

#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

/**
 * \brief Represent the fetching of a field inside a structure or union
 */
class ComponentRef : public Value
{
	public:
		/**
		 * \brief Construct a new ComponentRef from a TREE COMPONENT REF
		 * \param t the tree value
		 * \param symbol the operand used for indirection (for example
		 * '.' or '->'
		 */
		explicit ComponentRef(tree t, const std::string& symbol);
		std::string print() const override;

	private:
		/** The container */
		std::shared_ptr<Value> _container;
		/** The field inside the container */
		std::shared_ptr<Value> _component;
		/** The operand used for indirection */
		const std::string _symbol;
};

#endif
