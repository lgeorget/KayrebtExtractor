#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <tuple>
#include <gcc-plugin.h>
#include <activity_graph.h>
#include "activity_graph_dumper.h"
#include "assign_expr.h"
#include "bb_list.h"
#include "call_expr.h"
#include "case_label_expr.h"
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
	_branches.emplace(1,_g.initialNode());
	_end = false;
	_skip = false;
	_buildLeaf = true;
}

void ActivityGraphDumper::dumpExpression(Expression* const e)
{
	std::cerr << "Discarded: " << *e  << std::endl;
	_skip = true;
}

void ActivityGraphDumper::dumpModifyExpr(ModifyExpr* const e)
{
	ActionIdentifier a(_g.addAction(e->_whatToSet->print() + " = " + e->_newValue->print()));
	_branches.emplace(1,a);
	_end = false;
	_skip = false;
}

void ActivityGraphDumper::dumpBbList(BbList* const e)
{
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
}

void ActivityGraphDumper::dumpCaseLabelExpr(CaseLabelExpr* const e)
{
	MergeIdentifier node = _g.addDecision();
	std::string condition;
	if (e->_lowValue)
		if (e->_highValue)
			condition = "[" + _switchs.top().second + " between " + e->_lowValue->print() + " and " + e->_highValue->print() + "]";
		else
			condition = "[" + _switchs.top().second + " == " + e->_lowValue->print() + "]";
	else
		condition = "[otherwise]";

	_g.addGuard(_switchs.top().first, node, condition);
	_branches.emplace(1,node);
	_end = false;
	_skip = false;
}

void ActivityGraphDumper::dumpCondExpr(CondExpr* const e)
{
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
}

void ActivityGraphDumper::dumpGotoExpr(GotoExpr* const e)
{
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
}

void ActivityGraphDumper::dumpLabelExpr(LabelExpr* const e)
{
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
}

void ActivityGraphDumper::dumpNopExpr(NopExpr* const e)
{
	_skip = true;
}

void ActivityGraphDumper::dumpReturnExpr(ReturnExpr* const e)
{
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
}


void ActivityGraphDumper::dumpSwitchExpr(SwitchExpr* const e)
{
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
}

ActivityGraph& ActivityGraphDumper::graph()
{
	_g.simplifyMergeNodes();
	return _g;
}
