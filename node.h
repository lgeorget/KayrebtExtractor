#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <memory>

class Node : public std::enable_shared_from_this<Node>
{
	public:
		explicit Node(std::string&& label, uintptr_t nid);
		unsigned int getLevel();
		void setLevelAfter(std::shared_ptr<Node> other);

	protected:
		std::string _label;
		uintptr_t _nid;
		unsigned int _level;
};

#endif
