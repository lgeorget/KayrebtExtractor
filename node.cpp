#include <iostream>
#include <string>
#include <memory>
#include "node.h"

Node::Node(std::string&& label, uintptr_t nid) : _label(label), _nid(nid)
{}

void Node::setLevelAfter(std::shared_ptr<Node> other)
{
	if (other->_level > _level)
		_level = other->_level+1;
}

std::ostream& operator<<(std::ostream& out, const Node& n)
{
	out << n._nid << " [label=\"" << n._label << "\"];" << std::endl;
	return out;
}
