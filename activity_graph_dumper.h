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

class BindExpr;
class CaseLabelExpr;
class CondExpr;
class CompoundExpr;
class DeclExpr;
class GotoExpr;
class LabelExpr;
class ModifyExpr;
class NopExpr;
class PreincrementExpr;
class PredecrementExpr;
class PostdecrementExpr;
class PostincrementExpr;
class ReturnExpr;
class Leaf;
class StmtList;
class SwitchExpr;
class Expression;
class Value;

class ActivityGraphDumper : public Dumper
{
	public:
		ActivityGraphDumper();
		void dumpBindExpr(BindExpr* const e) override;
		void dumpCaseLabelExpr(CaseLabelExpr* const e) override;
		void dumpCompoundExpr(CompoundExpr* const e) override;
		void dumpCondExpr(CondExpr* const e) override;
		void dumpDeclExpr(DeclExpr* const e) override;
		void dumpGotoExpr(GotoExpr* const e) override;
		void dumpLabelExpr(LabelExpr* const e) override;
		void dumpLeaf(Leaf* const e) override;
		void dumpModifyExpr(ModifyExpr* const e) override;
		void dumpNopExpr(NopExpr* const e) override;
		void dumpPreincrementExpr(PreincrementExpr* const e) override;
		void dumpPredecrementExpr(PredecrementExpr* const e)  override;
		void dumpPostdecrementExpr(PostdecrementExpr* const e) override;
		void dumpPostincrementExpr(PostincrementExpr* const e) override;
		void dumpReturnExpr(ReturnExpr* const e) override;
		void dumpStmtList(StmtList* const e) override;
		void dumpSwitchExpr(SwitchExpr* const e) override;
		void dumpExpression(Expression* const e) override;
		kayrebt::ActivityGraph& graph();

	private:
		kayrebt::ActivityGraph _g;
		std::stack<std::pair<kayrebt::MergeIdentifier,std::string>> _switchs;
		std::stack<std::vector<kayrebt::Identifier>> _branches;
		std::stack<std::string> _values;
		std::map<std::shared_ptr<Value>,kayrebt::MergeIdentifier> _labels;
		bool _end;
};


#endif
