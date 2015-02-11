#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <tuple>
#include <gcc-plugin.h>
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
	_branches.push(_g.initialNode());
	_end = false;
	_skip = false;
}


void ActivityGraphDumper::dumpExpression(Expression* const e)
{
	std::cerr << "Discarded: " << *e  << std::endl;
	_skip = true;
}

void ActivityGraphDumper::dumpAsmExpr(AsmExpr* const e)
{
	std::cerr << "building asm" << std::endl;
	auto assemb = _g.addAction(e->_stmt);
	_branches.push(assemb);
	_end = false;
}

void ActivityGraphDumper::dumpAssignExpr(AssignExpr* const e)
{
	std::cerr << "building assign" << std::endl;
	std::string label = e->_rhs2 ?
		e->_whatToSet->print() + " = " +
		e->_rhs1->print() + Operator::print(e->_op) +
		e->_rhs2->print()
		:
		e->_whatToSet->print() + " = " +
		e->_rhs1->print();

	if (e->_anonymous) {
		auto assig = _g.addAction(label);
		_branches.push(assig);
	} else {
		auto assig = _g.addObject(label);
		_branches.push(assig);
	}
	_end = false;
}

void ActivityGraphDumper::dumpFunctionBody(FunctionBody* const e)
{
	std::cerr << "function body" << std::endl;
	bool end = false;
	auto before = _branches.top();
	for (auto expr : e->_exprs) {
		std::cerr << "building stmt" << std::endl;
		expr->accept(*this);
		std::cerr << "built stmt" << std::endl;
		if (!_skip) {
			auto after = _branches.top();
			if (!end)
				_g.addEdge(before, after);
			end = _end;
			before = after;
		} else {
			_skip = false;
		}
	}
}


void ActivityGraphDumper::dumpCallExpr(CallExpr* const e)
{
	std::cerr << "building call" << std::endl;
	auto call = _g.addAction(e->_built_str);
	_branches.push(call);
	_end = false;
}

void ActivityGraphDumper::dumpCondExpr(CondExpr* const e)
{
	std::cerr << "building cond" << std::endl;
	auto decision = _g.addDecision();
	std::string condition = e->_lhs->print() + " " +
				Operator::print(e->_op) + " " +
				e->_rhs->print();

	auto bthen = _labels.find(*(e->_then));
	if (bthen == _labels.end()) {
		std::cerr << "Then-branch not found!" << std::endl;
		MergeIdentifier labelNode(_g.addDecision());
		bthen = _labels.insert(std::make_pair(*(e->_then),labelNode)).first;
	}
	_g.addGuard(decision, bthen->second, "[" + condition + "]");

	auto belse = _labels.find(*(e->_else));
	if (belse == _labels.end()) {
		std::cerr << "Else-branch not found!" << std::endl;
		MergeIdentifier labelNode(_g.addDecision());
		belse = _labels.insert(std::make_pair(*(e->_else),labelNode)).first;
	}
	_g.addGuard(decision, belse->second, "[!" + condition + "]");
	_branches.push(decision);
	_end = true;
}


void ActivityGraphDumper::dumpGotoExpr(GotoExpr* const e)
{
	std::cerr << "building goto" << std::endl;
	auto label = _labels.find(*(e->_label));
	if (label == _labels.end()) {
		std::cerr << "Not found!" << std::endl;
		MergeIdentifier labelNode(_g.addDecision());
		label = _labels.insert(std::make_pair(*(e->_label),labelNode)).first;
	}
	MergeIdentifier gotoNode(_g.addDecision());
	_g.addEdge(gotoNode, label->second);
	_branches.push(gotoNode);
	_end = true;
}


void ActivityGraphDumper::dumpLabelExpr(LabelExpr* const e)
{
	std::cerr << "building label" << std::endl;
	std::cerr << "Check for already existing label " << e->_label->print() << std::endl;
	auto label = _labels.find(*(e->_label));
	if (label == _labels.end()) {
		std::cerr << "Label not found" << std::endl;
		MergeIdentifier labelNode(_g.addDecision());
		label = _labels.insert(std::make_pair(*(e->_label),labelNode)).first;
		_branches.push(labelNode);
	} else {
		MergeIdentifier& labelNode = label->second;
		_branches.push(labelNode);
	}
	_end = false;
}


void ActivityGraphDumper::dumpNopExpr(NopExpr* const e)
{
	_skip = true;
}


void ActivityGraphDumper::dumpReturnExpr(ReturnExpr* const e)
{
	std::cerr << "building return" << std::endl;
	auto endingNode = _g.terminateActivity();
	if (e->_value) {
		auto ret = _g.addObject(e->_value->print());
		_g.addEdge(ret,endingNode);
		_branches.push(ret);
	} else {
		_branches.push(endingNode);
	}
	_end = true;
}


void ActivityGraphDumper::dumpSwitchExpr(SwitchExpr* const e)
{
	std::cerr << "building switch" << std::endl;
	auto cond = _g.addDecision();

	for (auto label_ptr : e->_labels) {
		auto label = _labels.find(*label_ptr);
		if (label == _labels.end()) {
			std::cerr << "Label not found" << std::endl;
			MergeIdentifier labelNode(_g.addDecision());
			label = _labels.insert(std::make_pair(*label_ptr,labelNode)).first;
		}
		_g.addGuard(cond, label->second, e->_var->print() + " == " + label_ptr->print());
	}
	_branches.push(cond);
	_end = true;
}


const ActivityGraph& ActivityGraphDumper::graph()
{
	_g.simplifyMergeNodes();
	return _g;
}

