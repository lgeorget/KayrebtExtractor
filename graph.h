#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>

namespace Activity {
	struct vertex_shape_t {
		typedef vertex_property_tag kind;
	};

	enum VertexShapes {
		CHOICE,
		ASIGNATION,
	};
}

typedef property<vertex_name_t, std::string,
	property<Activity::vertex_shape_t, Activity::VertexShape>> VertexProperty;

typedef adjacency_list<listS, vecS, directedS, VertexProperty, no_property> ActivityGraph;

#endif
