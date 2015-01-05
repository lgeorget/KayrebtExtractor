#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <memory>

class Node
{
	public:
		explicit Node(std::string&& label, uintptr_t nid);
		void setLevelAfter(std::shared_ptr<Node> other);
		inline unsigned int getLevel() const { return _level; }
		inline uintptr_t getNid() const { return _nid; }
		void setLabel(std::string&& newLabel) { _label = newLabel; }

	protected:
		std::string _label;
		uintptr_t _nid;
		unsigned int _level;

	friend std::ostream& operator<<(std::ostream& out, const Node& n);
};

#endif
