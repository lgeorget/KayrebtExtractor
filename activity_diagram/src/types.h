#ifndef TYPES_H
#define TYPES_H

#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace kayrebt
{
	class ActivityGraph;
	class Identifier;
	class Node;
	class Edge;

	typedef boost::adjacency_list<boost::listS,boost::setS,boost::bidirectionalS,Node,Edge> GraphType;
	typedef boost::graph_traits<GraphType>::vertex_descriptor NodeDescriptor;
	typedef boost::graph_traits<GraphType>::vertex_iterator NodeIterator;
}

#endif
