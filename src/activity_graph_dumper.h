/**
 * \file activity_graph_dumper.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Interface of the main class : the activity graph dumper
 */
#ifndef ACTIVITY_DUMPER_H
#define ACTIVITY_DUMPER_H

#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <stack>
#include <utility>
#include <memory>
#include <activity_graph.h>
#include "dumper.h"
#include "label.h"
#include "url_finder.h"

class AssignExpr;
class FunctionBody;
class CallExpr;
class CondExpr;
class GotoExpr;
class LabelExpr;
class NopExpr;
class ReturnExpr;
class SwitchExpr;
class Expression;
class Configurator;

/**
 * \brief Builder and handler of Kayrebt::ActivityGraph -s
 *
 * This class allows for step-by-step building of a Kayrebt::ActivityGraph
 * from an Expression. At the end of the process, the activity diagram constructed
 * can be retrieved through the ActivityGraphDumper::graph() method. Usually,
 * one wants to call the ActivityGraphDumper::dumpFunctionBody() and feeds it
 * with a well-formed FunctionBody, and then expects the whole graph for the
 * function to be constructed.
 *
 * This class uses the visitor design pattern. ActivityGraph::dumpAsmExpr(), for
 * example, is meant to be called by AsmExpr::accept(). Beginning the dumping
 * from any entry point but ActivityGraphDumper::dumpFunctionBody is likely to
 * yield a strange, strange, graph.
 */
class ActivityGraphDumper : public Dumper
{
	public:
		/**
		 * \brief Construct a new dumper for activity graphs
		 */
		ActivityGraphDumper(const Configurator& global_config);
		/**
		 * \brief Build the graph corresponding to an entire function
		 * \param e the function to consider
		 */
		void dumpFunctionBody(FunctionBody* const e) override;
		/**
		 * \brief Build the subgraph corresponding to an asm statement
		 * \param e the asm expression to dump
		 */
		void dumpAsmExpr(AsmExpr* const e) override;
		/**
		 * \brief Build the subgraph corresponding to an assignment
		 * \param e the assignment expression to dump
		 */
		void dumpAssignExpr(AssignExpr* const e) override;
		/**
		 * \brief Build the subgraph corresponding to a function call
		 * \param e the calling expression to dump
		 */
		void dumpCallExpr(CallExpr* const e) override;
		/**
		 * \brief Build the subgraph corresponding to a condition
		 * \param e the condition expression to dump
		 */
		void dumpCondExpr(CondExpr* const e) override;
		/**
		 * \brief Build the subgraph corresponding to an goto statement
		 * \param e the goto expression to dump
		 */
		void dumpGotoExpr(GotoExpr* const e) override;
		/**
		 * \brief Build the subgraph corresponding to an label statement
		 * \param e the label expression to dump
		 */
		void dumpLabelExpr(LabelExpr* const e) override;
		/**
		 * \brief Build the subgraph corresponding to a no-op statement
		 * \param e the no-op expression to dump
		 */
		void dumpNopExpr(NopExpr* const e) override;
		/**
		 * \brief Build the subgraph corresponding to a return statement
		 * \param e the return expression to dump
		 */
		void dumpReturnExpr(ReturnExpr* const e) override;
		/**
		 * \brief Build the subgraph corresponding to a switch expression
		 * \param e the switch expression to dump
		 */
		void dumpSwitchExpr(SwitchExpr* const e) override;
		/**
		 * \brief Build the subgraph corresponding to a untyped Expression
		 * \param e the untyped expression to dump
		 */
		void dumpExpression(Expression* const e) override;
		/**
		 * \brief Return the graph built
		 *
		 * The graph is returned as a constant reference, to avoid a
		 * useless copy if only a read-only consultation is done
		 * \return a constant reference to the graph built
		 */
		const kayrebt::ActivityGraph& graph();

	private:
		std::function<unsigned int(const std::string&)> _categorizer;
		UrlFinder _urlFinder;
		/**
		 * The graph in construction
		 */
		kayrebt::ActivityGraph _g;
		/**
		 * The identifier of the last node added to the graph
		 */
		std::unique_ptr<kayrebt::Identifier> _last;
		/**
		 * The identifier of the last-but-one node added to the graph
		 */
		std::unique_ptr<kayrebt::Identifier> _last_but_one;
		/**
		 * The values built during dumping the graph
		 */
		std::stack<std::string> _values;
		/**
		 * Mapping between the basic blocks of the function body and the
		 * first node of the corresponding subgraph
		 */
		std::map<basic_block,std::unique_ptr<kayrebt::MergeIdentifier>> _init_bb;
		/**
		 * Mapping between the basic blocks of the function body and a
		 * pair consisting of the decision node corresponding to a
		 * condition point (a 'if' in the function body) and the
		 * textual condition associated to it
		 */
		std::map<basic_block,std::pair<std::unique_ptr<kayrebt::MergeIdentifier>,std::string>> _ifs;
		/**
		 * List of pairs mapping nodes at the end of their basic block
		 * to the destination basic block the control flows to
		 */
		std::vector<std::pair<std::unique_ptr<kayrebt::Identifier>,basic_block>> _gotos;

		std::map<unsigned int, kayrebt::Identifier> _labels;

		/**
		 * Tell that the next Expression is to be skipped instead of dumped
		 */
		bool _skip = false;

		bool _outgoing_transitions_handled =false;
		/**
		 * The current basic block being dumped
		 */
		basic_block _current_bb;

		/**
		 * \brief Replace the last-but-one node by the last, and the
		 * last by \a node
		 * \param node the new node that must replace \a last
		 */
		void updateLast(kayrebt::Identifier&& node);
		/**
		 * \brief Replace the last-but-one node by the last, and the
		 * last by \a node
		 * \param node the new node that must replace \a last
		 */
		void updateLast(kayrebt::Identifier& node);

		kayrebt::Identifier getLabel(unsigned int uid);
};


#endif
