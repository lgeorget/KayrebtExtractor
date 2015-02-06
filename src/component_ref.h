#ifndef COMPONENT_REF_H
#define COMPONENT_REF_H

#include <iostream>
#include <string>
#include <memory>
#include <gcc-plugin.h>
#include <tree.h>
#include "value.h"

class ComponentRef : public Value
{
	public:
		explicit ComponentRef(tree t, const std::string& symbol);
		std::string print() const override;

	private:
		std::shared_ptr<Value> _container;
		std::shared_ptr<Value> _component;
		const std::string _symbol;
};

#endif
