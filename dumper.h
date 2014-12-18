#ifndef DUMPER_H
#define DUMPER_H

class BindExpr;
class CallExpr;
class CaseLabelExpr;
class CondExpr;
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

class Dumper
{
	public:
		Dumper() = default;
		virtual void dumpBindExpr(BindExpr* const e) = 0;
		virtual void dumpCallExpr(CallExpr* const e) = 0;
		virtual void dumpCaseLabelExpr(CaseLabelExpr* const e) = 0;
		virtual void dumpCondExpr(CondExpr* const e) = 0;
		virtual void dumpDeclExpr(DeclExpr* const e) = 0;
		virtual void dumpGotoExpr(GotoExpr* const e) = 0;
		virtual void dumpLabelExpr(LabelExpr* const e) = 0;
		virtual void dumpLeaf(Leaf* const e) = 0;
		virtual void dumpModifyExpr(ModifyExpr* const e) = 0;
		virtual void dumpNopExpr(NopExpr* const e) = 0;
		virtual void dumpPreincrementExpr(PreincrementExpr* const e) = 0;
		virtual void dumpReturnExpr(ReturnExpr* const e) = 0;
		virtual void dumpStmtList(StmtList* const e) = 0;
		virtual void dumpSwitchExpr(SwitchExpr* const e) = 0;
		virtual void dumpExpression(Expression* const e) = 0;
};


#endif
