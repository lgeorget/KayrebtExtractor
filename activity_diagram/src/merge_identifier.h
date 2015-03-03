/**
 * \file merge_identifier.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of an merge node identifier
 */

#ifndef MERGE_IDENTIFIER_H
#define MERGE_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	/**
	 * \brief Refine a \a FlowIdentifier to identify specifically a merge
	 * node
	 */
	class MergeIdentifier : public FlowIdentifier
	{
		public:
			/**
			 * \brief Construct a \a MergeIdentifier from a
			 * Boost Graph Library node descriptor
			 * Identifier::Identifier(NodeDescriptor n)
			 * \param[in] n the Boost Graph Library node descriptor
			 */
			MergeIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

