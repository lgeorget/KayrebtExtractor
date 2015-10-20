/**
 * \file attribute.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of structures that foreign code can use to embed extra
 *        attributes in the disgrams
 */

#include <boost/config.hpp>
#include <iostream>
#include "attribute.h"
#include <boost/graph/graphviz.hpp>

std::ostream& operator<<(std::ostream& out, const kayrebt::BaseAttribute& attr) {
	attr.print(out);
	return out;
}

namespace kayrebt {
	void default_outputter<std::string>::operator()(std::ostream& out, const std::string& value) const {
		out << boost::escape_dot_string(value);
	}

	void default_outputter<const char*>::operator()(std::ostream& out, const char*& value) const {
		out << boost::escape_dot_string(value);
	}
}
