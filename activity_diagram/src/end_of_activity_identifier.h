#ifndef END_OF_ACTIVITY_IDENTIFIER_H
#define END_OF_ACTIVITY_IDENTIFIER_H

#include "ending_node_identifier.h"

namespace kayrebt
{
	class EndOfActivityIdentifier : public EndingNodeIdentifier
	{
		public:
			EndOfActivityIdentifier(NodeDescriptor n) : EndingNodeIdentifier(n) {}
	};
}
#endif

