/**
 * \file activity_graph_internals.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of the PIMPL-ed class for use in kayrebt::ActivityGraph
 */
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <memory>
#include <map>
#include <vector>
#include "types.h"
#include "node.h"
#include "attribute.h"
#include "init_identifier.h"

namespace kayrebt
{
	/**
	 * \brief PIMPL-ed struct used in kayrebt::ActivityGraph
	 *
	 * This masks most dependencies, including Boost, from client code
	 * needing the activity_graph.h header.
	 */
	struct ActivityGraphInternals
	{
		/**
		 * \brief Construct kayrebt::ActivityGraph's attributes
		 */
		ActivityGraphInternals() : initNode(new InitIdentifier(add_vertex(inner)))
		{}

		GraphType inner; /*!< The underlying Boost graph */
		std::unique_ptr<InitIdentifier> initNode; /*!< The top node in the graph */
	};
}
