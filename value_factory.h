#ifndef VALUE_FACTORY_H
#define VALUE_FACTORY_H

#include <memory>
#include <gcc-plugin.h>

class Value;

class ValueFactory
{
	private:
		ValueFactory() = default;

	public:
		static const ValueFactory INSTANCE;
		std::shared_ptr<Value> build(tree t) const;
};

#endif
