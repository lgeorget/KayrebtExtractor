/**
 * \file bad_gimple_exception.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of a runtime exception indicating that another GIMPLE
 * structure was expected at some point
 */
#ifndef BAD_GIMPLE_EXCEPTION_H
#define BAD_GIMPLE_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <gcc-plugin.h>
#include <gimple.h>

/**
 * \brief Represent a kind of caught error in the control flow: the wrong
 * GIMPLE value was supplied to some constructor
 */
class BadGimpleException : public std::domain_error
{
	public:
		/**
		 * \brief Construct a new BadGimpleExpression explaining
		 * which GIMPLE value was seen and which was expected
		 * \param got the GIMPLE value caught
		 * \param expected the expected GIMPLE value name
		 */
		BadGimpleException(gimple got, const char* expected);
};

#endif
