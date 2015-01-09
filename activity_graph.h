#ifndef ACTIVITY_GRAPH_H
#define ACTIVITY_GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <unordered_map>
#include <memory>

class Node;

class ActivityGraph
{
	public:
		explicit ActivityGraph();
		std::shared_ptr<Node> getLabel(uintptr_t);
		void fork(std::shared_ptr<Node> newBranch, uintptr_t dest);
		void addNode(std::shared_ptr<Node> newNode);
		std::shared_ptr<Node>& getCurrent() { return _current; }
		void setCurrent(std::shared_ptr<Node>& newCurr);
		void invalidateCurrent();
		void closeBranch();


	private:
		std::vector<std::shared_ptr<Node>> _vertices;
		std::set<std::pair<std::shared_ptr<Node>,std::shared_ptr<Node>>> _edges;
		std::shared_ptr<Node> _current;
		const int INIT = 0;
		const int END = 1;

	friend std::ostream& operator<<(std::ostream& out, const ActivityGraph& g);
};

#endif
