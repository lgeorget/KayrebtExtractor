#ifndef FORK_IDENTIFIER_H
#define FORK_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	class ForkIdentifier : public FlowIdentifier
	{
		public:
			ForkIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

