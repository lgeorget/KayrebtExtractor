#ifndef TEXT_DUMPER_H
#define TEXT_DUMPER_H

#include <iostream>
#include "dumper.h"

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

class TextDumper : public Dumper
{
	public:
		TextDumper(std::ostream* const out = &std::cout, bool withHeader = true);
		void dumpBindExpr(BindExpr* const e) override;
		void dumpCaseLabelExpr(CaseLabelExpr* const e) override;
		void dumpCondExpr(CondExpr* const e) override;
		void dumpCompoundExpr(CompoundExpr* const e) override;
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
		void header();
		std::ostream* const _out;
		bool _withHeader;
};


#endif
