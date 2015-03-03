/**
 * \file end_of_activity_identifier.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of an end-of-activity node identifier
 */

#ifndef END_OF_ACTIVITY_IDENTIFIER_H
#define END_OF_ACTIVITY_IDENTIFIER_H

#include "ending_node_identifier.h"

namespace kayrebt
{
	/**
	 * \brief Refine an \a EndingNode to identify specifically an
	 * end-of-activity node
	 */
	class EndOfActivityIdentifier : public EndingNodeIdentifier
	{
		public:
			/**
			 * \brief Construct an \a EndOfActivityIdentifier from a
			 * Boost Graph Library node descriptor
			 * Identifier::Identifier(NodeDescriptor n)
			 * \param[in] n the Boost Graph Library node descriptor
			 */
			EndOfActivityIdentifier(NodeDescriptor n) : EndingNodeIdentifier(n) {}
	};
}
#endif

