/**
 * \file fork_identifier.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of an fork node identifier
 */

#ifndef FORK_IDENTIFIER_H
#define FORK_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	/**
	 * \brief Refine a \a FlowIdentifier to identify specifically a fork
	 * node
	 */
	class ForkIdentifier : public FlowIdentifier
	{
		public:
			/**
			 * \brief Construct an \a ForkIdentifier from a
			 * Boost Graph Library node descriptor
			 * Identifier::Identifier(NodeDescriptor n)
			 * \param[in] n the Boost Graph Library node descriptor
			 */
			ForkIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

