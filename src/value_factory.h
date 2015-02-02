#ifndef VALUE_FACTORY_H
#define VALUE_FACTORY_H

#include <memory>
#include <map>
#include <gcc-plugin.h>

class Value;

class ValueFactory
{
	private:
		ValueFactory() = default;

	public:
		static ValueFactory INSTANCE;
		std::shared_ptr<Value> build(tree t);
		std::map<tree,std::shared_ptr<Value>> strings;
		std::map<tree,std::shared_ptr<Value>> integers;
		std::map<tree,std::shared_ptr<Value>> idents;
};

#endif
