#ifndef ACTIVITY_DUMPER_H
#define ACTIVITY_DUMPER_H

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <utility>
#include <activity_graph.h>
#include "dumper.h"
#include "label.h"

class AssignExpr;
class BbList;
class CaseLabelExpr;
class CondExpr;
class GotoExpr;
class LabelExpr;
class NopExpr;
class ReturnExpr;
class SwitchExpr;
class Expression;

class ActivityGraphDumper : public Dumper
{
	public:
		ActivityGraphDumper();
		void dumpAssignExpr(AssignExpr* const e) override;
		void dumpBbList(BbList* const e) override;
		void dumpCaseLabelExpr(CaseLabelExpr* const e) override;
		void dumpCondExpr(CondExpr* const e) override;
		void dumpGotoExpr(GotoExpr* const e) override;
		void dumpLabelExpr(LabelExpr* const e) override;
		void dumpNopExpr(NopExpr* const e) override;
		void dumpReturnExpr(ReturnExpr* const e) override;
		void dumpSwitchExpr(SwitchExpr* const e) override;
		void dumpExpression(Expression* const e) override;

	private:
		kayrebt::ActivityGraph _g;
		std::stack<std::pair<kayrebt::MergeIdentifier,std::string>> _switchs;
		std::stack<std::vector<kayrebt::Identifier>> _branches;
		std::stack<std::string> _values;
		std::map<Value,kayrebt::MergeIdentifier> _labels;
		bool _end;
		bool _skip;
		bool _buildLeaf;
};


#endif
