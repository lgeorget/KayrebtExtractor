/**
 * \file sync_identifier.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of an sync node identifier
 */

#ifndef SYNC_IDENTIFIER_H
#define SYNC_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	/**
	 * \brief Refine a \a FlowIdentifier to identify specifically a sync
	 * node
	 */
	class SyncIdentifier : public FlowIdentifier
	{
		public:
			/**
			 * \brief Construct an \a SyncIdentifier from a
			 * Boost Graph Library node descriptor
			 * Identifier::Identifier(NodeDescriptor n)
			 * \param[in] n the Boost Graph Library node descriptor
			 */
			SyncIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

