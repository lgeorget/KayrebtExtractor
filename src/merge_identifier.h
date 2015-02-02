#ifndef MERGE_IDENTIFIER_H
#define MERGE_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	class MergeIdentifier : public FlowIdentifier
	{
		public:
			MergeIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

