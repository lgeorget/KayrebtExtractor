#ifndef DUMPER_H
#define DUMPER_H

#include <iostream>
#include <gcc-plugin.h>
#include <tree.h>

class CallExpr;
class CondExpr;
class DeclExpr;
class GotoExpr;
class LabelExpr;
class ModifyExpr;
class PreincrementExpr;
class ReturnExpr;
class Leaf;
class SwitchExpr;
class Expression;

class Dumper
{
	public:
		Dumper(std::ostream* const out = &std::cout, bool withHeader = true);
		void dumpCallExpr(CallExpr* const e);
		void dumpCondExpr(CondExpr* const e);
		void dumpDeclExpr(DeclExpr* const e);
		void dumpGotoExpr(GotoExpr* const e);
		void dumpLabelExpr(LabelExpr* const e);
		void dumpModifyExpr(ModifyExpr* const e);
		void dumpPreincrementExpr(PreincrementExpr* const e);
		void dumpReturnExpr(ReturnExpr* const e);
		void dumpLeaf(Leaf* const e);
		void dumpSwitchExpr(SwitchExpr* const e);
		void dumpExpression(Expression* const e);

	private:
		void header();
		std::ostream* const _out;
		bool _withHeader;
};


#endif
