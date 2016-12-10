// Vertex.cpp
#include "Vertex.hpp"

#include <cassert>

namespace graph {

Vertex::Index Vertex::invalid_index()
{
	return std::numeric_limits<Index>::max();
}

bool Vertex::is_index_valid(Index const index, std::size_t const num_indices)
{
	assert(index != invalid_index());
	assert(index < num_indices);
	return index != invalid_index() and index < num_indices;
}

Vertex::Vertex()
{

}

void Vertex::add_neighbour(Index const vertex_id)
{
	_neighbours.push_back(vertex_id);
}

std::size_t Vertex::num_neighbours() const
{
	return _neighbours.size();
}

std::vector<Vertex::Index> const& Vertex::get_neighbours() const
{
	return _neighbours;
}

} // namespace graph
