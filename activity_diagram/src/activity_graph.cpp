#include <boost/config.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/connected_components.hpp>
#include "activity_graph.h"
#include "activity_graph_internals.h"
#include "node.h"
#include "edge.h"

using namespace kayrebt;
using namespace boost;

namespace kayrebt
{
	ActivityGraph::ActivityGraph() : _d(new ActivityGraphInternals())
	{
	}

	ActivityGraph::~ActivityGraph()
	{
		delete _d;
	}

	ActionIdentifier ActivityGraph::addAction(std::string label, unsigned int cat)
	{
		auto v = add_vertex(_d->inner);
		_d->inner[v].label = label;
		_d->inner[v].shape = ACTION;
		_d->inner[v].category = cat;
		return ActionIdentifier(v);
	}

	ObjectIdentifier ActivityGraph::addObject(std::string label, unsigned int cat)
	{
		auto v = add_vertex(_d->inner);
		_d->inner[v].label = label;
		_d->inner[v].shape = OBJECT;
		_d->inner[v].category = cat;
		return ObjectIdentifier(v);
	}

	ForkIdentifier ActivityGraph::fork()
	{
		auto v = add_vertex(_d->inner);
		_d->inner[v].shape = FORK;
		return ForkIdentifier(v);
	}

	EndOfFlowIdentifier ActivityGraph::closeFlow()
	{
		auto v = add_vertex(_d->inner);
		_d->inner[v].shape = END_OF_FLOW;
		return EndOfFlowIdentifier(v);
	}

	EndOfActivityIdentifier ActivityGraph::terminateActivity()
	{
		auto v = add_vertex(_d->inner);
		_d->inner[v].shape = END_OF_ACTIVITY;
		return EndOfActivityIdentifier(v);
	}

	MergeIdentifier ActivityGraph::addDecision()
	{
		auto v = add_vertex(_d->inner);
		_d->inner[v].shape = MERGE;
		return MergeIdentifier(v);
	}

	SyncIdentifier ActivityGraph::synchronize()
	{
		auto v = add_vertex(_d->inner);
		_d->inner[v].shape = SYNC;
		return SyncIdentifier(v);
	}

	void ActivityGraph::addEdge(const Identifier& branch, const Identifier& head, unsigned int cat)
	{
		auto e = add_edge(*branch, *head, _d->inner);
		_d->inner[e.first].category = cat;
	}

	void ActivityGraph::addGuard(const Identifier& branch, const Identifier& head, std::string condition, unsigned int cat)
	{
		auto e = edge(*branch, *head, _d->inner);
		if (!e.second)
			e = add_edge(*branch, *head, _d->inner);
		_d->inner[e.first].condition = condition;
		_d->inner[e.first].category = cat;
	}

	void ActivityGraph::setLabel(Identifier& branch, std::string label)
	{
		_d->inner[*branch].label = label;
		//labels are implemented as notes for nodes other than actions
		//and object, but they're not part of the graph until we draw it
	}

	bool ActivityGraph::validate()
	{
		std::vector<unsigned int> reachable;
		std::vector<NodeDescriptor> wrongEndingNodes;
		std::vector<NodeDescriptor> mergeNodesOutEdgesWithoutGuards;
		std::map<NodeDescriptor, boost::default_color_type> c_m;
		depth_first_search(_d->inner,
				make_dfs_visitor(
					make_pair(
					write_property(get(&Node::id,_d->inner),
							std::back_inserter(reachable),
							on_discover_vertex()),
					make_pair(
					filter_nodes(std::back_inserter(mergeNodesOutEdgesWithoutGuards),
						     [](NodeDescriptor v, const GraphType& g) -> bool {
							auto it = out_edges(v,g);
							return g[v].shape == MERGE &&
								std::any_of(it.first, it.second,
								[&g](decltype(*(it.first)) edge) -> bool { return g[edge].condition.empty(); });
							}),
					filter_nodes(std::back_inserter(wrongEndingNodes),
						     [](NodeDescriptor v, const GraphType& g) -> bool {
						        return out_degree(v,g) == 0 &&
							       g[v].shape != END_OF_FLOW &&
							       g[v].shape != END_OF_ACTIVITY; })
					))),
				make_assoc_property_map(c_m));
		return reachable.size() == num_vertices(_d->inner) &&
		       wrongEndingNodes.size() == 0 &&
		       mergeNodesOutEdgesWithoutGuards.size() == 0;
	}

	bool ActivityGraph::validateConnexity()
	{
		std::vector<unsigned int> reachable;
		std::map<NodeDescriptor, boost::default_color_type> c_m;
		depth_first_search(_d->inner,
				make_dfs_visitor(
					write_property(get(&Node::id,_d->inner),
							std::back_inserter(reachable),
							on_discover_vertex())),
				make_assoc_property_map(c_m));
		return reachable.size() == num_vertices(_d->inner);
	}

	bool ActivityGraph::validateBranchesEndings()
	{
		std::vector<NodeDescriptor> nodes;
		NodeIterator vi,vend;
		for (boost::tie(vi,vend) = vertices(_d->inner) ; vi != vend ; ++vi) {
			if (boost::out_degree(*vi,_d->inner) == 0 && _d->inner[*vi].shape != END_OF_FLOW && _d->inner[*vi].shape != END_OF_ACTIVITY)
				nodes.push_back(*vi);
		}
		return nodes.size() == 0;
	}

	bool ActivityGraph::validateMergeEdges()
	{
		std::vector<NodeDescriptor> nodes;
		std::map<NodeDescriptor, boost::default_color_type> c_m;
		depth_first_search(_d->inner,
				make_dfs_visitor(
					filter_nodes(std::back_inserter(nodes),
						     [](NodeDescriptor v, const GraphType& g) -> bool {
							auto it = out_edges(v,g);
							return (g[v].shape == MERGE &&
								std::any_of(it.first, it.second,
								[&g](decltype(*(it.first)) edge) -> bool { return g[edge].condition.empty(); }));
							})),
				make_assoc_property_map(c_m));
		return nodes.size() == 0;
	}

	/**
	 * \brief Output the activity diagram in GraphViz format
	 * \relates kayrebt::ActivityGraph
	 */
	std::ostream& ActivityGraph::graphVizify(std::ostream& out, std::function<std::string(unsigned int)> categoryDumper) const
	{
		unsigned int nb = num_vertices(_d->inner);
#ifndef NDEBUG
		std::cerr << "Number of vertices in graph: " << nb << std::endl;
		std::cerr << "Number of edges in graph: " << num_edges(_d->inner) << std::endl;
#endif
		out << "digraph d {" << std::endl;
		if (nb > 0) {
			auto dfs = make_dfs_visitor(NodeDumper(out, categoryDumper));
			std::map<NodeDescriptor, boost::default_color_type> c_m;
			depth_first_search(_d->inner, dfs, make_assoc_property_map(c_m));
		}
		out << "}" << std::endl;

		return out;
	}

	InitIdentifier ActivityGraph::initialNode() const
	{
		return *(_d->initNode);
	}

	void ActivityGraph::simplifyMergeNodes()
	{
		std::set<NodeDescriptor> nodes;
		std::map<NodeDescriptor, boost::default_color_type> c_m;
		depth_first_search(_d->inner,
				make_dfs_visitor(
					filter_nodes(std::inserter(nodes,nodes.begin()),

			[](NodeDescriptor v, const GraphType& g) -> bool
			{
				return (g[v].shape == MERGE && in_degree(v,g) <= 1 && out_degree(v,g) == 1);
			})),
				make_assoc_property_map(c_m));

		GraphType& g = _d->inner;
		for (NodeDescriptor n : nodes)
		{
			auto maybe_pred = inv_adjacent_vertices(n,g);
			auto maybe_succ  = adjacent_vertices(n,g);
			if (maybe_succ.first != maybe_succ.second) {
				NodeDescriptor succ = *(maybe_succ.first);
				if (maybe_pred.first != maybe_pred.second) {
					NodeDescriptor pred = *(maybe_pred.first);
					auto newEdge = add_edge(pred,succ,g).first;
					g[newEdge].condition = g[edge(pred,n,g).first].condition;
				}
				clear_vertex(n,g);
				remove_vertex(n,g);
			}
		}
	}
}
