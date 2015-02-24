#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <map>
#include <gcc-plugin.h>
#include <tree.h>

class Operator
{
	public:
		static const std::string& print(tree_code op);

	private:
		Operator() = default;
		const static std::map<tree_code,std::string> symbols;
};

#endif
