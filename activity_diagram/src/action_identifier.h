#ifndef ACTION_IDENTIFIER_H
#define ACTION_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	class ActionIdentifier : public FlowIdentifier
	{
		public:
			ActionIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

