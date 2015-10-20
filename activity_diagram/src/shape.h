/**
 * \file shape.h
 * \author Laurent Georget
 * \date 2015-10-20
 * \brief Definition of the enumeration of possible node shapes
 */
#ifndef ENUM_H
#define ENUM_H

namespace kayrebt {
	/**
	 * the type of the node for the activity diagram
	 */
	enum Shape {
		NOTE=0, /*!< a comment */
		INIT, /*!< the initial node */
		MERGE, /*!< a merge or a decision node */
		FORK, /*!< a fork node */
		ACTION, /*!< an action node */
		OBJECT, /*!< an object node */
		SYNC, /*!< a fusion node */
		END_OF_FLOW, /*!< an end-of-flow node */
		END_OF_ACTIVITY, /*!< an end-of-activity node */
		NO_NODE /*!< last and unused node type */
	};
}

#endif
