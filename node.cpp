#include <iostream>
#include <string>
#include <memory>
#include "node.h"

Node::Node(std::string&& label, uintptr_t nid) : _label(label), _nid(nid)
{}

unsigned int Node::getLevel()
{
	return _level;
}

void Node::setLevelAfter(std::shared_ptr<Node> other)
{
	if (other->_level > _level)
		_level _other->_level+1;
}
