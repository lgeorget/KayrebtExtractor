#ifndef ACTIVITY_DUMPER_H
#define ACTIVITY_DUMPER_H

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <utility>
#include <memory>
#include <activity_graph.h>
#include "dumper.h"
#include "label.h"

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

class ActivityGraphDumper : public Dumper
{
	public:
		ActivityGraphDumper();
		void dumpAsmExpr(AsmExpr* const e) override;
		void dumpAssignExpr(AssignExpr* const e) override;
		void dumpFunctionBody(FunctionBody* const e) override;
		void dumpCallExpr(CallExpr* const e) override;
		void dumpCondExpr(CondExpr* const e) override;
		void dumpGotoExpr(GotoExpr* const e) override;
		void dumpLabelExpr(LabelExpr* const e) override;
		void dumpNopExpr(NopExpr* const e) override;
		void dumpReturnExpr(ReturnExpr* const e) override;
		void dumpSwitchExpr(SwitchExpr* const e) override;
		void dumpExpression(Expression* const e) override;
		const kayrebt::ActivityGraph& graph();

	private:
		kayrebt::ActivityGraph _g;
		std::unique_ptr<kayrebt::Identifier> _last;
		std::unique_ptr<kayrebt::Identifier> _last_but_one;
		std::stack<std::string> _values;
		std::map<basic_block,std::unique_ptr<kayrebt::MergeIdentifier>> _init_bb;
		std::map<basic_block,std::pair<std::unique_ptr<kayrebt::MergeIdentifier>,std::string>> _ifs;
		std::vector<std::pair<std::unique_ptr<kayrebt::Identifier>,basic_block>> _gotos;
		bool _skip;
		basic_block _current_bb;

		void updateLast(kayrebt::Identifier&& node);
		void updateLast(kayrebt::Identifier& node);
};


#endif
