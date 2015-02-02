#ifndef OBJECT_IDENTIFIER_H
#define OBJECT_IDENTIFIER_H

#include "flow_identifier.h"

namespace kayrebt
{
	class ObjectIdentifier : public FlowIdentifier
	{
		public:
			ObjectIdentifier(NodeDescriptor n) : FlowIdentifier(n) {}
	};
}
#endif

