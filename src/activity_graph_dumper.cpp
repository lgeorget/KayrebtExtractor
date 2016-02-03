/**
 * \file activity_graph_dumper.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the ActivityGraphDumper
 */
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <regex>
#include <gcc-plugin.h>
#include <basic-block.h>
#include <activity_graph.h>
#include "activity_graph_dumper.h"
#include "asm_expr.h"
#include "assign_expr.h"
#include "function_body.h"
#include "call_expr.h"
#include "phi_expr.h"
#include "cond_expr.h"
#include "expression.h"
#include "goto_expr.h"
#include "label_expr.h"
#include "nop_expr.h"
#include "return_expr.h"
#include "switch_expr.h"
#include "dumper.h"
#include "label.h"
#include "operator.h"
#include "case_label.h"
#include "configurator.h"
#include "make_unique.h"

using namespace kayrebt;

std::ostream& operator<<(std::ostream& out, std::vector<std::shared_ptr<Value>> v) {
	out << "\"";
	if (!v.empty()) {
		auto it = v.cbegin();
		out << (*it)->print();
		for (++it ; it != v.cend() ; ++it)
			out << "," << (*it)->print();
	}
	out << "\"";
	return out;
}

ActivityGraphDumper::ActivityGraphDumper(const Configurator& global_config,
	const std::string& file, int line) :
	Dumper(), _categorizer(global_config.getCategorizer()),
	_categorydumper(global_config.getCategoryDumper()), _urlFinder(main_input_filename), _last(_g.initialNode()), _last_but_one(_g.initialNode())
{
	_g.addGraphAttribute("file",file);
	_g.addGraphAttribute("line",line);
	if (global_config.shallDumpUrls())
		_urlFinder.open(global_config.getDbFile().c_str(), global_config.getDbName().c_str());
	_skip = false;
	_gotos.emplace(ENTRY_BLOCK_PTR,_g.initialNode());
	_g.addNodeAttribute(_g.initialNode(), "type", std::string("init"));
}

void ActivityGraphDumper::updateLast(kayrebt::Identifier node)
{
	_last_but_one = _last;
	_last = node;
}

inline void ActivityGraphDumper::addAttributesForCategory(
		const kayrebt::Identifier& i, unsigned int cat)
{
	const std::vector<std::pair<std::string,std::string>>* rep;
	if (!cat || !(rep = _categorydumper(cat)))
		return;
	for (const auto& attr : *rep) {
		_g.addNodeAttribute(i,attr.first,attr.second);
	}
}

inline void ActivityGraphDumper::addLineAndFileAttributes(
		const kayrebt::Identifier& i, int line,
		const std::string& filename)
{
	if (line > 0)
		_g.addNodeAttribute(i,"line",line);
	if (!filename.empty())
		_g.addNodeAttribute(i,"filename",filename);
}

#ifndef NDEBUG
void ActivityGraphDumper::dumpExpression(Expression* const e)
#else
void ActivityGraphDumper::dumpExpression(Expression* const)
#endif
{
#ifndef NDEBUG
	std::cerr << "Discarded: " << *e << std::endl;
#endif
	_skip = true;
}

void ActivityGraphDumper::dumpAsmExpr(AsmExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building asm" << std::endl;
#endif
	auto i = _g.addAction(e->_stmt);
	addLineAndFileAttributes(i,e->_line,e->_file);
	_g.addNodeAttribute(i,"type",std::string("asm"));
	addAttributesForCategory(i,_categorizer(e->_stmt));
	updateLast(i);

}

void ActivityGraphDumper::dumpAssignExpr(AssignExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building assign" << std::endl;
#endif
	std::string label = e->_rhs2 ?
		e->_whatToSet->print() + " = " +
		e->_rhs1->print() + Operator::print(e->_op) +
		e->_rhs2->print()
		:
		e->_whatToSet->print() + " = " +
		e->_rhs1->print()
		;

#ifndef NDEBUG
	std::cerr << "got a label for assign stmt" << std::endl;
#endif
	auto i = _g.addAction(label);
	addLineAndFileAttributes(i,e->_line,e->_file);
	_g.addNodeAttribute(i,"type",std::string("assign"));
	addAttributesForCategory(i,_categorizer(label));
	updateLast(i);
}

void ActivityGraphDumper::dumpFunctionBody(FunctionBody* const e)
{
#ifndef NDEBUG
	std::cerr << "function body" << std::endl;
#endif
	_g.addGraphAttribute("parameters",e->getFormalParameters());
	for (const auto& bb : e->_bb) {
		auto node = _g.addDecision();
		updateLast(node);
		_init_bb.emplace(bb.first, node);
#ifndef NDEBUG
		std::cerr << "dumping basic block " << bb.first << std::endl;
#endif
		_current_bb = bb.first;
		for (const auto& expr : bb.second) {
			expr->accept(*this);
			if (!_skip) {
				_g.addEdge(_last_but_one, _last);
			} else {
				_skip = false;
			}
		}
#ifndef NDEBUG
		std::cerr << "all statements dumped " << bb.first << std::endl;
#endif
		if (!_outgoing_transitions_handled) {
			_gotos.emplace(_current_bb,_last);
		}
		_outgoing_transitions_handled = false;
	}

#ifndef NDEBUG
	std::cerr << "dumping conditionals" << std::endl;
#endif
	for (auto& cond : _ifs) {
		basic_block bb = cond.first;
		kayrebt::MergeIdentifier decision = cond.second.first;
		std::string& condition = cond.second.second;

		edge ed;
		edge_iterator ei;
		FOR_EACH_EDGE(ed, ei, bb->succs) {
#ifndef NDEBUG
			std::cerr << "Edge: " << ed << std::endl;
			std::cerr << "Edge->flags: " << ed->flags << std::endl;
			std::cerr << "Edge->dest: " << ed->dest << std::endl;
#endif
			auto it =  _init_bb.find(ed->dest);
			if (ed->flags & EDGE_TRUE_VALUE && it != _init_bb.end())
				_g.addGuard(decision,it->second,"["+condition+"]");
			else if (ed->flags & EDGE_FALSE_VALUE && _init_bb.find(ed->dest) != _init_bb.end())
				_g.addGuard(decision,it->second,"[!"+condition+"]");
		}
	}

#ifndef NDEBUG
	std::cerr << "dumping fallthrough" << std::endl;
#endif
	for (auto& fallthru : _gotos) {
		basic_block bb = fallthru.first;
		kayrebt::Identifier& start = fallthru.second;
		edge ed;
		edge_iterator ei;
		FOR_EACH_EDGE(ed, ei, bb->succs) {
#ifndef NDEBUG
			std::cerr << "Edge: " << ed << "(" << ed->src << ")" << std::endl;
			std::cerr << "Edge->flags: " << ed->flags << std::endl;
			std::cerr << "Edge->dest: " << ed->dest << std::endl;
#endif
			auto it = _init_bb.find(ed->dest);
			if (it != _init_bb.end()) {
				_g.addEdge(start,it->second);
			} else if (ed->dest == EXIT_BLOCK_PTR) {
#ifndef NDEBUG
				std::cerr << "Fallthrough to end of function at end of bb " << bb << std::endl;
#endif
				auto end = _g.terminateActivity();
				_g.addNodeAttribute(end,"type",std::string("end_of_activity"));
				_g.addEdge(start,end);
			}
#ifndef NDEBUG
			else
				std::cerr << "Edge going to no known bb! " << ed->dest << std::endl;
#endif
		}
		if (EDGE_COUNT(bb->succs) == 0) {
#ifndef NDEBUG
			std::cerr << "bb without transition!!  " << bb << std::endl;
#endif
			auto end = _g.closeFlow();
			_g.addNodeAttribute(end,"type",std::string("end_of_flow"));
			_g.addEdge(start,end);
		}
	}

	postDumpingPass();
}

void ActivityGraphDumper::postDumpingPass()
{
	auto outputter = [this](std::ostream& out,
			const std::vector<basic_block>& bbs)
	{
		auto printOnePred = [this](std::ostream& out, const basic_block& bb) {
			//std::cerr << "Trying to find bb " << bb << std::endl;
			auto itIfs = _ifs.find(bb);
			if (itIfs != _ifs.cend()) {
				_g.printNodeId(out,itIfs->second.first);
				return;
			}
			auto itGotos = _gotos.find(bb);
			if (itGotos != _gotos.cend()) {
				_g.printNodeId(out,itGotos->second);
				return;
			}
			itGotos = _labelled_gotos.find(bb);
			if (itGotos != _labelled_gotos.cend()) {
				_g.printNodeId(out,itGotos->second);
				return;
			}
			//ups...
		};
		if (!bbs.empty()) {
			out << "\"";
			auto it = bbs.cbegin();
			printOnePred(out,*it);
			for (++it ; it != bbs.cend() ; ++it) {
				out << ",";
				printOnePred(out, *it);
			}
			out << "\"";
		}
	};

	for (const auto& p : _phiNodes) {
		kayrebt::Identifier i = p.first;
		PhiExpr* phi = p.second;
		_g.addNodeAttribute(i,"predecessors",phi->_predsBBs,outputter);
	}

	//All the unnecessary nodes are still there, which we maintained in the
	//graph to to be able to access their attributes are still here at this
	//point, we need to remove them
	_g.purgeGraph();
}

void ActivityGraphDumper::dumpCallExpr(CallExpr* const e)
{
	kayrebt::Identifier i = _g.addAction(e->_built_str);

	addLineAndFileAttributes(i,e->_line,e->_file);
	_g.addNodeAttribute(i,"type",std::string("call"));
	addAttributesForCategory(i,_categorizer(e->_built_str));
	if (_urlFinder && !e->_internalOrDynamicCall) {
#ifndef NDEBUG
		std::cerr << "building call (URLs enabled)" << std::endl;
#endif
		_g.addNodeAttribute(i,"URL",_urlFinder(e->_name->print()));
	} else {
#ifndef NDEBUG
		std::cerr << "building call (URLs disabled)" << std::endl;
#endif
	}
	updateLast(i);
}

void ActivityGraphDumper::dumpPhiExpr(PhiExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building phi" << std::endl;
#endif
	auto i = _g.addAction(e->_built_str);

	addLineAndFileAttributes(i,e->_line,e->_file);
	_g.addNodeAttribute(i,"type",std::string("phi"));
	_g.addNodeAttribute(i,"args",e->_args);
	addAttributesForCategory(i,_categorizer(e->_built_str));
	_phiNodes.emplace_back(i, e);
	updateLast(i);
}

void ActivityGraphDumper::dumpCondExpr(CondExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building cond" << std::endl;
#endif
	auto decision = _g.addDecision();
	addAttributesForCategory(decision,_categorizer(std::string()));
	addLineAndFileAttributes(decision,e->_line,e->_file);
	_g.addNodeAttribute(decision,"type",std::string("cond"));
	std::string condition = e->_lhs->print() + " " +
				Operator::print(e->_op) + " " +
				e->_rhs->print();
	_ifs.emplace(_current_bb,std::make_pair(decision,condition));
	updateLast(decision);
	_outgoing_transitions_handled = true;
}


void ActivityGraphDumper::dumpGotoExpr(GotoExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building goto" << std::endl;
#endif
	auto gotol = _g.addDecision();
	addLineAndFileAttributes(gotol,e->_line,e->_file);
	_g.addNodeAttribute(gotol,"type",std::string("goto"));
	addAttributesForCategory(gotol,_categorizer(std::string()));
	//if the label is available the edge
	//is built right away, otherwise it is delayed
	//until the end of the function dumping
	if (e->_label) {
		auto label = getLabel(e->_label->getUid());
		_g.addEdge(gotol, label);
		_labelled_gotos.emplace(_current_bb, gotol);
		_outgoing_transitions_handled = true;
	}
	updateLast(gotol);
}


void ActivityGraphDumper::dumpLabelExpr(LabelExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building label" << std::endl;
#endif
	auto label = getLabel(e->_label->getUid());
	_g.addNodeAttribute(label,"type",std::string("label"));
	updateLast(label);
}


void ActivityGraphDumper::dumpNopExpr(NopExpr* const)
{
	_skip = true;
}


void ActivityGraphDumper::dumpReturnExpr(ReturnExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building return" << std::endl;
#endif
	if (e->_value) {
		auto ret = _g.addObject(e->_value->print());
		addLineAndFileAttributes(ret,e->_line,e->_file);
		_g.addNodeAttribute(ret,"type",std::string("return"));
		addAttributesForCategory(ret,_categorizer(e->_value->print()));
		updateLast(ret);
	} else {
		_skip = true;
	}
}


void ActivityGraphDumper::dumpSwitchExpr(SwitchExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building switch" << std::endl;
#endif
	auto switchnode = _g.addDecision();
	addLineAndFileAttributes(switchnode,e->_line,e->_file);
	_g.addNodeAttribute(switchnode,"type",std::string("switch"));
	addAttributesForCategory(switchnode,_categorizer(std::string()));

	//Draw the edges for outgoing transitions ahead of time,
	//otherwise their labels would be missed
	for (auto casel : e->_labels) {
		auto l = getLabel(casel->getUid());
		_g.addGuard(switchnode, l, "[" + e->_var->print() + " == " + casel->print() + "]");
		_labelled_gotos.emplace(_current_bb, switchnode);
	}
	_outgoing_transitions_handled = true;

	updateLast(switchnode);
}


const ActivityGraph& ActivityGraphDumper::graph()
{
	return _g;
}

kayrebt::Identifier ActivityGraphDumper::getLabel(unsigned int uid)
{
	auto it = _labels.find(uid);
	if (it == _labels.end()) {
		//we cannot use insert directly instead of
		//find because it would build an unused decision
		//node if the key already exists
		it = _labels.emplace(uid, _g.addDecision()).first;
	}
	return it->second;
}
