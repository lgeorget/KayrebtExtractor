/**
 * \file node.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of a node from the activity diagram along with a bunch of
 * useful enums, functors, etc.
 */
#ifndef NODE_H
#define NODE_H

#include <boost/config.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <boost/graph/visitors.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_traits.hpp>
#include "types.h"
#include "edge.h"
#include "attribute.h"
#include "shape.h"

namespace kayrebt
{
	/**
	 * Converter between kayrebt::Shapes values and strings
	 */
	extern const char* SHAPES[];

	/**
	 * \brief Describe a node in the activity diagram
	 *
	 * This structure does not contain all the attributes that a node may
	 * have because client code can add more attributes using
	 * ActivityGraph::addNodeAttribute(). Nevertheless, some attributes are
	 * mandatory such as the shape and the label.
	 */
	struct Node
	{
		/**
		 * \brief Construct a node with no label, no shape, and no branch.
		 */
		Node() = default;

		/**
		 * \brief Convert a node's shape into a string
		 * \param[in] s the shape to convert
		 * \return a string describing the shape
		 */
		static std::string shapeToStr(Shape s);

		unsigned int id = index++; /*!< the node unique identifier,
						for internal use only */
		std::string label; /*!< the node's label */
		Shape shape = NO_NODE; /*!< the node's shape, or type */
		static unsigned int index; /*!< a counter to generate unique
					     identifiers for nodes
					     \bug this counter may overflow,
					     and is shared between all graphs
					     built during the lifespan of the
					     process*/
	};

	/**
	 * \brief Functor for use in some Boost Graph algorithms to output some
	 * nodes to an output iterator under some condition
	 * \tparam OutputIterator the type of output iterator to output to
	 * \tparam Predicate the type of the filter condition
	 */
	template<typename OutputIterator, typename Predicate>
	struct NodeFilter : public boost::base_visitor<NodeFilter<OutputIterator,Predicate>> {

		/**
		 * The action will be taken on exiting the vertex during a
		 * depth- or breadth-first search
		 */
		typedef boost::on_finish_vertex event_filter;

		/**
		 * \brief Construct a filter for nodes
		 * \param[in,out] it the output iterator
		 * \param[in] p the condition under which the nodes must be
		 * output to the output iterator
		 */
		NodeFilter(OutputIterator it, Predicate p) : iterator(it), predicate(p) {}

		/**
		 * \brief Possibly output a node, depending on a condition
		 * \tparam Vertex the node descriptor type as provided by the
		 * Boost Graph Library
		 * \tparam Graph the graph type as provided by the Boost Graph
		 * Library
		 * \param[in] v the node to dump
		 * \param[in] g the graph containing the node
		 */
		template <typename Vertex, typename Graph>
		void operator()(Vertex v, const Graph& g) {
			if (predicate(v,g))
				iterator = v;
		}

		private:
			OutputIterator iterator; /*!< the output iterator */
			Predicate predicate; /*!< the predicate for filtering */
	};

	/**
	 * \brief Convenient method to build a kayrebt::NodeFilter
	 * \tparam OutputIterator the type of output iterator to output to
	 * \tparam Predicate the type of the filter condition
	 * \param[in] it the output iterator
	 * \param[in] p the condition under which the nodes must be
	 * output to the output iterator
	 */
	template<typename OutputIterator, typename Predicate> NodeFilter<OutputIterator,Predicate> filter_nodes(OutputIterator it, Predicate p)
	{
		return NodeFilter<OutputIterator,Predicate>(it,p);
	}

	/**
	 * \brief Functor for use in some Boost Graph algorithms to take some
	 * action to each node
	 * \tparam Action the type of the action to take (must be a callable)
	 */
	template<typename Action>
	struct NodeModifier : public boost::base_visitor<NodeModifier<Action>> {

		/**
		 * The action will be taken on exiting the vertex during a
		 * depth- or breadth-first search
		 */
		typedef boost::on_finish_vertex event_filter;

		/**
		 * \brief Construct a NodeModifier
		 * \param[in] a the action that will be called on each node
		 */
		NodeModifier(Action a) : action(a) {}

		/**
		 * \brief Call the action on a given node
		 * \tparam Vertex the node descriptor type as provided by the
		 * Boost Graph Library
		 * \tparam Graph the graph type as provided by the Boost Graph
		 * Library
		 * \param[in] v the node to dump
		 * \param[in] g the graph containing the node
		 */
		template <typename Vertex, typename Graph>
		void operator()(Vertex v, const Graph& g) {
			action(v,g);
		}

		private:
			Action action; /*!< The action to take on each node*/
	};

	/**
	 * \brief Convenient method to build a kayrebt::NodeModifier
	 * \tparam Action the type of the action to take (must be a callable)
	 * \param[in] a the action that will be called on each node
	 */
	template<typename Action> NodeModifier<Action> modify_nodes(Action a)
	{
		return NodeModifier<Action>(a);
	}
}

std::ostream& operator<<(std::ostream& out, const kayrebt::Shape& s);

#endif
