/**
 * \file expr_factory.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of the Expression Factory
 */
#ifndef EXPR_FACTORY_H
#define EXPR_FACTORY_H

#include <memory>
#include <gcc-plugin.h>
#include <gimple.h>
#include <function.h>
#include "expression.h"
#include "function_body.h"

/**
 * \brief Singleton used to build expressions from gimple and function structures
 */
class ExprFactory
{
	private:
		/** Build the factory, this is private because there can
		 * be only one instance of the factory */
		ExprFactory() = default;
		/** The no-op generic expression */
		std::shared_ptr<Expression> _nop;

	public:
		/** The public instance available to the world */
		static ExprFactory INSTANCE;
		/**
		 * \brief Build an Expression from a GIMPLE structure
		 * \param t the gimple structure
		 * \return the Expression built
		 */
		std::shared_ptr<Expression> build(gimple t);
		/**
		 * \brief Build an Expression from a GCC function structure
		 * \param t the function structure
		 * \return the Expression built
		 */
		std::shared_ptr<FunctionBody> build(function* t);
};

#endif
