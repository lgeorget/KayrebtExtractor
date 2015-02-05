#ifndef BAD_GIMPLE_EXCEPTION_H
#define BAD_GIMPLE_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <gcc-plugin.h>
#include <gimple.h>

class BadGimpleException : public std::domain_error
{
	public:
		BadGimpleException(gimple got, const char* expected);
};

#endif
