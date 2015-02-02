#ifndef END_OF_FLOW_IDENTIFIER_H
#define END_OF_FLOW_IDENTIFIER_H

#include "ending_node_identifier.h"

namespace kayrebt
{
	class EndOfFlowIdentifier : public EndingNodeIdentifier
	{
		public:
			EndOfFlowIdentifier(NodeDescriptor n) : EndingNodeIdentifier(n) {}
	};
}
#endif

