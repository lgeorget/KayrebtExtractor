#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <memory>
#include <gcc-plugin.h>
#include "text_dumper.h"
#include "operator.h"
#include "asm_expr.h"
#include "assign_expr.h"
#include "bb_list.h"
#include "call_expr.h"
#include "cond_expr.h"
#include "expression.h"
#include "goto_expr.h"
#include "label_expr.h"
#include "nop_expr.h"
#include "return_expr.h"
#include "switch_expr.h"
#include "dumper.h"

TextDumper::TextDumper(std::ostream* const out, bool withHeader) : Dumper(), _out(out), _withHeader(withHeader)
{}

void TextDumper::dumpExpression(Expression* const e)
{
	header();
	*_out << "<Expression for which we have not yet a type> : "
		<< *e;
}

void TextDumper::dumpAsmExpr(AsmExpr* const e)
{
	header();
	*_out << "Asm statement(s) : \n\t" << e->_stmt;
}

void TextDumper::dumpAssignExpr(AssignExpr* const e)
{
	header();
	*_out << "Affectation : " <<
		e->_whatToSet->print() << " = ";
		if (e->_rhs2)
		{
			*_out << e->_rhs1->print() << " " <<
			Operator::print(e->_op) << tree_code_name[e->_op] << " " <<
			e->_rhs2->print();
		} else {
			*_out << Operator::print(e->_op) << tree_code_name[e->_op] << " " <<
			e->_rhs1->print();
		}
}

void TextDumper::dumpCallExpr(CallExpr* const e)
{
	header();
	*_out << "Function call : " << e->_built_str;
}

void TextDumper::dumpCondExpr(CondExpr* const e)
{
	header();
	*_out << "Conditional : " << std::endl;
	*_out << "\tif (";
	*_out << e->_lhs->print() << Operator::print(e->_op)
	      << e->_rhs->print() << ")" << std::endl;
	*_out << "\tthen ";
	if (e->_then)
		*_out << "goto " << e->_then->print();
	*_out << "\n\telse ";
	if (e->_else)
		*_out << "goto " << e->_else->print();
}

void TextDumper::dumpGotoExpr(GotoExpr* const e)
{
	header();
	*_out << "Goto : " << e->_label->print();
}

void TextDumper::dumpLabelExpr(LabelExpr* const e)
{
	header();
	*_out << "Label : " << e->_label->print();
}

void TextDumper::dumpNopExpr(NopExpr* const e)
{
	*_out << "No-op";
}

void TextDumper::dumpReturnExpr(ReturnExpr* const e)
{
	header();
	*_out << "Return from function";
	if (e->_value) {
		*_out << " : " << e->_value->print();
	}
}

void TextDumper::dumpBbList(BbList* const e)
{
	*_out << "***Statements***" << std::endl;
	for (auto expr : e->_exprs) {
		expr->accept(*this);
		*_out << std::endl;
	}
	*_out << "***end of statements***" << std::endl;
}

void TextDumper::dumpSwitchExpr(SwitchExpr* const e)
{
	header();
	*_out << "Switch ("  << e->_var->print() << ") : ";
	*_out << std::endl;
	for (std::shared_ptr<Value> l : e->_labels)
		*_out << l->print() << std::endl;
	*_out << "*** end of switch ***";
}

void TextDumper::header()
{
	if (_withHeader)
		*_out << "<" << main_input_filename << "> : ";
}
