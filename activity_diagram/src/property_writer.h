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
	template<typename Graph>
	class NodeWriter
	{
		public:
			NodeWriter(const Graph& g, const std::map<NodeDescriptor,std::vector<std::shared_ptr<BaseAttribute>>>& attrs) : _attrs(attrs), _g(g) {}
			template<typename VertexOrEdge>
			void operator()(std::ostream& out, const VertexOrEdge& v) {
				//First, output mandatory attributes
				out << "[shape=\"" << _g[v].shape << "\"";
				if (!_g[v].label.empty())
					out << ",label=\"" << _g[v].label << "\"";

				//and then, the supplementary attributes
				auto it = _attrs.find(v);
				if (it != _attrs.cend()) {
					for (auto attrIt = it->second.cbegin() ;
					     attrIt != it->second.cend() ;
					     ++attrIt)
						out << "," << **attrIt;
				}

				//end
				out << "]";
			}
		private:
			const std::map<NodeDescriptor,std::vector<std::shared_ptr<BaseAttribute>>>& _attrs;
			const Graph& _g;
	};

	class GraphWriter
	{
		public:
			GraphWriter(const std::vector<std::shared_ptr<BaseAttribute>>& attrs) : _attrs(attrs) {}
			void operator()(std::ostream& out) {
				auto attrIt = _attrs.cbegin();
				if (attrIt == _attrs.cend())
					return;

				out << "graph [";
				out << **attrIt;
				for (++attrIt ; attrIt != _attrs.cend() ; ++attrIt)
					out << "," << **attrIt;
				out << "]\n";
			}
		private:
			const std::vector<std::shared_ptr<BaseAttribute>>& _attrs;
	};
}

#endif
