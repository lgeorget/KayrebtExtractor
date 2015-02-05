#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <memory>
#include <gcc-plugin.h>
#include "text_dumper.h"
#include "operator.h"
#include "assign_expr.h"
#include "bb_list.h"
#include "call_expr.h"
#include "case_label_expr.h"
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

void TextDumper::dumpAssignExpr(AssignExpr* const e)
{
	header();
	*_out << "Affectation : " <<
		e->_whatToSet->print() << " = " <<
		e->_rhs1->print() <<
		Operator::print(e->_op) <<
		e->_rhs2->print();
}

void TextDumper::dumpCaseLabelExpr(CaseLabelExpr* const e)
{
	header();
	*_out << "Case label : ";
	if (e->_lowValue) {
		*_out << e->_lowValue->print();
		if (e->_highValue) {
			*_out <<  " ... " << e->_highValue->print();
		}
	}
	else
		*_out << "default";
	*_out << e->_label->print();
}

void TextDumper::dumpCondExpr(CondExpr* const e)
{
	header();
	*_out << "Conditional : " << std::endl;
	*_out << "\tif (";
	*_out << e->_lhs->print() << Operator::print(e->_op)
	      << e->_rhs->print() << ")" << std::endl;
	*_out << "\tthen ";
	*_out << "goto " << e->_then->print();
	if (e->_else) {
		*_out << "\n\telse ";
		*_out << "goto " << e->_else->print();
	}
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
	for (std::shared_ptr<Expression> e : _labels)
		e->accept();
	*_out << "*** end of switch ***";
}

void TextDumper::header()
{
	if (_withHeader)
		*_out << "<" << main_input_filename << "> : ";
}
