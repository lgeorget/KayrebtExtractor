#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <memory>
#include "types.h"
#include "node.h"
#include "init_identifier.h"

namespace kayrebt
{
	struct ActivityGraphInternals
	{
		ActivityGraphInternals()
		{
			initNode = std::unique_ptr<InitIdentifier>(new InitIdentifier(add_vertex(Node{"INIT",INIT}, inner)));
		}

		GraphType inner;
		std::unique_ptr<InitIdentifier> initNode;
	};
}
