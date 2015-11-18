/**
 * \file dumper.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of the Dumper interface
 */
#ifndef DUMPER_H
#define DUMPER_H

class AsmExpr;
class AssignExpr;
class FunctionBody;
class CallExpr;
class PhiExpr;
class CondExpr;
class GotoExpr;
class LabelExpr;
class NopExpr;
class ReturnExpr;
class SwitchExpr;
class Expression;

/**
 * \brief Dumper interface
 *
 * The Dumper's role is to output subclasses of Expression or FunctionBody in
 * some format. Each class implementing the Dumper interface defines an output
 * format: text, graph, etc.
 */
class Dumper
{
	public:
		/**
		 * \brief Dump an asm statement
		 * \param e the asm expression
		 */
		virtual void dumpAsmExpr(AsmExpr* const e) = 0;
		/**
		 * \brief Dump an assignment statement
		 * \param e the assignment expression
		 */
		virtual void dumpAssignExpr(AssignExpr* const e) = 0;
		/**
		 * \brief Dump a function calling statement
		 * \param e the function calling expression
		 */
		virtual void dumpCallExpr(CallExpr* const e) = 0;
		/**
		 * \brief Dump a phi statement
		 * \param e the phi expression
		 */
		virtual void dumpPhiExpr(PhiExpr* const e) = 0;
		/**
		 * \brief dump a conditional branching
		 * \param e the condition expression
		 */
		virtual void dumpCondExpr(CondExpr* const e) = 0;
		/**
		 * \brief Dump a function body, consisting of basic blocks
		 * \param e the function body
		 */
		virtual void dumpFunctionBody(FunctionBody* const e) = 0;
		/**
		 * \brief dump a unconditional branching
		 * \param e the goto expression
		 */
		virtual void dumpGotoExpr(GotoExpr* const e) = 0;
		/**
		 * \brief dump a label
		 * \param e the label expression
		 */
		virtual void dumpLabelExpr(LabelExpr* const e) = 0;
		/**
		 * \brief dump a no-op
		 * \param e the no-op expression
		 */
		virtual void dumpNopExpr(NopExpr* const e) = 0;
		/**
		 * \brief Dump a return statement
		 * \param e the return expression
		 */
		virtual void dumpReturnExpr(ReturnExpr* const e) = 0;
		/**
		 * \brief Dump a switch branching
		 * \param e the switch statement
		 */
		virtual void dumpSwitchExpr(SwitchExpr* const e) = 0;
		/**
		 * \brief Dump an untyped expression
		 * \param e the untyped expression
		 */
		virtual void dumpExpression(Expression* const e) = 0;

	protected:
		/**
		 * Construct an empty dumper
		 */
		Dumper() = default;
};

#endif
