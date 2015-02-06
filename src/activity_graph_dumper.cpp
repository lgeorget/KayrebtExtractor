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
#include "bb_list.h"
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

using namespace kayrebt;

ActivityGraphDumper::ActivityGraphDumper() : Dumper()
{
#if 0

	_branches.emplace(1,_g.initialNode());
	_end = false;
	_skip = false;
	_buildLeaf = true;
#endif
}


void ActivityGraphDumper::dumpExpression(Expression* const e)
{
#if 0

	std::cerr << "Discarded: " << *e  << std::endl;
	_skip = true;
#endif
}

void ActivityGraphDumper::dumpAsmExpr(AsmExpr* const e)
{
}

void ActivityGraphDumper::dumpAssignExpr(AssignExpr* const e)
{
#if 0

	ActionIdentifier a(_g.addAction(e->_whatToSet->print() + " = " + e->_newValue->print()));
	_branches.emplace(1,a);
	_end = false;
	_skip = false;
#endif
}

void ActivityGraphDumper::dumpBbList(BbList* const e)
{
#if 0

	std::vector<Identifier> stmtBranch;
	if (!_skip) {
		stmtBranch = std::move(_branches.top());
		_branches.pop();
	} else {
		stmtBranch.push_back(_g.addDecision());
	}
	_skip = false;

	bool end = _end;
	for (auto expr : e->_exprs) {
		expr->accept(*this);
		if (!_skip)
		{
			auto after = _branches.top();
			_branches.pop();
			if (!end && !stmtBranch.empty())
				_g.addEdge(stmtBranch.back(), after.front());
			std::move(after.begin(), after.end(), std::back_inserter(stmtBranch));
		}
		end = _end;
	}
	_branches.push(std::move(stmtBranch));
	//_end is untouched
	_skip = false;
#endif
}


void ActivityGraphDumper::dumpCallExpr(CallExpr* const e)
{
}

void ActivityGraphDumper::dumpCondExpr(CondExpr* const e)
{
#if 0

	bool end;
	std::vector<Identifier> condBranch;
	auto decision = _g.addDecision();
	auto fusion = _g.addDecision();
	condBranch.push_back(decision);

	_buildLeaf = false;
	e->_cond->accept(*this);
	std::string condition = std::move(_values.top());
	_values.pop();
	_buildLeaf = true;

	_skip = true;
	e->_then->accept(*this);
	std::vector<Identifier> bthen;
	bthen = std::move(_branches.top());
	_g.addGuard(decision, bthen.front(), "[" + condition + "]");
	if (!_end)
		_g.addEdge(bthen.back(), fusion);
	std::move(bthen.begin(), bthen.end(), std::back_inserter(condBranch));
	_branches.pop();
	end = _end;

	if (e->_else) {
		_skip = true;
		e->_else->accept(*this);
		std::vector<Identifier> belse(std::move(_branches.top()));
		_g.addGuard(decision, belse.front(), "[!" + condition + "]");
		end &= _end;
		if (!_end)
			_g.addEdge(belse.back(), fusion);
		std::move(belse.begin(), belse.end(), std::back_inserter(condBranch));
		_branches.pop();
	} else {
		end = false;
		_g.addGuard(decision, fusion, "[!" + condition + "]");
	}
	_end = end;
	condBranch.push_back(fusion);
	_branches.push(std::move(condBranch));
	_skip = false;
#endif
}


void ActivityGraphDumper::dumpGotoExpr(GotoExpr* const e)
{
#if 0

	std::cerr << "Looking for label " << e->_label->print() << std::endl;
	auto label = _labels.find(*(e->_label));
	if (label == _labels.end()) {
		std::cerr << "Not found!" << std::endl;
		MergeIdentifier labelNode(_g.addDecision());
		label = _labels.insert(std::make_pair(*(e->_label),labelNode)).first;
	}
	MergeIdentifier gotoNode(_g.addDecision());
	_g.addEdge(gotoNode, label->second);
	_branches.emplace(1,gotoNode);
	_end = true;
	_skip = false;
#endif
}


void ActivityGraphDumper::dumpLabelExpr(LabelExpr* const e)
{
#if 0

	std::cerr << "Check for already existing label " << e->_label->print() << std::endl;
	auto label = _labels.find(*(e->_label));
	if (label == _labels.end()) {
		std::cerr << "Label not found" << std::endl;
		MergeIdentifier labelNode(_g.addDecision());
		label = _labels.insert(std::make_pair(*(e->_label),labelNode)).first;
		_branches.emplace(1,labelNode);
	} else {
		MergeIdentifier& labelNode = label->second;
		_branches.emplace(1,labelNode);
	}
	_end = false;
	_skip = false;
#endif
}


void ActivityGraphDumper::dumpNopExpr(NopExpr* const e)
{
#if 0

	_skip = true;
#endif
}


void ActivityGraphDumper::dumpReturnExpr(ReturnExpr* const e)
{
#if 0

	std::vector<Identifier> returnBranch;
	auto endingNode = _g.terminateActivity();
	if (e->_value) {
		e->_value->accept(*this);
		returnBranch = std::move(_branches.top());
		_branches.pop();
		_g.addEdge(returnBranch.back(),endingNode);
	}
	returnBranch.push_back(endingNode);
	_branches.push(std::move(returnBranch));
	_end = true;
	_skip = false;
#endif
}



void ActivityGraphDumper::dumpSwitchExpr(SwitchExpr* const e)
{
#if 0

	_buildLeaf = false;
	e->_cond->accept(*this);
	auto cond = _g.addDecision();
	_switchs.push(std::make_pair(cond,_values.top()));
	_values.pop();
	_buildLeaf = true;

	std::vector<Identifier> switchBranch;
	switchBranch.push_back(cond);
	e->_body->accept(*this);
	std::move(_branches.top().begin(), _branches.top().end(), std::back_inserter(switchBranch));
	_branches.pop();
	_switchs.pop();

	_branches.push(std::move(switchBranch));
	//_end is untouched
	_skip = false;
#endif
}


const ActivityGraph& ActivityGraphDumper::graph()
{

	_g.simplifyMergeNodes();
	return _g;
}

