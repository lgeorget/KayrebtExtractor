/**
 * \file ending_node_identifier.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of an ending node identifier
 */

#ifndef ENDING_NODE_IDENTIFIER_H
#define ENDING_NODE_IDENTIFIER_H

#include "identifier.h"

namespace kayrebt
{
	/**
	 * \brief Refine an \a Identifier to identify ending nodes, that is,
	 * nodes that cannot have successors in the activity diagram
	 */
	class EndingNodeIdentifier : public Identifier
	{
		protected:
			/**
			 * \brief Construct an \a EndingNodeIdentifier from a
			 * Boost Graph Library node descriptor
			 *
			 * This abstract class is provided only for strong
			 * typing.
			 * Identifier::Identifier(NodeDescriptor n)
			 * \param[in] n the Boost Graph Library node descriptor
			 */
			EndingNodeIdentifier(NodeDescriptor n) : Identifier(n) {}
	};
}
#endif

