/**
 * \file object_identifier.h
 * \author Laurent Georget
 * \date 2015-03-02
 * \brief Definition of an object node identifier
 */

#ifndef OBJECT_IDENTIFIER_H
#define OBJECT_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	/**
	 * \brief Refine a \a FlowIdentifier to identify specifically an object
	 * node
	 */
	class ObjectIdentifier : public FlowIdentifier
	{
		public:
			/**
			 * \brief Construct an \a ObjectIdentifier from a
			 * Boost Graph Library node descriptor
			 * Identifier::Identifier(NodeDescriptor n)
			 * \param[in] n the Boost Graph Library node descriptor
			 */
			ObjectIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

