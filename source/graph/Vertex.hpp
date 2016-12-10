// Vertex.hpp
#ifndef GRAPH_VERTEX_HPP
#define GRAPH_VERTEX_HPP

#include <vector>
#include <limits>

namespace graph {

class Vertex {
public:
	using Index = std::size_t;
	using Vector = std::vector<Vertex>;

public:
	static Index invalid_index();
	static bool is_index_valid(Index const index, std::size_t const num_indices);

public:
	Vertex();

	void add_neighbour(Index const vertex_id);

	std::size_t num_neighbours() const;

	std::vector<Index> const& get_neighbours() const;

private:

private:
	std::vector<Index> _neighbours;
};

} // namespace graph

#endif
