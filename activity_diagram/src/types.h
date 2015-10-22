/**
 * \file types.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Useful typedefs for use with the Boost Graph Library
 */
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

	/**
	 * Underlying type of Boost graph used for representation
	 * and manipulation of activity diagrams
	 */
	typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::bidirectionalS,Node,Edge> GraphType;
	/**
	 * Underlying type of Boost vertex descriptor for manipulation
	 * of the nodes in the activity diagrams
	 */
	typedef boost::graph_traits<GraphType>::vertex_descriptor NodeDescriptor;
	/**
	 * Underlying type of Boost vertex iterator for use in Boost algorithms
	 * on the nodes in the activity diagrams
	 */
	typedef boost::graph_traits<GraphType>::vertex_iterator NodeIterator;
}

#endif
