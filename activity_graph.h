#ifndef ACTIVITY_GRAPH_H
#define ACTIVITY_GRAPH_H

#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <unordered_map>
#include <memory>

class Node;

class ActivityGraph
{
	public:
		explicit ActivityGraph() = default;
		std::shared_ptr<Node> getLabel(uintptr_t);
		void fork(std::shared_ptr<Node> newBranch, uintptr_t dest);
		void addNode(std::shared_ptr<Node> newNode);


	private:
		std::list<std::shared_ptr<Node>> _vertices;
		std::list<std::pair<std::weak_ptr<Node>,std::weak_ptr<Node>>> _edges;
		std::unordered_map<uintptr_t,std::weak_ptr<Node>> _labels;
		std::shared_ptr<Node>& _current;
};

#endif
