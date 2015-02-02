#ifndef FLOW_IDENTIFIER_H
#define FLOW_IDENTIFIER_H

#include "identifier.h"

namespace kayrebt
{
	class FlowIdentifier : public Identifier
	{
		protected:
			FlowIdentifier(NodeDescriptor n) : Identifier(n) {}
	};
}
#endif

