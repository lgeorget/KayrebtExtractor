/**
 * \file asm_expr.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the AsmExpr
 */
#include <iostream>
#include <string>
#include <gcc-plugin.h>
#include <gimple.h>
#include "asm_expr.h"
#include "value.h"
#include "bad_gimple_exception.h"
#include "value_factory.h"
#include "dumper.h"

AsmExpr::AsmExpr(gimple t) : Expression(t)
{
	if (gimple_code(t) != GIMPLE_ASM)
		throw BadGimpleException(t, "gimple_asm");

	const char* stmt = gimple_asm_string(t);
	_stmt = std::string(stmt);
	size_t n = _stmt.find('\n');
	for (; n != std::string::npos ; n = _stmt.find('\n',n)) {
		_stmt.erase(n,1);
		_stmt.insert(n,"\\n ");
		n+=3;
	}
	n = _stmt.find('"');
	for (; n != std::string::npos ; n = _stmt.find('"',n)) {
		_stmt.erase(n,1);
		_stmt.insert(n,"\\\"");
		n+=2;
	}
	n = _stmt.find('\t');
	for (; n != std::string::npos ; n = _stmt.find('\t',n)) {
		_stmt.erase(n,1);
	}
}

void AsmExpr::accept(Dumper& d)
{
	d.dumpAsmExpr(this);
}
