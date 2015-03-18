/**
 * \file node.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of miscellaneous Node stuff
 */
#include <boost/config.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <boost/graph/visitors.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_traits.hpp>
#include "node.h"
#include "types.h"


using namespace kayrebt;
using namespace boost;

namespace kayrebt
{
	const char* SHAPES[] = {"note", "ellipse", "diamond", "dot", "ellipse", "rect", "dot", "doublecircle", "ellipse", "invisible"};

	Node::Node(std::string l, Shape s, unsigned int c) : label(l), shape(s), category(c) {}

	std::string Node::shapeToStr(Shape s)
	{
		return SHAPES[static_cast<int>(s)];
	}

	NodeDumper::NodeDumper(std::ostream& out) : boost::base_visitor<NodeDumper>(), _out(out)
	{}
}
