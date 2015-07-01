/**
 * \file init_identifier.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of an init node identifier
 */

#ifndef INIT_IDENTIFIER_H
#define INIT_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	/**
	 * \brief Refine a \a FlowIdentifier to identify specifically an init
	 * node
	 */
	class InitIdentifier : public FlowIdentifier
	{
		public:
			/**
			 * \brief Construct an \a InitIdentifier from a
			 * Boost Graph Library node descriptor
			 * Identifier::Identifier(NodeDescriptor n)
			 * \param[in] n the Boost Graph Library node descriptor
			 */
			InitIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

