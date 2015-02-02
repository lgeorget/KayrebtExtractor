#ifndef INIT_IDENTIFIER_H
#define INIT_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	class InitIdentifier : public FlowIdentifier
	{
		public:
			InitIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

