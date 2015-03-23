/**
 * \file edge.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of an edge in the activity diagram
 */
#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <string>
#include <memory>

namespace kayrebt
{
	/**
	 * \brief Describe a possibly conditional transition in the activity
	 * diagram
	 */
	struct Edge
	{
		/**
		 * \brief Guard controlling the firing of the transition
		 */
		std::string condition;
		/**
		 * \brief Unspecified Category field, for use by external code
		 */
		unsigned int category = 0;
	};
}

#endif
