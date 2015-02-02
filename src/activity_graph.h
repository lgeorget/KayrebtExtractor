#ifndef ACTIVITY_GRAPH_H
#define ACTIVITY_GRAPH_H

#include <iostream>
#include <string>
#include <memory>
#include "action_identifier.h"
#include "flow_identifier.h"
#include "end_of_flow_identifier.h"
#include "end_of_activity_identifier.h"
#include "fork_identifier.h"
#include "init_identifier.h"
#include "identifier.h"
#include "merge_identifier.h"
#include "object_identifier.h"
#include "sync_identifier.h"


namespace kayrebt
{
	struct ActivityGraphInternals;
	class ActivityGraph
	{
		private:
			friend std::ostream& operator<<(std::ostream& out, const ActivityGraph& graph);
			ActivityGraphInternals* _d;

		public:
			ActivityGraph();
			~ActivityGraph();
			ActionIdentifier addAction(std::string label);
			ObjectIdentifier addObject(std::string label);
			ForkIdentifier fork();
			EndOfFlowIdentifier closeFlow();
			EndOfActivityIdentifier terminateActivity();
			MergeIdentifier addDecision();
			SyncIdentifier synchronize();
			void addEdge(const Identifier& branch, const Identifier& head);
			void addGuard(const Identifier& branch, const Identifier& head, std::string condition);
			void setLabel(Identifier& branch, std::string label);
			bool validate();
			bool validateConnexity();
			bool validateBranchesEndings();
			bool validateMergeEdges();
			//TODO validateForkSync();
			void simplifyMergeNodes();
			InitIdentifier initialNode() const;
	};
}
#endif
