// Matching.hpp
#ifndef GRAPH_MATCHING_HPP
#define GRAPH_MATCHING_HPP

#include "../Edge.hpp"

namespace graph {

class Matching {
public:

public:
	Matching(std::size_t const num_vertices);

	bool is_vertex_covered(Vertex::Index const vertex_id) const;
	Vertex::Index get_matching_partner(Vertex::Index const vertex_id) const;

	std::size_t cardinality() const;
	bool is_perfect() const;

	Edge::Vector compute_matching_edges() const;

	void match(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2);
	void match(Edge const& edge);

	void divorce(Vertex::Index const vertex_id_1, Vertex::Index const vertex_id_2);

private:

private:
	std::size_t /*const*/ _num_vertices;

	std::size_t _cardinality;
	std::vector<Vertex::Index> _matching_partner;
};

} // namespace graph

#endif
