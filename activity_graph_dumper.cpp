#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <tuple>
#include <gcc-plugin.h>
#include "activity_graph_dumper.h"
#include "bind_expr.h"
#include "call_expr.h"
#include "case_label_expr.h"
#include "cond_expr.h"
#include "compound_expr.h"
#include "decl_expr.h"
#include "expression.h"
#include "goto_expr.h"
#include "label_expr.h"
#include "leaf.h"
#include "modify_expr.h"
#include "nop_expr.h"
#include "preincrement_expr.h"
#include "predecrement_expr.h"
#include "postincrement_expr.h"
#include "postdecrement_expr.h"
#include "return_expr.h"
#include "stmt_list.h"
#include "switch_expr.h"
#include "dumper.h"
#include <activity_graph.h>
#include "label.h"

using namespace kayrebt;

ActivityGraphDumper::ActivityGraphDumper() : Dumper()
{
	std::cerr << "Dumping" << std::endl;
	_branches.push(std::vector<Identifier>(1,_g.initialNode()));
	_end = false;
	std::cerr << "Ready" << std::endl;
}

void ActivityGraphDumper::dumpExpression(Expression* const e)
{
}

void ActivityGraphDumper::dumpBindExpr(BindExpr* const e)
{
	e->_body->accept(*this);
}

void ActivityGraphDumper::dumpCaseLabelExpr(CaseLabelExpr* const e)
{
	ActionIdentifier node = _g.addAction(e->_label->print());
	_g.addGuard(_switchs.top().first, node, "[" + _switchs.top().second + " == " + e->_label->print() + "]");
	_branches.emplace(1,node);
	_end = false;
}

void ActivityGraphDumper::dumpCondExpr(CondExpr* const e)
{
	bool end;
	std::vector<Identifier> condBranch;
	auto decision = _g.addDecision();
	auto fusion = _g.addDecision();

	condBranch.push_back(decision);
	e->_cond->accept(*this);
	std::string condition = std::move(_values.top());
	_values.pop();
	e->_then->accept(*this);

	std::vector<Identifier> bthen(std::move(_branches.top()));
	_g.addGuard(decision, bthen.front(), "[" + condition + "]");
	end = _end;
	if (!_end)
		_g.addEdge(bthen.back(), fusion);
	std::move(bthen.begin(), bthen.end(), std::back_inserter(condBranch));
	_branches.pop();

	if (e->_else) {
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
}

void ActivityGraphDumper::dumpCompoundExpr(CompoundExpr* const e)
{
	std::vector<Identifier> compoundBranch;

	e->_first->accept(*this);
	std::move(_branches.top().begin(), _branches.top().end(), std::back_inserter(compoundBranch));
	_branches.pop();

	e->_second->accept(*this);
	std::vector<Identifier> second(std::move(_branches.top()));
	_g.addEdge(compoundBranch.back(),second.front());
	std::move(second.begin(), second.end(), std::back_inserter(compoundBranch));
	_branches.pop();

	_branches.push(compoundBranch);
}

void ActivityGraphDumper::dumpDeclExpr(DeclExpr* const e)
{
	std::unique_ptr<ObjectIdentifier> o;
	if (e->_init) {
		o = std::unique_ptr<ObjectIdentifier>(new ObjectIdentifier(_g.addObject(e->_name->print() + " = " + e->_init->print())));
	} else {
		o = std::unique_ptr<ObjectIdentifier>(new ObjectIdentifier(_g.addObject(e->_name->print())));
	}
	_branches.push(std::vector<Identifier>(1,*o));
	_end = false;
}

void ActivityGraphDumper::dumpGotoExpr(GotoExpr* const e)
{
	auto label = _labels.find(e->_label);
	if (label == _labels.end()) {
		MergeIdentifier labelNode(_g.addDecision());
		label = _labels.insert(std::make_pair(e->_label,labelNode)).first;
	}
	MergeIdentifier gotoNode(_g.addDecision());
	_g.addEdge(gotoNode, label->second);
	_branches.push(std::vector<Identifier>(1,gotoNode));
	_end = true;
}

void ActivityGraphDumper::dumpLabelExpr(LabelExpr* const e)
{
	auto label = _labels.find(e->_label);
	if (label == _labels.end()) {
		MergeIdentifier labelNode(_g.addDecision());
		label = _labels.insert(std::make_pair(e->_label,labelNode)).first;
		_branches.push(std::vector<Identifier>(1,labelNode));
	} else {
		MergeIdentifier& labelNode = label->second;
		_branches.push(std::vector<Identifier>(1,labelNode));
	}
	_end = false;
}

void ActivityGraphDumper::dumpLeaf(Leaf* const e)
{
	ObjectIdentifier o(_g.addObject(e->_val->print()));
	_branches.push(std::vector<Identifier>(1,o));
	_values.push(e->_val->print());
	_end = false;
}

void ActivityGraphDumper::dumpModifyExpr(ModifyExpr* const e)
{
	ActionIdentifier a(_g.addAction(e->_whatToSet->print() + " = " + e->_newValue->print()));
	_branches.push(std::vector<Identifier>(1,a));
	_end = false;
}

void ActivityGraphDumper::dumpNopExpr(NopExpr* const e)
{
}

void ActivityGraphDumper::dumpPreincrementExpr(PreincrementExpr* const e)
{
	ActionIdentifier a(_g.addAction("++" + e->_variable->print()));
	_branches.push(std::vector<Identifier>(1,a));
	_end = false;
}

void ActivityGraphDumper::dumpPredecrementExpr(PredecrementExpr* const e)
{
	ActionIdentifier a(_g.addAction("--" + e->_variable->print()));
	_branches.push(std::vector<Identifier>(1,a));
	_end = false;
}

void ActivityGraphDumper::dumpPostdecrementExpr(PostdecrementExpr* const e)
{
	ActionIdentifier a(_g.addAction(e->_variable->print() + "--"));
	_branches.push(std::vector<Identifier>(1,a));
	_end = false;
}

void ActivityGraphDumper::dumpPostincrementExpr(PostincrementExpr* const e)
{
	ActionIdentifier a(_g.addAction(e->_variable->print() + "++"));
	_branches.push(std::vector<Identifier>(1,a));
	_end = false;
}

void ActivityGraphDumper::dumpReturnExpr(ReturnExpr* const e)
{
	if (e->_value)
		e->_value->accept(*this);
	_branches.push(std::vector<Identifier>(1,_g.terminateActivity()));
	_end = true;
}

void ActivityGraphDumper::dumpStmtList(StmtList* const e)
{
	std::vector<Identifier> stmtBranch(_branches.top());
	_branches.pop();

	bool end = _end;
	for (auto expr : e->_exprs) {
		expr->accept(*this);
		auto after = _branches.top();
		_branches.pop();
		if (!end)
			_g.addEdge(stmtBranch.back(), after.front());
		end = _end;
		std::move(after.begin(), after.end(), std::back_inserter(stmtBranch));
	}
	_branches.push(std::move(stmtBranch));
	//_end is untouched
}

void ActivityGraphDumper::dumpSwitchExpr(SwitchExpr* const e)
{
	e->_cond->accept(*this);
	_branches.pop(); // condition is not represented as a node
			 // so discard it
	auto cond = _g.addDecision();
	_switchs.push(std::make_pair(cond,_values.top()));
	_values.pop();

	std::vector<Identifier> switchBranch;
	switchBranch.push_back(cond);
	e->_body->accept(*this);
	auto switchBody = _branches.top();
	_branches.pop();
	std::move(switchBody.begin(), switchBody.end(), std::back_inserter(switchBranch));
	_switchs.pop();

	_branches.push(std::move(switchBranch));
	//_end is untouched
}

ActivityGraph& ActivityGraphDumper::graph()
{
	return _g;
}
