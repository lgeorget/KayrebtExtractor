#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include "activity_graph.h"
#include "node.h"

ActivityGraph::ActivityGraph()
{
	_vertices.push_back(std::make_shared<Node>("init",0));
	_current = _vertices.back();
}

std::shared_ptr<Node> ActivityGraph::getLabel(uintptr_t nid)
{
	auto it = std::find_if(_vertices.cbegin(), _vertices.cend(),
			[&nid](const std::shared_ptr<Node>& a){ return a->getNid() == nid; });
	if (it == _vertices.cend()) {
		auto node = std::make_shared<Node>(std::to_string(nid) + ": ",nid);
		_vertices.push_back(node);
		return node;
	} else {
		return *it;
	}
}

void ActivityGraph::fork(std::shared_ptr<Node> newBranch, uintptr_t dest)
{
	_edges.emplace(newBranch,getLabel(dest));
}

void ActivityGraph::addNode(std::shared_ptr<Node> newNode)
{
	_vertices.push_back(newNode);
	_edges.emplace(_current,newNode);
	_current = newNode;
}

void ActivityGraph::setCurrent(std::shared_ptr<Node>& newCurr)
{
	if (std::find(_vertices.cbegin(), _vertices.cend(), newCurr) != _vertices.cend())
		_current = newCurr;
}

std::ostream& operator<<(std::ostream& out, const ActivityGraph& g)
{
	out << "digraph d {" << std::endl;
	for (auto n : g._vertices)
		out << *n;
	for (auto e : g._edges)
		out << e.first->getNid() << " -> " << e.second->getNid() << ";" << std::endl;
	out << "}" << std::endl;
}
