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
#include <memory>
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

ActivityGraphDumper::ActivityGraphDumper(const Configurator& global_config,
	const std::string& file, int line) :
	Dumper(), _categorizer(global_config.getCategorizer()), _urlFinder()
{
	_g.setFile(file);
	_g.setLine(line);
	if (global_config.shallDumpUrls())
		_urlFinder.open(global_config.getDbFile().c_str(), global_config.getDbName().c_str());
	_skip = false;
	_gotos.emplace_back(make_unique<kayrebt::Identifier>(_g.initialNode()),ENTRY_BLOCK_PTR);
}

void ActivityGraphDumper::updateLast(kayrebt::Identifier&& node)
{
	_last_but_one = std::move(_last);
	_last = make_unique<kayrebt::Identifier>(node);
}

void ActivityGraphDumper::updateLast(kayrebt::Identifier& node)
{
	_last_but_one = std::move(_last);
	_last = make_unique<kayrebt::Identifier>(node);
}

void ActivityGraphDumper::dumpExpression(Expression* const e)
{
#ifndef NDEBUG
	std::cerr << "Discarded: " << *e  << std::endl;
#endif
	_skip = true;
}

void ActivityGraphDumper::dumpAsmExpr(AsmExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building asm" << std::endl;
#endif
	updateLast(_g.addAction(e->_stmt,e->_file,e->_line,_categorizer(e->_stmt)));
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
		e->_rhs1->print();

	if (e->_anonymous) {
		updateLast(_g.addAction(label,e->_file,e->_line,_categorizer(label)));
	} else {
		updateLast(_g.addObject(label,e->_file,e->_line,_categorizer(label)));
	}
}

void ActivityGraphDumper::dumpFunctionBody(FunctionBody* const e)
{
#ifndef NDEBUG
	std::cerr << "function body" << std::endl;
#endif
	for (auto bb : e->_bb) {
		auto node = _g.addDecision();
		updateLast(node);
		_init_bb[bb.first] = make_unique<kayrebt::MergeIdentifier>(node);
#ifndef NDEBUG
		std::cerr << "dumping basic block " << bb.first << std::endl;
#endif
		_current_bb = bb.first;
		for (auto expr : bb.second) {
			expr->accept(*this);
			if (!_skip) {
				if (_last_but_one && _last)
					_g.addEdge(*_last_but_one, *_last);
			} else {
				_skip = false;
			}
		}
		if (!_outgoing_transitions_handled) {
			_gotos.emplace_back(std::move(_last), _current_bb);
		}
		_last = nullptr;
		_outgoing_transitions_handled = false;
	}

#ifndef NDEBUG
	std::cerr << "dumping conditionals" << std::endl;
#endif
	for (auto& cond : _ifs) {
		basic_block bb = cond.first;
		kayrebt::MergeIdentifier& decision = *(cond.second.first);
		std::string& condition = cond.second.second;

		edge ed;
		edge_iterator ei;
		FOR_EACH_EDGE(ed, ei, bb->succs) {
#ifndef NDEBUG
			std::cerr << "Edge: " << ed << std::endl;
			std::cerr << "Edge->flags: " << ed->flags << std::endl;
			std::cerr << "Edge->dest: " << ed->dest << std::endl;
#endif
			if (ed->flags & EDGE_TRUE_VALUE && _init_bb.find(ed->dest) != _init_bb.end())
				_g.addGuard(decision,*(_init_bb[ed->dest]),"["+condition+"]");
			else if (ed->flags & EDGE_FALSE_VALUE && _init_bb.find(ed->dest) != _init_bb.end())
				_g.addGuard(decision,*(_init_bb[ed->dest]),"[!"+condition+"]");
		}
	}

#ifndef NDEBUG
	std::cerr << "dumping fallthrough" << std::endl;
#endif
	for (auto& fallthru : _gotos) {
		basic_block bb = fallthru.second;
		kayrebt::Identifier& start = *(fallthru.first);
		edge ed;
		edge_iterator ei;
		FOR_EACH_EDGE(ed, ei, bb->succs) {
#ifndef NDEBUG
			std::cerr << "Edge: " << ed << "(" << ed->src << ")" << std::endl;
			std::cerr << "Edge->flags: " << ed->flags << std::endl;
			std::cerr << "Edge->dest: " << ed->dest << std::endl;
#endif
			if (_init_bb.find(ed->dest) != _init_bb.end()) {
				_g.addEdge(start,*(_init_bb[ed->dest]));
			} else if (ed->dest == EXIT_BLOCK_PTR) {
#ifndef NDEBUG
				std::cerr << "Fallthrough to end of function at end of bb " << bb << std::endl;
#endif
				_g.addEdge(start,_g.terminateActivity());
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
			_g.addEdge(start,_g.terminateActivity());
		}
	}
}


void ActivityGraphDumper::dumpCallExpr(CallExpr* const e)
{
	std::string fn;
	if (e->_name)
		fn = e->_name->print();
	if (_urlFinder && !fn.empty()) {
#ifndef NDEBUG
		std::cerr << "building call (URLs enabled)" << std::endl;
#endif
		updateLast(_g.addAction(e->_built_str,e->_file,e->_line, _categorizer(e->_built_str), _urlFinder(fn)));
	} else {
#ifndef NDEBUG
		std::cerr << "building call (URLs disabled)" << std::endl;
#endif
		updateLast(_g.addAction(e->_built_str,e->_file,e->_line, _categorizer(e->_built_str)));
	}
}

void ActivityGraphDumper::dumpCondExpr(CondExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building cond" << std::endl;
#endif
	auto decision = _g.addDecision(e->_file,e->_line);
	std::string condition = e->_lhs->print() + " " +
				Operator::print(e->_op) + " " +
				e->_rhs->print();
	_ifs[_current_bb] = std::make_pair(make_unique<kayrebt::MergeIdentifier>(decision),condition);
	updateLast(decision);
	_outgoing_transitions_handled = true;
}


void ActivityGraphDumper::dumpGotoExpr(GotoExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building goto" << std::endl;
#endif
	auto gotol = _g.addDecision(e->_file,e->_line);
	//if the label is available the edge
	//is built right away, otherwise it is delayed
	//until the end of the function dumping
	if (e->_label) {
		auto label = getLabel(e->_label->getUid());
		_g.addEdge(gotol, label);
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
	updateLast(label);
}


void ActivityGraphDumper::dumpNopExpr(NopExpr* const e)
{
	_skip = true;
}


void ActivityGraphDumper::dumpReturnExpr(ReturnExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building return" << std::endl;
#endif
	if (e->_value) {
		auto ret = _g.addObject(e->_value->print(),e->_file,e->_line);
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
	auto switchnode = _g.addDecision(e->_file,e->_line);

	//Draw the edges for outgoing transitions ahead of time,
	//otherwise their labels would be missed
	for (auto casel : e->_labels) {
		auto l = getLabel(casel->getUid());
		_g.addGuard(switchnode, l, "[" + e->_var->print() + " == " + casel->print() + "]");
	}
	_outgoing_transitions_handled = true;

	updateLast(switchnode);
}


const ActivityGraph& ActivityGraphDumper::graph()
{
	_g.simplifyMergeNodes();
	return _g;
}

kayrebt::Identifier ActivityGraphDumper::getLabel(unsigned int uid)
{
	auto it = _labels.find(uid);
	if (it == _labels.end()) {
		//we cannot use insert directly instead of
		//find because it would build an unused decision
		//node if the key already exist
		it = _labels.emplace(uid, _g.addDecision()).first;
	}
	return it->second;
}
