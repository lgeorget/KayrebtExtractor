#ifndef DUMPER_H
#define DUMPER_H

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

class Dumper
{
	public:
		Dumper() = default;
		virtual void dumpAssignExpr(AssignExpr* const e) = 0;
		virtual void dumpBbList(BbList* const e) = 0;
		virtual void dumpCaseLabelExpr(CaseLabelExpr* const e) = 0;
		virtual void dumpCondExpr(CondExpr* const e) = 0;
		virtual void dumpGotoExpr(GotoExpr* const e) = 0;
		virtual void dumpLabelExpr(LabelExpr* const e) = 0;
		virtual void dumpNopExpr(NopExpr* const e) = 0;
		virtual void dumpReturnExpr(ReturnExpr* const e) = 0;
		virtual void dumpSwitchExpr(SwitchExpr* const e) = 0;
		virtual void dumpExpression(Expression* const e) = 0;
};


#endif
