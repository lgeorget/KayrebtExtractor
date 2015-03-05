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

using namespace kayrebt;

ActivityGraphDumper::ActivityGraphDumper() : Dumper()
{
	_skip = false;
	_gotos.emplace_back(std::unique_ptr<kayrebt::Identifier>(new kayrebt::Identifier(_g.initialNode())),ENTRY_BLOCK_PTR);
}

void ActivityGraphDumper::updateLast(kayrebt::Identifier&& node)
{
	_last_but_one = std::move(_last);
	_last = std::unique_ptr<kayrebt::Identifier>(new kayrebt::Identifier(node));
}

void ActivityGraphDumper::updateLast(kayrebt::Identifier& node)
{
	_last_but_one = std::move(_last);
	_last = std::unique_ptr<kayrebt::Identifier>(new kayrebt::Identifier(node));
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
	updateLast(_g.addAction(e->_stmt));
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
		updateLast(_g.addAction(label));
	} else {
		updateLast(_g.addObject(label));
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
		_init_bb[bb.first] = std::unique_ptr<kayrebt::MergeIdentifier>(new MergeIdentifier(node));
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
		if (_ifs.find(_current_bb) == _ifs.end()) {
			_gotos.emplace_back(std::move(_last), _current_bb);
		}
		_last = nullptr;
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
#endif
#ifndef NDEBUG
			std::cerr << "Edge->flags: " << ed->flags << std::endl;
#endif
#ifndef NDEBUG
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
			std::cerr << "Edge: " << ed << std::endl;
#endif
#ifndef NDEBUG
			std::cerr << "Edge->flags: " << ed->flags << std::endl;
#endif
#ifndef NDEBUG
			std::cerr << "Edge->dest: " << ed->dest << std::endl;
#endif
			if (_init_bb.find(ed->dest) != _init_bb.end())
				_g.addEdge(start,*(_init_bb[ed->dest]));
		}
	}
}


void ActivityGraphDumper::dumpCallExpr(CallExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building call" << std::endl;
#endif
	updateLast(_g.addAction(e->_built_str));
}

void ActivityGraphDumper::dumpCondExpr(CondExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building cond" << std::endl;
#endif
	auto decision = _g.addDecision();
	std::string condition = e->_lhs->print() + " " +
				Operator::print(e->_op) + " " +
				e->_rhs->print();
	_ifs[_current_bb] = std::make_pair(std::unique_ptr<kayrebt::MergeIdentifier>(new kayrebt::MergeIdentifier(decision)),condition);
	updateLast(decision);
}


void ActivityGraphDumper::dumpGotoExpr(GotoExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building goto" << std::endl;
#endif
	updateLast(_g.addDecision());
}


void ActivityGraphDumper::dumpLabelExpr(LabelExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building label" << std::endl;
#endif
	updateLast(_g.addDecision());
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
	auto endingNode = _g.terminateActivity();
	if (e->_value) {
		auto ret = _g.addObject(e->_value->print());
		_g.addEdge(ret,endingNode);
		updateLast(ret);
	} else {
		updateLast(endingNode);
	}
}


void ActivityGraphDumper::dumpSwitchExpr(SwitchExpr* const e)
{
#ifndef NDEBUG
	std::cerr << "building switch" << std::endl;
#endif
	updateLast(_g.addDecision());
}


const ActivityGraph& ActivityGraphDumper::graph()
{
	_g.simplifyMergeNodes();
	return _g;
}

