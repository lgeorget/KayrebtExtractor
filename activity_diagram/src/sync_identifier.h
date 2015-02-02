#ifndef SYNC_IDENTIFIER_H
#define SYNC_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	class SyncIdentifier : public FlowIdentifier
	{
		public:
			SyncIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

