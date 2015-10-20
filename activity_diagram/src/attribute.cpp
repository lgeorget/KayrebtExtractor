/**
 * \file attribute.cpp
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Implementation of structures that foreign code can use to embed extra
 *        attributes in the disgrams
 */

#include <iostream>
#include "attribute.h"

std::ostream& operator<<(std::ostream& out, const kayrebt::BaseAttribute& attr) {
	attr.print(out);
	return out;
}

