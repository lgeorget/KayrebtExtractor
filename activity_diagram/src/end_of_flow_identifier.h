/**
 * \file end_of_flow_identifier.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of an end-of-flow node identifier
 */

#ifndef END_OF_FLOW_IDENTIFIER_H
#define END_OF_FLOW_IDENTIFIER_H

#include "ending_node_identifier.h"

namespace kayrebt
{
	/**
	 * \brief Refine an \a EndOfFlowIdentifier to identify specifically an
	 * end-of-flow node
	 */
	class EndOfFlowIdentifier : public EndingNodeIdentifier
	{
		public:
			/**
			 * \brief Construct an \a EndOfFlowIdentifier from a
			 * Boost Graph Library node descriptor
			 * Identifier::Identifier(NodeDescriptor n)
			 * \param[in] n the Boost Graph Library node descriptor
			 */
			EndOfFlowIdentifier(NodeDescriptor n) : EndingNodeIdentifier(n) {}
	};
}
#endif

