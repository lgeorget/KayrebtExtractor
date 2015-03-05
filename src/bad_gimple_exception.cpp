/**
 * \file bad_gimple_exception.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of the BadGimpleExpression
 */
#include <exception>
#include <stdexcept>
#include <gcc-plugin.h>
#include <gimple.h>
#include "bad_gimple_exception.h"

BadGimpleException::BadGimpleException(gimple got, const char* expected) :
	std::domain_error(std::string("Got ") + gimple_code_name[gimple_code(got)] + std::string(" while we were expecting ") + expected)
{}
