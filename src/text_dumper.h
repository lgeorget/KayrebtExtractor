#ifndef TEXT_DUMPER_H
#define TEXT_DUMPER_H

#include <iostream>
#include "dumper.h"

class AssignExpr;
class BbList;
class CallExpr;
class CondExpr;
class GotoExpr;
class LabelExpr;
class NopExpr;
class ReturnExpr;
class SwitchExpr;
class Expression;

class TextDumper : public Dumper
{
	public:
		TextDumper(std::ostream* const out = &std::cout, bool withHeader = true);
		void dumpAsmExpr(AsmExpr* const e) override;
		void dumpAssignExpr(AssignExpr* const e) override;
		void dumpBbList(BbList* const e) override;
		void dumpCallExpr(CallExpr* const e) override;
		void dumpCondExpr(CondExpr* const e) override;
		void dumpGotoExpr(GotoExpr* const e) override;
		void dumpLabelExpr(LabelExpr* const e) override;
		void dumpNopExpr(NopExpr* const e) override;
		void dumpReturnExpr(ReturnExpr* const e) override;
		void dumpSwitchExpr(SwitchExpr* const e) override;
		void dumpExpression(Expression* const e) override;

	private:
		void header();
		std::ostream* const _out;
		bool _withHeader;
};


#endif
