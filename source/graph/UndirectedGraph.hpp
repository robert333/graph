// UndirectedGraph.hpp
#ifndef GRAPH_UNDIRECTED_GRAPH_HPP
#define GRAPH_UNDIRECTED_GRAPH_HPP

#include "Edge.hpp"

namespace graph {

class UndirectedGraph {
public:

public:
	UndirectedGraph(std::size_t const num_vertices);

	std::size_t num_vertices() const;

	Vertex const& get_vertex(Vertex::Index const vertex_id) const;

	Vertex::Vector const& get_vertices() const;

	void add_edge(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2);
	void add_edge(Edge const& edge);

private:

private:
	Vertex::Vector _vertices;
};

} // namespace graph

#endif
