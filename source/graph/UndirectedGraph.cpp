// UndirectedGraph.cpp
#include "UndirectedGraph.hpp"

#include <cassert>

namespace graph {

UndirectedGraph::UndirectedGraph(std::size_t const num_vertices) :
	_vertices(num_vertices)
{

}

std::size_t UndirectedGraph::num_vertices() const
{
	return _vertices.size();
}

Vertex const& UndirectedGraph::get_vertex(Vertex::Index const vertex_id) const
{
	assert(vertex_id < num_vertices());
	return _vertices[vertex_id];
}

Vertex::Vector const& UndirectedGraph::get_vertices() const
{
	return _vertices;
}

void UndirectedGraph::add_edge(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2)
{
	assert(vertex_id_1 < num_vertices());
	assert(vertex_id_2 < num_vertices());
	//TODO what to do with parallel edges?

	_vertices[vertex_id_1].add_neighbour(vertex_id_2);
	_vertices[vertex_id_2].add_neighbour(vertex_id_1);
}

void UndirectedGraph::add_edge(Edge const& edge)
{
	add_edge(edge.get_tail(), edge.get_head());
}

} // namespace graph
