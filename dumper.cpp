#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <memory>
#include <gcc-plugin.h>
#include "bind_expr.h"
#include "call_expr.h"
#include "case_label_expr.h"
#include "cond_expr.h"
#include "decl_expr.h"
#include "expression.h"
#include "goto_expr.h"
#include "label_expr.h"
#include "leaf.h"
#include "modify_expr.h"
#include "nop_expr.h"
#include "preincrement_expr.h"
#include "return_expr.h"
#include "stmt_list.h"
#include "switch_expr.h"
#include "dumper.h"

Dumper::Dumper(std::ostream* const out, bool withHeader) : _out(out), _withHeader(withHeader)
{}

void Dumper::dumpExpression(Expression* const e)
{
	header();
	*_out << "<Expression for which we have not yet a type> : "
		<< *e << std::endl;
}

void Dumper::dumpBindExpr(BindExpr* const e)
{
	header();
	*_out << "*** start of inner scope ***" << std::endl;
// Vars are declared in body too
//	e->_vars->accept(*this);
	e->_body->accept(*this);
	*_out << "*** end of inner scope ***" << std::endl;
}

void Dumper::dumpCallExpr(CallExpr* const e)
{
	header();
	*_out << "Function call : " << *e;
}

void Dumper::dumpCaseLabelExpr(CaseLabelExpr* const e)
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

void Dumper::dumpCondExpr(CondExpr* const e)
{
	header();
	*_out << "Conditional : " << std::endl;
	*_out << "\tif ";
	e->_cond->accept(*this);
	*_out << "\tthen ";
	e->_then->accept(*this);
	if (e->_else) {
		*_out << "\n\telse ";
		e->_else->accept(*this);
	}
}

void Dumper::dumpDeclExpr(DeclExpr* const e)
{
	header();
	*_out << "Declaration : " << e->_name->print();
	if (e->_init)
		*_out << " = " << e->_init->print();
	*_out << std::endl;
}

void Dumper::dumpGotoExpr(GotoExpr* const e)
{
	header();
	*_out << "Goto : " << *e;
}

void Dumper::dumpLabelExpr(LabelExpr* const e)
{
	header();
	*_out << "Label : " << *e;
}

void Dumper::dumpLeaf(Leaf* const e)
{
	header();
	*_out << e->_val->print();
}

void Dumper::dumpModifyExpr(ModifyExpr* const e)
{
	header();
	*_out << "Affectation : " << *e;
}

void Dumper::dumpNopExpr(NopExpr* const e)
{
}

void Dumper::dumpPreincrementExpr(PreincrementExpr* const e)
{
	header();
	*_out << "Preincrementation : " << *e;
}

void Dumper::dumpReturnExpr(ReturnExpr* const e)
{
	header();
	*_out << "Return from function : " << *e;
}

void Dumper::dumpStmtList(StmtList* const e)
{
	for (auto expr : e->_exprs) {
		expr->accept(*this);
		*_out << std::endl;
	}
}

void Dumper::dumpSwitchExpr(SwitchExpr* const e)
{
	header();
	*_out << "Switch : ";
	e->_cond->accept(*this);
	*_out << std::endl;
	e->_body->accept(*this);
	*_out << "*** end of switch ***" << std::endl;
}

void Dumper::header()
{
	if (_withHeader)
		*_out << "<" << main_input_filename << "> : ";
}
