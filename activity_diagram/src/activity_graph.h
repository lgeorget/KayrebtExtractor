/**
 * \file activity_graph.h
 * \author Laurent Georget
 * \date 2015-3-03
 * \brief Main header file, defining the activity diagram
 */
#ifndef ACTIVITY_GRAPH_H
#define ACTIVITY_GRAPH_H

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include "action_identifier.h"
#include "flow_identifier.h"
#include "end_of_flow_identifier.h"
#include "end_of_activity_identifier.h"
#include "fork_identifier.h"
#include "init_identifier.h"
#include "identifier.h"
#include "merge_identifier.h"
#include "object_identifier.h"
#include "sync_identifier.h"
#include "property_writer.h"
#include "shape.h"

/**
 * Covers all the activity diagram library
 */
namespace kayrebt
{
	struct ActivityGraphInternals;

	/**
	 * \brief Main class of the activity graph library
	 *
	 * This class is used for the step-by-step construction of an activity
	 * diagram, as well as its validation ond output in GraphViz format.
	 */
	class ActivityGraph
	{
		private:
			/**
			 * \brief Pointer to private implementation
			 */
			ActivityGraphInternals* _d;
			std::map<NodeDescriptor,std::vector<std::shared_ptr<BaseAttribute>>> _nodeAttrs;
			std::vector<std::shared_ptr<BaseAttribute>> _graphAttrs;

		public:
			/**
			 * \brief Construct an almost empty activity diagram,
			 * containing only the initial node
			 */
			ActivityGraph();
			/**
			 * \brief Destruct the activity diagram, freeing all memory
			 */
			~ActivityGraph();

			template<typename T, typename Outputter = default_outputter<T>>
			void addGraphAttribute(const std::string& name, const T& value, const Outputter& out = Outputter()) {
				_graphAttrs.emplace_back(new Attribute<T,Outputter>(name,value,out));
			}

			template<typename T, typename Outputter = default_outputter<T>>
			void addNodeAttribute(const Identifier& i, const std::string& name, const T& value, const Outputter& out = Outputter()) {
				_nodeAttrs[*i].emplace_back(new Attribute<T,Outputter>(name,value,out));
			}

			void printNodeId(std::ostream& out, const Identifier& i);
			/**
			 * \brief Add an action node to the activity diagram
			 * \param[in] label the label of the new action node
			 * \return an identifier for the newly created node
			 */
			ActionIdentifier addAction(std::string label);
			/**
			 * \brief Add an object node to the activity diagram
			 * \param[in] label the label of the new object node
			 * \return an identifier for the newly created node
			 */
			ObjectIdentifier addObject(std::string label);
			/**
			 * \brief Add a forking node to the activity diagram,
			 * to start a concurrent area
			 * \return an identifier for the newly created node
			 */
			ForkIdentifier fork();
			/**
			 * \brief Add an end-of-flow node in the activity
			 * diagram
			 * \return an identifier for the newly created node
			 */
			EndOfFlowIdentifier closeFlow();
			/**
			 * \brief Add an end-of-activity node in the activity
			 * diagram
			 * \return an identifier for the newly created node
			 */
			EndOfActivityIdentifier terminateActivity();
			/**
			 * \brief Add a decision node in the activity diagram
			 *
			 * Decision nodes also serve as merging nodes in the
			 * current implementation.
			 * \return an identifier for the newly created node
			 */
			MergeIdentifier addDecision();
			/**
			 * \brief Add a synchronization node in the activity
			 * diagram, to close a concurrent section
			 * \return an identifier for the newly creaed node
			 */
			SyncIdentifier synchronize();
			/**
			 * \brief Build an unguarded edge between two nodes
			 * \param[in] branch the source node
			 * \param[in] head the destination node
			 * \sa ActivityGraph::addGuard
			 */
			void addEdge(const Identifier& branch, const Identifier& head);
			/**
			 * \brief Build a guarded edge between two nodes
			 * \param[in] branch the source node
			 * \param[in] head the destination node
			 * \param[in] condition the guard, which will be used
			 * as the edge label
			 * \sa ActivityGraph::addEdge
			 */
			void addGuard(const Identifier& branch, const Identifier& head, std::string condition);
			/**
			 * \brief Set the label of a given node
			 *
			 * In the current implementation, labels are supported
			 * everywhere but are only displayed on action and object
			 * nodes.
			 * \param[in] node the node
			 * \param[in] label the new label for \a node
			 */
			void setLabel(Identifier& node, std::string label);
			/**
			 * \brief Verify whether an activity diagram is well-formed
			 *
			 * Equivalent to
			 * <code>
			 * validateConnexity() &&
			 * validate BranchesEndings() &&
			 * validateMergeEdges()
			 * </code>
			 * but outputs warning message if one of the test fails
			 * \return true if and only if the diagram is well-formed
			 */
			bool validate() const;
			/**
			 * \brief Verify that the activity diagram has as a
			 * spanning tree, i.e. every node is reachable from the
			 * initial node
			 *
			 * Guards cannot be verified, so even if the path to a
			 * node contains some, it will still be considered as
			 * reachable.
			 * \return true if and only if every node is reachable
			 * from the initial node
			 */
			bool validateConnexity() const;
			/**
			 * \brief Verify that every node either is an ending
			 * node or has an outgoing edge
			 *
			 * All nodes without successors must be ending nodes,
			 * i.e. end-of-flow or end-of-activity nodes.
			 * \return true if and only if every branch in the
			 * activity diagram ends with an ending node
			 */
			bool validateBranchesEndings() const;
			/**
			 * \brief Verify that for every decision nodes, either
			 * it has only one outgoing transition or every of its
			 * outgoing transition is guarded
			 * \return true if and only if the activity diagram
			 * contains no decision nodes with unguarded outgoing
			 * transitions when having more than one outgoing
			 * transition.
			 */
			bool validateMergeEdges() const;
			//TODO validateForkSync();
			/**
			 * \brief Eliminate redundant decision nodes
			 *
			 * Eliminate decision/merging nodes with exactly one
			 * incoming transition and one outgoing transition.
			 * An edge is reated between the predecessor and the
			 * successor of the decision/merging node.
			 */
			void simplifyMergeNodes();

			/**
			 * \brief Eliminate the nodes which we left behind for
			 * their attributes but which must not be displayed
			 */
			void purgeGraph();
			/**
			 * \brief Get the initial node of the activity diagram
			 * \return the identifier for the initial node in the
			 * activity diagram
			 */
			InitIdentifier initialNode() const;

			/**
			 * \brief Output the activity diagram in GraphViz format
			 */
			std::ostream& graphVizify(std::ostream& out) const;
	};
}
#endif
