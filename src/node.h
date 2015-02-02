#ifndef NODE_H
#define NODE_H

#include <boost/config.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <boost/graph/visitors.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graph_traits.hpp>
#include "types.h"
#include "edge.h"

namespace kayrebt
{
	enum Shape { NOTE=0, INIT, MERGE, FORK, ACTION, OBJECT, SYNC, END_OF_FLOW, END_OF_ACTIVITY, NO_NODE };
	extern const char* SHAPES[];

	struct Node
	{
		Node() = default;
		Node(std::string l, Shape s, unsigned int b=0);
		static std::string shapeToStr(Shape s);

		unsigned int id = index++;
		std::string label = "";
		Shape shape = NO_NODE;
		unsigned int branch = 0;
		static unsigned int index;
	};

	struct NodeDumper : public boost::base_visitor<NodeDumper> {
		typedef boost::on_discover_vertex event_filter;

		NodeDumper(std::ostream& out);

		template<typename Vertex, typename Graph>
		void operator()(Vertex v, const Graph& g) {
			//std::cout << g[v].id << ": " << g[v].shape << " " << g[v].label << std::endl;
			_out << g[v].id << "[label=\"" << g[v].label << "\", shape=\"" << Node::shapeToStr(g[v].shape) << "\"];" << std::endl;
			boost::graph_traits<GraphType>::adjacency_iterator vi,vend;
			for (boost::tie(vi,vend) = adjacent_vertices(v,g) ;
				vi != vend ;
				++vi) {
				auto e = edge(v,*vi,g).first;
				if (g[e].condition.empty())
					_out << g[v].id << " -> " << g[*vi].id << ";" << std::endl;
				else
					_out << g[v].id << " -> " << g[*vi].id << "[label=\"" << g[e].condition << "\"];" << std::endl;
			}

		}

		private:
			std::ostream& _out;
	};

	template<typename OutputIterator, typename Predicate>
	struct NodeFilter : public boost::base_visitor<NodeFilter<OutputIterator,Predicate>> {
		typedef boost::on_finish_vertex event_filter;
		OutputIterator iterator;
		Predicate predicate;

		NodeFilter(OutputIterator it, Predicate p) : iterator(it), predicate(p) {}
		template <typename Vertex, typename Graph>
		void operator()(Vertex v, const Graph& g) {
			if (predicate(v,g))
				iterator = v;
		}
	};

	template<typename OutputIterator, typename Predicate> NodeFilter<OutputIterator,Predicate> filter_nodes(OutputIterator it, Predicate p)
	{
		return NodeFilter<OutputIterator,Predicate>(it,p);
	}

	template<typename Action>
	struct NodeModifier : public boost::base_visitor<NodeModifier<Action>> {
		typedef boost::on_finish_vertex event_filter;
		Action action;

		NodeModifier(Action a) : action(a) {}
		template <typename Vertex, typename Graph>
		void operator()(Vertex v, const Graph& g) {
			action(v,g);
		}
	};

	template<typename Action> NodeModifier<Action> modify_nodes(Action a)
	{
		return NodeModifier<Action>(a);
	}
}

#endif
