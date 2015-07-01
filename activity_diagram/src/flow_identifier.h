/**
 * \file flow_identifier.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of an flow node identifier
 */

#ifndef FLOW_IDENTIFIER_H
#define FLOW_IDENTIFIER_H

#include "identifier.h"

namespace kayrebt
{
	/**
	 * \brief Refine an \a Identifier to identify specifically a flow node,
	 * that is, a node that must be followed by a successor node in the
	 * activity diagram
	 */
	class FlowIdentifier : public Identifier
	{
		protected:
			/**
			 * \brief Construct an \a FlowIdentifier from a
			 * Boost Graph Library node descriptor
			 *
			 * This abstract class is provided only for strong
			 * typing.
			 * Identifier::Identifier(NodeDescriptor n)
			 * \param[in] n the Boost Graph Library node descriptor
			 */
			FlowIdentifier(NodeDescriptor n) : Identifier(n) {}
	};
}
#endif

