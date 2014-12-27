#ifndef ACTIVITY_DUMPER_H
#define ACTIVITY_DUMPER_H

#include <boost/graph/adjacency_list.hpp>
#include "graph.h"

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
class ReturnExpr;
class Leaf;
class StmtList;
class SwitchExpr;
class Expression;

class ActivityGraphDumper
{
	public:
		ActivityGraphDumper() = default;
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
		void dumpReturnExpr(ReturnExpr* const e) override;
		void dumpStmtList(StmtList* const e) override;
		void dumpSwitchExpr(SwitchExpr* const e) override;
		void dumpExpression(Expression* const e) override;

	private:
		void updateCurrent();
		ActivityGraph _g();
		graph_traits<adjacency_list>::vertex_iterator _currentNode;

};


#endif
