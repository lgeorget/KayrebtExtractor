/**
 * \file expression.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of an abstract, untyped, Expresion
 */
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <gcc-plugin.h>
#include <gimple.h>
#include <string>

class Dumper;

/**
 * \brief Motherclass of all expressions
 */
class Expression
{
	public:
		/**
		 * \brief Build an expression or statement from a GIMPLE value
		 * \param t the gimple expression
		 */
		explicit Expression(gimple t);
		/**
		 * \brief Virtual destructor
		 */
		virtual ~Expression() = default;
		/**
		 * \brief Visit method for dumpers
		 * \param d the visiting dumper, which must be called back
		 */
		virtual void accept(Dumper& d); // Visitor design pattern

	protected:
		/** The file at which the expression is found in the source
		 * code */
		std::string _file;
		/** The line number at which the expression is found in the
		 * source file */
		int _line = 0;

	private:
		/** The gimple expression */
		gimple _expr;

	/** Output an Expression in a textual form */
	friend std::ostream& operator<<(std::ostream& out, const Expression& e);
};

#endif
