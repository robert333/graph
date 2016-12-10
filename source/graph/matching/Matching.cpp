// Matching.cpp
#include "Matching.hpp"

#include <cassert>

namespace graph {

Matching::Matching(std::size_t const num_vertices) :
	_num_vertices(num_vertices),
	_cardinality(0),
	_matching_partner(num_vertices, Vertex::invalid_index())
{

}

bool Matching::is_vertex_covered(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _num_vertices));

	return _matching_partner[vertex_id] != Vertex::invalid_index();
}

Vertex::Index Matching::get_matching_partner(Vertex::Index const vertex_id) const
{
	assert(Vertex::is_index_valid(vertex_id, _num_vertices));
	assert(is_vertex_covered(vertex_id));

	return _matching_partner[vertex_id];
}

std::size_t Matching::cardinality() const
{
	return _cardinality;
}

bool Matching::is_perfect() const
{
	return 2 * cardinality() == _num_vertices;
}

Edge::Vector Matching::compute_matching_edges() const
{
	Edge::Vector matching_edges;
	matching_edges.reserve(cardinality());

	std::vector<bool> processed(_num_vertices, false);

	for (Vertex::Index vertex_id = 0; vertex_id < _num_vertices; ++vertex_id) {
		if (processed[vertex_id]) {
			continue;
		}

		if (is_vertex_covered(vertex_id)) {
			Vertex::Index const matching_partner = get_matching_partner(vertex_id);

			matching_edges.emplace_back(vertex_id, matching_partner);

			processed[vertex_id] = true;
			processed[matching_partner] = true;
		}
	}

	return matching_edges;
}

void Matching::match(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2)
{
	assert(Vertex::is_index_valid(vertex_id_1, _num_vertices));
	assert(Vertex::is_index_valid(vertex_id_2, _num_vertices));
	assert(vertex_id_1 != vertex_id_2);
	assert(_matching_partner[vertex_id_1] != vertex_id_2);
	assert(_matching_partner[vertex_id_2] != vertex_id_1);

	++_cardinality;

	_matching_partner[vertex_id_1] = vertex_id_2;
	_matching_partner[vertex_id_2] = vertex_id_1;
}

void Matching::match(Edge const& edge)
{
	match(edge.get_tail(), edge.get_head());
}

#ifndef NDEBUG
void Matching::divorce(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2)
#else
void Matching::divorce(Vertex::Index const, Vertex::Index const)
#endif
{
	assert(Vertex::is_index_valid(vertex_id_1, _num_vertices));
	assert(Vertex::is_index_valid(vertex_id_2, _num_vertices));
	assert(vertex_id_1 != vertex_id_2);
//	assert(_matching_partner[vertex_id_1] != vertex_id_2);
//	assert(_matching_partner[vertex_id_2] != vertex_id_1);
	assert(_cardinality > 0);

	--_cardinality;

//	_matching_partner[vertex_id_1] = Vertex::invalid_index();
//	_matching_partner[vertex_id_2] = Vertex::invalid_index();
}

} // namespace graph
