/**
 * \file action_identifier.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of an action node identifier
 */

#ifndef ACTION_IDENTIFIER_H
#define ACTION_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	/**
	 * \brief Refine a \a FlowIdentifier to identify specifically an action
	 * node
	 */
	class ActionIdentifier : public FlowIdentifier
	{
		public:
			/**
			 * \brief Construct an \a ActionIdentifier from a
			 * Boost Graph Library node descriptor
			 * Identifier::Identifier(NodeDescriptor n)
			 * \param[in] n the Boost Graph Library node descriptor
			 */
			ActionIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

