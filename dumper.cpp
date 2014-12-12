#include <iostream>
#include <memory>
#include <gcc-plugin.h>
#include "dumper.h"

void Dumper::dumpExpression(std::shared_ptr<Expression> e)
{
	dumpChannel << header << "<Expression for which we have not yet a type>" <<
		*e << std::endl;
}

void Dumper::dumpCallExpr(std::shared_ptr<CallExpr> e)
{
	dumpChannel << header << "Function call : " << *e;
}

void Dumper::dumpDeclExpr(std::shared_ptr<DeclExpr> e)
{
	dumpChannel << header << "Declaration : " << *e;
}

void Dumper::dumpGotoExpr(std::shared_ptr<GotoExpr> e)
{
	dumpChannel << header << "Goto : " << *e;
}

void Dumper::dumpLabelExpr(std::shared_ptr<LabelExpr> e)
{
	dumpChannel << header << "Label : " << *e;
}

void Dumper::dumpModifyExpr(std::shared_ptr<ModifyExpr> e)
{
	dumpChannel << header << "Affectation : " << *e;
}

void Dumper::dumpPreincrementExpr(std::shared_ptr<PreincrementExpr> e)
{
	dumpChanner << header << "Preincrementation : " << *e;
}

void Dumper::dumpReturnExpr(std::shared_ptr<ReturnExpr> e)
{
	dumpChannel << header << "Return from function : " << *e;
}

std::ostream& Dumper::header()
{
	dumpChannel << "<" << main_input_filename << "> : ";
	return dumpChannel;
}
