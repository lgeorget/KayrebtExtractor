#ifndef ENDING_NODE_IDENTIFIER_H
#define ENDING_NODE_IDENTIFIER_H

#include "identifier.h"

namespace kayrebt
{
	class EndingNodeIdentifier : public Identifier
	{
		protected:
			EndingNodeIdentifier(NodeDescriptor n) : Identifier(n) {}
	};
}
#endif

