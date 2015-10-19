/**
 * \file property_writer.h
 * \author Laurent Georget
 * \date 2015-03-03
 * \brief Definition of property writers for nodes and graphs
 */
#ifndef PROPERTY_WRITER_H
#define PROPERTY_WRITER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "identifier.h"
#include "attribute.h"

namespace kayrebt {
	class NodeWriter
	{
		public:
			NodeWriter(const std::map<NodeDescriptor,std::vector<std::unique_ptr<BaseAttribute>>>& attrs) : _attrs(attrs) {}
			template<typename VertexOrEdge>
			void operator()(std::ostream& out, const VertexOrEdge& v) {
				auto it = _attrs.find(v);
				if (it == _attrs.cend())
					return;
				
				auto attrIt = it->second.cbegin();
				if (attrIt == it->second.cend())
					return;

				out << "[";
				out << **attrIt;
				for ( ; attrIt != it->second.cend() ; ++attrIt)
					out << "," << **attrIt;
				out << "]";
			}
		private:
			const std::map<NodeDescriptor,std::vector<std::unique_ptr<BaseAttribute>>>& _attrs;
	};

	class GraphWriter
	{
		public:
			GraphWriter(const std::vector<std::unique_ptr<BaseAttribute>>& attrs) : _attrs(attrs) {}
			void operator()(std::ostream& out) {
				auto attrIt = _attrs.cbegin();
				if (attrIt == _attrs.cend())
					return;

				out << "graph [";
				out << **attrIt;
				for ( ; attrIt != _attrs.cend() ; ++attrIt)
					out << "," << **attrIt;
				out << "]\n";
			}
		private:
			const std::vector<std::unique_ptr<BaseAttribute>>& _attrs;
	};
}

#endif
