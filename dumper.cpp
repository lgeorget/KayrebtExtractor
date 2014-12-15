#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <memory>
#include <gcc-plugin.h>
#include "dumper.h"

Dumper::Dumper()
{}

void Dumper::dumpExpression(Expression* const e)
{
	header();
	std::cout << "<Expression for which we have not yet a type>"
		<< *e << std::endl;
}

void Dumper::dumpCallExpr(CallExpr* const e)
{
//	header();
	std::cout << "Function call : " << *e;
}

void Dumper::dumpDeclExpr(DeclExpr* const e)
{
	header();
	std::cout << "Declaration : " << *e;
}

void Dumper::dumpGotoExpr(GotoExpr* const e)
{
	header();
	std::cout << "Goto : " << *e;
}

void Dumper::dumpLabelExpr(LabelExpr* const e)
{
	header();
	std::cout << "Label : " << *e;
}

void Dumper::dumpModifyExpr(ModifyExpr* const e)
{
	header();
	std::cout << "Affectation : " << *e;
}

void Dumper::dumpPreincrementExpr(PreincrementExpr* const e)
{
	header();
	std::cout << "Preincrementation : " << *e;
}

void Dumper::dumpReturnExpr(ReturnExpr* const e)
{
	header();
	std::cout << "Return from function : " << *e;
}

void Dumper::header()
{
	std::cout << "<" << main_input_filename << "> : ";
}
