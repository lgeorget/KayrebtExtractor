#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <unordered_map>
#include <memory>
#include "activity_graph.h"
#include "node.h"

ActivityGraph::ActivityGraph()
{
	addNode(std::make_shared<Node>("init",0));
	_current = _vertices.back();
}

std::shared_ptr<Node> ActivityGraph::getLabel(uintptr_t nid)
{
	auto it = _labels.find(nid);
	if (it == _labels.end()) {
		_vertices.push_back(std::make_shared<Node>("label",nid));
		_labels[nid] = _vertices.back();
	}
	return _vertices.back();
}

void ActivityGraph::fork(std::shared_ptr<Node>& newBranch, uintptr_t dest)
{
//	_vertices.push_back(newBranch);
	auto node = getLabel(dest);
	_edges.push_back(std::make_pair<std::weak_ptr<Node>,std::weak_ptr<Node>>(newBranch,node));
//	_current = newBranch;
}

void ActivityGraph::addNode(std::shared_ptr<Node> newNode)
{
	_vertices.push_back(newNode);
	_edges.push_back(std::make_pair<std::weak_ptr<Node>,std::weak_ptr<Node>>(_current,newNode));
	_current = newNode;
}

std::ostream& operator<<(std::ostream& out, const ActivityGraph& g)
{
	out << "digraph d {" << std::endl;
	for (auto n : _vertices)
		out << *n;
	for (auto e : _edges)
		out << e.first.lock()->getNid() << " -> " << e.second.lock()->getNid() << ";" << std::endl;
	out << "}" << std::endl;
}
