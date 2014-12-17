#ifndef DUMPER_H
#define DUMPER_H

#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>

class BooleanExpr;
class CallExpr;
class CondExpr;
class CompareExpr;
class DeclExpr;
class GotoExpr;
class LabelExpr;
class ModifyExpr;
class PreincrementExpr;
class ReturnExpr;
class SwitchExpr;
class Expression;

class Dumper
{
	public:
		Dumper(std::ostream* const out = &std::cout, bool withHeader = true);
		void dumpBooleanExpr(BooleanExpr* const e);
		void dumpCallExpr(CallExpr* const e);
		void dumpCondExpr(CondExpr* const e);
		void dumpCompareExpr(CompareExpr* const e);
		void dumpDeclExpr(DeclExpr* const e);
		void dumpGotoExpr(GotoExpr* const e);
		void dumpLabelExpr(LabelExpr* const e);
		void dumpModifyExpr(ModifyExpr* const e);
		void dumpPreincrementExpr(PreincrementExpr* const e);
		void dumpReturnExpr(ReturnExpr* const e);
		void dumpExpression(Expression* const e);

	private:
		void header();
		std::ostream* const _out;
		bool _withHeader;
};


#endif
