#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <unordered_map>
#include <memory>
#include "activity_graph.h"

std::shared_ptr<Node> ActivityGraph::getLabel(uintptr_t nid)
{
	auto it = _labels.find(nid);
	if (it == std::unordered_map::end()) {
		_vertices.push_back(std::make_shared<Node>("label",nid));
		it = _labels.insert(_vertices.back()).first;
	}
	return it->second.lock();
}

void ActivityGraph::fork(std::shared_ptr<Node> newBranch)
{
	_vertices.push_back(newBranch);
	auto node = getLabel(dest);
	_edges.push_back(std::make_pair<std::weak_ptr<Node>,std::weak_ptr<Node>>(newBranch,dest));
	_current = newBranch;
}

void ActivityGraph::addNode(std::shared_ptr<Node> newNode)
{
	_vertices.push_back(newNode);
	_edges.push_back(std::make_pair<std::weak_ptr<Node>,std::weak_ptr<Node>>(current,newNode));
	_current = newNode;
}
