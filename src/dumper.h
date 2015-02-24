#ifndef DUMPER_H
#define DUMPER_H

class AsmExpr;
class AssignExpr;
class FunctionBody;
class CallExpr;
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
		virtual void dumpAsmExpr(AsmExpr* const e) = 0;
		virtual void dumpAssignExpr(AssignExpr* const e) = 0;
		virtual void dumpFunctionBody(FunctionBody* const e) = 0;
		virtual void dumpCallExpr(CallExpr* const e) = 0;
		virtual void dumpCondExpr(CondExpr* const e) = 0;
		virtual void dumpGotoExpr(GotoExpr* const e) = 0;
		virtual void dumpLabelExpr(LabelExpr* const e) = 0;
		virtual void dumpNopExpr(NopExpr* const e) = 0;
		virtual void dumpReturnExpr(ReturnExpr* const e) = 0;
		virtual void dumpSwitchExpr(SwitchExpr* const e) = 0;
		virtual void dumpExpression(Expression* const e) = 0;
};


#endif
